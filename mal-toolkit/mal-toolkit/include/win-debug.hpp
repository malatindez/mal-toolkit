#if defined(_WIN32)
/**
 * @file win-debug.hpp
 * @brief Provides Windows-specific debugging utilities and macros.
 */
#include <malloc.h>

#include "../library-pch.hpp"
#include "win.hpp"

namespace mal_toolkit::debug
{
    // works only if there's no debugger attached to the process
    void RedirectOutputDebugString(std::function<void(std::string_view)> const &);
}  // namespace mal_toolkit::debug
#endif