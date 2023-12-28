#pragma once
#include "include/spdlog.hpp"
#include "library-pch.hpp"

/**
 * @file debug.hpp
 * @brief Contains debugging-related macros and utilities for assisting with debugging tasks.
 */

#ifndef MAL_TOOLKIT_ASSERT_LOGS

/**
 * @brief Indicates whether assertion logs are enabled (1) or disabled (0).
 *
 * If enabled, assertion logs will be generated when assertions fail.
 * Default value is 1.
 */
#define MAL_TOOLKIT_ASSERT_LOGS 1
#endif

/**
 * @def MAL_TOOLKIT_ASSERT_ABORTS
 * @brief Controls whether assertions should result in program abortion.
 *
 * If set to 1, failed assertions will lead to program abortion. If set to 0,
 * assertions will not abort the program, and behavior will depend on
 * MAL_TOOLKIT_ASSERT_THROWS. This option is ignored in _DEBUG mode.
 */

#if !defined(MAL_TOOLKIT_ASSERT_ABORTS)
#if defined(_DEBUG)
#define MAL_TOOLKIT_ASSERT_ABORTS 1
#define MAL_TOOLKIT_ASSERT_THROWS 0
#else
#define MAL_TOOLKIT_ASSERT_ABORTS 0
#endif
#endif

/**
 * @def MAL_TOOLKIT_ASSERT_THROWS
 * @brief Controls whether assertions throw exceptions in case of failure.
 *
 * If set to 1, failed assertions will throw exceptions. If set to 0, assertions
 * will not throw exceptions and will follow the behavior defined by
 * MAL_TOOLKIT_ASSERT_ABORTS. This option is ignored if
 * MAL_TOOLKIT_ASSERT_ABORTS is set to 1.
 */
#ifndef MAL_TOOLKIT_ASSERT_THROWS
#define MAL_TOOLKIT_ASSERT_THROWS 1
#endif

#ifdef _DEBUG
#ifndef MAL_TOOLKIT_ASSERT_ENABLED
/**
 * @def MAL_TOOLKIT_ASSERT_ENABLED
 * @brief Controls whether assertions are enabled in debug mode.
 *
 * If set to 1, assertions are enabled in debug mode. If set to 0, assertions
 * are disabled in debug mode.
 */
#define MAL_TOOLKIT_ASSERT_ENABLED 1
#endif
#ifndef MAL_TOOLKIT_ALWAYS_ASSERT_ENABLED
/**
 * @def MAL_TOOLKIT_ALWAYS_ASSERT_ENABLED
 * @brief Controls whether always assertions are enabled in debug mode.
 *
 * If set to 1, always assertions are enabled in debug mode. If set to 0, always
 * assertions are disabled in debug mode.
 */
#define MAL_TOOLKIT_ALWAYS_ASSERT_ENABLED 1
#endif
#else
#ifndef MAL_TOOLKIT_ASSERT_ENABLED
#define MAL_TOOLKIT_ASSERT_ENABLED 0
#endif
#ifndef MAL_TOOLKIT_ALWAYS_ASSERT_ENABLED
#define MAL_TOOLKIT_ALWAYS_ASSERT_ENABLED 1
#endif
#endif

#ifndef MAL_TOOLKIT_FORCE_ASSERT
#ifdef _DEBUG
/**
 * @def MAL_TOOLKIT_FORCE_ASSERT
 * @brief Controls whether assertions are forced to execute.
 *
 * If set to 1, assertions are forcibly executed. If set to 0, assertions are
 * executed based on the conditions defined by other macros.
 */
#define MAL_TOOLKIT_FORCE_ASSERT 1
#else
#define MAL_TOOLKIT_FORCE_ASSERT 0
#endif
#endif

#if MAL_TOOLKIT_ASSERT_THROWS
#define MAL_TOOLKIT_ASSERT_NOEXCEPT
#else
#define MAL_TOOLKIT_ASSERT_NOEXCEPT noexcept
#endif

#ifdef MAL_TOOLKIT_NO_SOURCE_LOCATION
#include "detail/debug_without_source_location.hpp"
#else
#include "detail/debug_with_source_location.hpp"
#endif