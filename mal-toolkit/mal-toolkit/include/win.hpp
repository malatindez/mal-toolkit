#pragma once
/**
 * @file win.hpp
 * @brief Provides general Windows-specific utilities and includes necessary headers.
 */

#if defined(_WIN32)

#include "win-def.hpp"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <SDKDDKVer.h>
#include <windows.h>

#include "win-undef.hpp"

#endif