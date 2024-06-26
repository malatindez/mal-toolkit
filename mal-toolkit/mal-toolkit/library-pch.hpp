#pragma once
/**
 * @file library-pch.hpp
 * @brief Precompiled header (PCH) file for common headers used across the library.
 */

#include <assert.h>
#include <stdint.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <concepts>
#include <condition_variable>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <istream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <random>
#include <shared_mutex>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_set>
#include <variant>
#include <vector>

#ifndef __mal_toolkit_lambda_force_inline
#ifdef __clang__
#define __mal_toolkit_lambda_force_inline __attribute__((always_inline))
#elif defined(__GNUC__)
#define __mal_toolkit_lambda_force_inline  __attribute__((always_inline))
#elif _MSC_VER
#define __mal_toolkit_lambda_force_inline  [[msvc::forceinline]]
#endif
#endif

#ifndef MAL_TOOLKIT_NO_SOURCE_LOCATION
#if __has_include(<source_location>)
#include <source_location>
#elif __has_include(<experimental/source_location>)
#include <experimental/source_location>
namespace std
{
    using source_location = std::experimental::source_location;
}
#else
#define MAL_TOOLKIT_NO_SOURCE_LOCATION
#endif
#endif
