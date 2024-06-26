#if defined(_WIN32)
/**
 * @file win-undef.hpp
 * @brief Undefines previously defined Windows-specific macros.
 */
#ifdef min
#define UNDEFINED_MIN
#pragma push_macro("min")
#undef min
#endif

#ifdef max
#define UNDEFINED_MAX
#pragma push_macro("max")
#undef max
#endif

#ifdef near
#define UNDEFINED_NEAR
#pragma push_macro("near")
#undef near
#endif

#ifdef far
#define UNDEFINED_FAR
#pragma push_macro("far")
#undef far
#endif
#endif
