#if defined(_WIN32)
/**
 * @file win-def.hpp
 * @brief Defines Windows-specific macros and settings.
 */
#ifdef UNDEFINED_MIN
#pragma pop_macro("min")
#endif

#ifdef UNDEFINED_MAX
#pragma pop_macro("max")
#endif

#ifdef UNDEFINED_NEAR
#pragma pop_macro("near")
#endif

#ifdef UNDEFINED_FAR
#pragma pop_macro("far")
#endif
#endif