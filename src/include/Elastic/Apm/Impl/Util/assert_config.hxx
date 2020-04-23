#pragma once

#include "Elastic/Apm/Impl/Util/is_debug_build.hxx"

/// - To exclude asserts from the compiled code define ELASTIC_APM_ASSERT_ENABLED to 0
/// - If ELASTIC_APM_ASSERT_ENABLED is not defined then asserts are left in the compiled code
///     but asserts level can still be controlled (for example turned off) by the runtime configuration

#ifndef ELASTIC_APM_ASSERT_ENABLED_01
#   if defined( ELASTIC_APM_ASSERT_ENABLED ) && ( ELASTIC_APM_ASSERT_ENABLED == 0 )
#       define ELASTIC_APM_ASSERT_ENABLED_01 0
#   else
#       define ELASTIC_APM_ASSERT_ENABLED_01 1
#   endif
#endif

#if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

enum class AssertLevel
{
    not_set = -1,
    off = 0,

    O_1,
    O_n,

    all,
};

#   ifndef ELASTIC_APM_ASSERT_DEFAULT_LEVEL
#       if ( ELASTIC_APM_IS_DEBUG_BUILD_01 != 0 )
#           define ELASTIC_APM_ASSERT_DEFAULT_LEVEL all
#       else
#           define ELASTIC_APM_ASSERT_DEFAULT_LEVEL off
#       endif
#   endif

static constexpr AssertLevel assertDefaultLevel = AssertLevel:: ELASTIC_APM_ASSERT_DEFAULT_LEVEL;

} } } } // namespace Elastic::Apm::Impl::Util

#endif // #if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )
