#pragma once

#include "Elastic/Apm/Impl/Util/platform.hxx"
#include "Elastic/Apm/Impl/Util/platform_detection.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdlib.hxx" // std::getenv, _dupenv_s
#if ELASTIC_APM_IS_OS_WINDOWS == 0
#   include "Elastic/Apm/Impl/wrapped_3rd_party_headers/Linux/sys/types.hxx" // getpid
#   include "Elastic/Apm/Impl/wrapped_3rd_party_headers/Linux/unistd.hxx" // getpid
#else
#   include "Elastic/Apm/Impl/wrapped_3rd_party_headers/Windows/process.hxx" // _getpid
#endif
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Impl/Util/OnScopeExit.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

ELASTIC_APM_INLINE_FOR_IMPL
Optional <String> getEnvVar( const char* envVarName, const PmrByteAllocator& allocator )
{
#if ELASTIC_APM_IS_OS_WINDOWS == 0

    const char* envVarValue = std::getenv( envVarName );
    if ( envVarValue == nullptr ) return {};

    return String::copyOf( envVarValue, allocator );

#else

    char* envVarValue;
    size_t envVarValueLen;
    errno_t errnoRetval = _dupenv_s( &envVarValue, &envVarValueLen, envVarName );
    if ( errnoRetval != 0 ) return {};

    //
    // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/dupenv-s-wdupenv-s
    // If the variable is not found, then buffer is set to NULL, numberOfElements is set to 0,
    // and the return value is 0 because this situation is not considered to be an error condition.
    //
    if ( envVarValue == nullptr || envVarValueLen == 0 ) return {};

    ELASTIC_APM_ON_SCOPE_EXIT( ( [ & ]()
    { free( envVarValue ); } ) );
    return String::copyOf( StringView{ envVarValue, envVarValueLen - 1 }, allocator );

#endif
}

ELASTIC_APM_INLINE_FOR_IMPL
ProcessId getCurrentProcessId()
{
#if ELASTIC_APM_IS_OS_WINDOWS == 0

    return static_cast< int64_t >( getpid() );

#else

    return static_cast< int64_t >( _getpid() );

#endif
}

} } } } // namespace Elastic::Apm::Impl::Util
