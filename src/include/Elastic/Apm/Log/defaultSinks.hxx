#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Log/ISink.hxx"
#include "Elastic/Apm/Util/PmrVector.hxx"

namespace Elastic { namespace Apm { namespace Log
{

ELASTIC_APM_INLINE_FOR_IMPL
Util::PmrVector< PSink > defaultSinks( const Util::PmrByteAllocator& allocator );

} } } // namespace Elastic::Apm::Log

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   include "Elastic/Apm/Impl/Log/defaultSinks_impl.hxx"
#endif
