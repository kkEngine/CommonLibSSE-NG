#pragma once


#if !defined(ENABLE_SKYRIM_AE) || !defined(ENABLE_SKYRIM_SE)
/**
 * A macro which defines a modifier for expressions that vary by Skyrim Address Library IDs.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build only targets one family of Address Library.
 * </p>
 */
#define SKYRIM_ADDR constexpr
#else
/**
 * A macro which defines a modifier for expressions that vary by Skyrim address library IDs.
 *
 * <p>
 * Currently defined as <code>inline</code> to support multiple Address Library ID families dynamically.
 * </p>
 */
#define SKYRIM_ADDR inline
#endif

#if !defined(ENABLE_SKYRIM_AE) || !defined(ENABLE_SKYRIM_SE)
/**
 * A macro which defines a modifier for expressions that vary by the specific Skyrim runtime.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is for only a single runtime.
 * </p>
 */
#define SKYRIM_REL constexpr

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selective targeting.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is for only a single runtime.
 * </p>
 */
#define SKYRIM_REL_CONSTEXPR constexpr
#else
/**
 * A macro which defines a modifier for expressions that vary by the specific Skyrim runtime.
 *
 * <p>
 * Currently defined as <code>inline</code> to support multiple runtimes dynamically.
 * </p>
 */
#define SKYRIM_REL inline

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selective targeting.
 *
 * <p>
 * Currently defined as empty to support multiple runtimes.
 * </p>
 */
#define SKYRIM_REL_CONSTEXPR
#endif

