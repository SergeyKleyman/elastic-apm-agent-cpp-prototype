#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Util/SystemClockTimePoint.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_via_ADL.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
ELASTIC_APM_INLINE_FOR_IMPL
bool streamToVisualLogImpl( SystemClockTimePoint timePoint, IVisualStream& logVisualStream );

} } } } // namespace Elastic::Apm::Impl::Util

//
// NOTE: streamToLogImpl for SystemClockTimePoint has to be in the same namespace as SystemClockTimePoint
// so that streamToLogImpl can be found via ADL
//
namespace Elastic { namespace Apm { namespace Util
{

ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
inline
bool streamToLogImpl( SystemClockTimePoint timePoint, Log::IStream& logStream )
{
    if ( auto logVisualStream = logStream.asVisual() ) return Impl::Util::streamToVisualLogImpl( timePoint, *logVisualStream );

    if ( ! logStream.writeCurrentValueType( literalToView( "SystemClockTimePoint" ) ) ) return false;
    return logStream.writeCurrentValueContent( toMicrosecondsSinceUnixEpoch( timePoint ) );
}

} } } // namespace Elastic::Apm::Util

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   include "Elastic/Apm/Impl/Util/SystemClockTimePoint_toLog_impl.hxx"
#endif
