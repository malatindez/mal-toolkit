#pragma once
/**
 * @file mal-toolkit.hpp
 * @brief Main header file for the MAL Toolkit library, providing a comprehensive set of tools and utilities.
 */

namespace mal_toolkit
{
    /**
     * @namespace uuid
     * @brief Provides utilities for working with Universally Unique Identifiers (UUIDs).
     */

    /**
     * @namespace endianness
     * @brief Provides functions and utilities for handling endianness conversions.
     */

    /**
     * @namespace events
     * @brief Contains classes and utilities related to event handling and notification.
     *
     * The `events` namespace provides a set of tools for managing and working with events,
     * allowing different parts of a software system to communicate and respond to various
     * occurrences or changes. This namespace includes classes for defining, subscribing to,
     * and dispatching events, enabling a flexible and modular design for event-driven
     * applications.
     */
}  // namespace mal_toolkit
/**
 * @namespace mal_toolkit
 * @brief Contains a collection of tools and utilities provided by the MAL Toolkit library.
 */

// clang-format off
#include "library-pch.hpp"
#include "converter.hpp"
#include "backoffs.hpp"
#include "debug.hpp"
#include "measurer.hpp"
#include "string.hpp"
#include "template.hpp"
#include "timer.hpp"
#include "stl-helpers.hpp"
#include "macro.hpp"
#include "common-structures.hpp"
#include "byte-helper.hpp"
// clang-format on