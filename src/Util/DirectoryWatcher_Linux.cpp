#ifdef __linux__
#include "DirectoryWatcher.hpp"

#include <iostream>
#include <cstring>
#include <unordered_map>

#include <sys/inotify.h>
#include <unistd.h>

#include "Util/Aliases.hpp"

struct DirectoryWatcher::Implementation {
    i32 inotify_fd{-1};
    std::unordered_map<i32, std::filesystem::path> watch_descriptor_to_path;
    std::filesystem::path root_directory;
    Callback callback_function;
    bool enabled{false};
    bool recursive{true};

    Implementation(const std::filesystem::path &_watch_dir, Callback _on_change, bool _recursive)
        : root_directory{_watch_dir}, callback_function{std::move(_on_change)}, recursive{_recursive}
    {
        inotify_fd = inotify_init1(IN_NONBLOCK);
        if (-1 == inotify_fd) {
            std::cerr << "inotify failed to initialize in DirectoryWatcher!\n";
            std::exit(EXIT_FAILURE);
        }

        AddWatch(root_directory);

        if (recursive) {
            AddWatchRecursive(root_directory);
        }
    }

    ~Implementation() {
        for (auto &[wd, path] : watch_descriptor_to_path) {
            inotify_rm_watch(inotify_fd, wd);
        }
        close(inotify_fd);
    }

    void AddWatch(const std::filesystem::path &directory) {
        i32 wd = inotify_add_watch(inotify_fd, directory.c_str(),
                                   IN_CREATE | IN_MODIFY | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);

        if (-1 == wd) {
            std::cerr << "inotify failed to add watch for: " << directory << "\n";
            return;
        }

        auto [it, inserted] = watch_descriptor_to_path.try_emplace(wd, directory);
        if (!inserted) {
            std::cerr << "watch_descriptor already present in watch_descriptor_to_path!\n";
        }
    }

    void AddWatchRecursive(const std::filesystem::path &directory) {
        for (const auto &entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_directory()) {
                AddWatch(entry.path());
            }
        }
    }

    void RemoveWatch(i32 wd) {
        inotify_rm_watch(inotify_fd, wd);
        watch_descriptor_to_path.erase(wd);
    }

    void Poll() {
        if (!enabled) {
            return;
        }

        alignas(struct inotify_event) char buffer[4096];
        ssize_t bytes_read = read(inotify_fd, buffer, sizeof(buffer));

        if (bytes_read <= 0) {
            return; // no events or EAGAIN
        }

        char *ptr = buffer;

        while (ptr < buffer + bytes_read) {
            inotify_event event;
            std::memcpy(&event, ptr, sizeof(inotify_event));

            if (event.len > 0) {
                std::string filename = event.name;

                // sesolve the directory this watch descriptor corresponds to
                std::filesystem::path dir = root_directory;
                if (auto it = watch_descriptor_to_path.find(event.wd);
                    it != std::ranges::cend(watch_descriptor_to_path))
                {
                    dir = it->second;
                }

                std::filesystem::path full_path = dir / filename;

                // map inotify mask to FileAction
                FileAction action = FileAction::Modified;
                if      (event.mask & IN_CREATE)     { action = FileAction::Created; }
                else if (event.mask & IN_DELETE)     { action = FileAction::Deleted; }
                else if (event.mask & IN_MOVED_FROM) { action = FileAction::RenamedFrom; }
                else if (event.mask & IN_MOVED_TO)   { action = FileAction::RenamedTo; }

                // if a new subdirectory was created and we're recursive, watch it
                if ((event.mask & IN_CREATE) && (event.mask & IN_ISDIR) && recursive) {
                    AddWatch(full_path);
                }

                std::cout << "DirectoryWatcher: " << full_path << "\n";
                callback_function(FileEvent{action, full_path});
            }

            // advance pointer to next event
            ptr += sizeof(struct inotify_event) + event.len;
        }
    }
};

// === PUBLIC METHODS ===

DirectoryWatcher::DirectoryWatcher(const std::filesystem::path &watch_dir, Callback on_change,
                                   bool recursive)
    : impl_{std::make_unique<Implementation>(watch_dir, std::move(on_change), recursive)} {}

DirectoryWatcher::~DirectoryWatcher() = default;

DirectoryWatcher::DirectoryWatcher(DirectoryWatcher &&other) noexcept = default;
DirectoryWatcher &DirectoryWatcher::operator=(DirectoryWatcher &&other) noexcept = default;

void DirectoryWatcher::PollEvents() { impl_->Poll(); }
void DirectoryWatcher::SetEnabled(bool enabled) { impl_->enabled = enabled; }
bool DirectoryWatcher::IsEnabled() const { return impl_->enabled; }

#endif
