#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Util/String.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Util/Optional.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdint.hxx" // uint64_t, int64_t

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

ELASTIC_APM_INLINE_FOR_IMPL
Optional< String > getEnvVar( const char* envVarName, const PmrByteAllocator& allocator );

using ProcessId = int64_t;

ELASTIC_APM_INLINE_FOR_IMPL
ProcessId getCurrentProcessId();

} } } } // namespace Elastic::Apm::Impl::Util

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   include "Elastic/Apm/Impl/Util/platform_impl.hxx"
#endif
