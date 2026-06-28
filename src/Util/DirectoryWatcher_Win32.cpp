#ifdef _WIN32
#include "Util/DirectoryWatcher.hpp"

#include <windows.h>

struct DirectoryWatcher::Implementation {
    HANDLE die_handle = INVALID_HANDLE_VALUE;
    OVERLAPPED overlapped = {};
    alignas(DWORD) char buffer[4096];
};

// === PUBLIC METHODS ===

DirectoryWatcher::DirectoryWatcher(const std::filesystem::path &watch_dir, Callback on_change, bool recursive)
    : impl_{std::make_unique<Implementation>(watch_dir, std::move(on_change), recursive)} {}

DirectoryWatcher::~DirectoryWatcher() = default;

DirectoryWatcher::DirectoryWatcher(DirectoryWatcher &&other) noexcept = default;
DirectoryWatcher &DirectoryWatcher::operator=(DirectoryWatcher &&other) noexcept = default;

void DirectoryWatcher::PollEvents() { impl_->Poll(); }
void DirectoryWatcher::SetEnabled(bool enabled) { impl_->enabled = enabled; }
bool DirectoryWatcher::IsEnabled() const { return impl_->enabled; }

#endif
