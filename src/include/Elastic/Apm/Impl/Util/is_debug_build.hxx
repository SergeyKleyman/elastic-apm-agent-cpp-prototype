#pragma once

/// - To force release build define ELASTIC_APM_IS_DEBUG_BUILD_01 to 0
/// - To force debug build define ELASTIC_APM_IS_DEBUG_BUILD_01 to any value different from 0 (for example 1)
/// - If ELASTIC_APM_IS_DEBUG_BUILD_01 is not defined then whether it's debug build will be detected automatically

#ifndef ELASTIC_APM_IS_DEBUG_BUILD_01
#   ifdef NDEBUG
#       define ELASTIC_APM_IS_DEBUG_BUILD_01 0
#   else
#       define ELASTIC_APM_IS_DEBUG_BUILD_01 1
#   endif
#endif
