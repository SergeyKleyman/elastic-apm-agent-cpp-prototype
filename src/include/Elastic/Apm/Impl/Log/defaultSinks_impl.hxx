#pragma once

#include "Elastic/Apm/Log/defaultSinks.hxx"
#include "Elastic/Apm/Impl/Log/Backend/StdStreamSink.hxx"
#include "Elastic/Apm/Impl/Util/platform_detection.hxx"
#if ELASTIC_APM_IS_OS_WINDOWS != 0
#include "Elastic/Apm/Impl/Log/Backend/WindowsOutputDebugStringSink.hxx"
#endif

namespace Elastic { namespace Apm { namespace Log
{

ELASTIC_APM_INLINE_FOR_IMPL
Util::PmrVector< PSink > defaultSinks( const Util::PmrByteAllocator& allocator )
{
    Util::PmrVector< PSink > result{ allocator };

    result.push_back( Util::pmrAllocateUniqueTypeErasedDeleter< Impl::Log::Backend::StdStreamSink >(
            allocator
            , allocator ) );

    #if ELASTIC_APM_IS_OS_WINDOWS != 0
    result.push_back( Util::pmrAllocateUniqueTypeErasedDeleter< Impl::Log::Backend::WindowsOutputDebugStringSink >(
            allocator
            , allocator ) );
    #endif

    return result;
}

} } } // namespace Elastic::Apm::Log
