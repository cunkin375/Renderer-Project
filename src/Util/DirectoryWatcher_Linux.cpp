#ifdef __linux__
#include "DirectoryWatcher.hpp"

#include <sys/inotify.h>
#include <unordered_map>

#include "Util/Aliases.hpp"

namespace {}

struct DirectoryWatcher::Implementation {
    i32 inotify_fd;
    std::unordered_map<i32, std::filesystem::path> watch_descriptor_to_path;
    std::filesystem::path root_directory;
    Callback callback_function;
    bool enabled{true};
    bool recursive{true};

    constexpr Implementation(const std::filesystem::path &_watch_dir, Callback _on_change, bool _recursive)
    : root_directory{_watch_dir}, callback_function{_on_change}, recursive{_recursive} {};

    void AddWatchRecursive(const std::filesystem::path &directory) {}
    void RemoveWatch(i32 watch_descriptor) {}
    void Poll() {}
};

constexpr DirectoryWatcher::DirectoryWatcher(
    const std::filesystem::path &watch_dir, Callback on_change, bool recursive)
    : impl_{std::make_unique<Implementation>(watch_dir, on_change, recursive)} {}

void DirectoryWatcher::PollEvents() { impl_->Poll(); }
void DirectoryWatcher::SetEnabled(bool enabled) { impl_->enabled = enabled; }
bool DirectoryWatcher::IsEnabled() const { return impl_->enabled; }
#endif
