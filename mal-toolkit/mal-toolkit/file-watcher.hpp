#pragma once
#include "event.hpp"
#include "library-pch.hpp"
/**
 * @file file-watcher.hpp
 * @brief Implements a file watcher that monitors changes to specified files or directories.
 */

namespace mal_toolkit::events
{
    /**
     * @brief Event class for files changed.
     *
     * Represents an event indicating that one or more files have changed.
     */
    class FilesChangedEvent final : public Event
    {
    public:
        /**
         * @brief Constructs a FilesChangedEvent instance.
         *
         * @param files The list of changed file paths.
         */
        explicit FilesChangedEvent(std::vector<std::filesystem::path> &&files)
            : Event(EventType::FilesChanged, EventCategoryUtils), files_{ std::move(files) }
        {
        }

        FilesChangedEvent(FilesChangedEvent &&) = default;
        FilesChangedEvent(FilesChangedEvent const &) = default;
        FilesChangedEvent &operator=(FilesChangedEvent &&) = delete;
        FilesChangedEvent &operator=(FilesChangedEvent const &) = delete;

        /**
         * @brief Get the list of changed file paths.
         *
         * @return A reference to the list of changed file paths.
         */
        [[nodiscard]] inline std::vector<std::filesystem::path> const &files_changed() { return files_; }
        EVENT_CLASS_TYPE(FilesChanged)
    private:
        std::vector<std::filesystem::path> files_;
    };
}  // namespace mal_toolkit::events
namespace mal_toolkit
{
    /**
     * @brief A class for monitoring file changes and notifying listeners.
     */
    class FileWatcher
    {
    public:
        /**
         * @brief Constructs a FileWatcher instance with an event callback.
         *
         * @param event_callback The callback function to be invoked on file changes.
         */
        explicit FileWatcher(::mal_toolkit::EventCallbackFn const &event_callback) : event_callback_{ event_callback }
        {
        }

        /**
         * @brief Add a file path to watch for changes.
         *
         * @param path The file path to watch.
         * @param recursive Whether to watch subdirectories recursively.
         */
        void AddPathToWatch(std::filesystem::path const &path, bool recursive = true)
        {
            if (std::filesystem::is_regular_file(path))
            {
                file_map_[path] = std::filesystem::last_write_time(path);
                return;
            }
            if (recursive) [[likely]]
            {
                for (auto &subpath : std::filesystem::recursive_directory_iterator(path))
                {
                    if (std::filesystem::is_regular_file(subpath))
                    {
                        file_map_[subpath.path()] = std::filesystem::last_write_time(subpath.path());
                    }
                }
            }
            else if (std::filesystem::is_directory(path))
            {
                for (auto &subpath : std::filesystem::directory_iterator(path))
                {
                    file_map_[subpath.path()] = std::filesystem::last_write_time(subpath.path());
                }
            }
        }

        /**
         * @brief Check for file updates and trigger event callback.
         */
        void OnUpdate()
        {
            std::vector<std::filesystem::path> paths;
            for (auto const &[file, ft] : file_map_)
            {
                if (!std::filesystem::exists(file))
                {
                    continue;
                }
                auto current_file_last_write_time = std::filesystem::last_write_time(file);
                if (file_map_[file] != current_file_last_write_time) [[unlikely]]
                {
                    file_map_[file] = current_file_last_write_time;
                    paths.emplace_back(file);
                }
            }
            if (!paths.empty()) [[unlikely]]
            {
                ::mal_toolkit::events::FilesChangedEvent fce{ std::move(paths) };
                event_callback_(fce);
            }
        }

    private:
        std::map<std::filesystem::path, std::filesystem::file_time_type> file_map_;
        ::mal_toolkit::EventCallbackFn event_callback_;
    };
}  // namespace mal_toolkit