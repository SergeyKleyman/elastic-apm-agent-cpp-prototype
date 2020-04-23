#pragma once

#include "Elastic/Apm/Log/Level.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_via_ADL.hxx"
#include "Elastic/Apm/Impl/Util/basic_util.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Impl::Util;
using namespace Elastic::Apm::Log;

ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
inline
bool streamToVisualLogImpl( Level level, IVisualStream& logVisualStream )
{
    auto name = levelName( level );

    if ( name ) return logVisualStream.write( *name );

    if ( ! logVisualStream.write( literalToView( "Unknown (as int: " ) ) ) return false;
    if ( ! logVisualStream.write( static_cast< int >( level ) ) ) return false;
    return logVisualStream.write( ')' );
}

} } } } // namespace Elastic::Apm::Impl::Log

//
// NOTE: streamToLogImpl for Level has to be in the same namespace as Level
// so that streamToLogImpl can be found via ADL
//
namespace Elastic { namespace Apm { namespace Log
{

ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
inline
bool streamToLogImpl( Level level, IStream& logStream )
{
    if ( auto logVisualStream = logStream.asVisual() ) return Impl::Log::streamToVisualLogImpl( level, *logVisualStream );

    // TODO: Sergey Kleyman: Implement: write Level as a map: { "value": <value as int>, "name": <name as string if known> }

    auto name = Impl::Log::levelName( level );
    if ( name ) return logStream.writeCurrentValueContent( *name );

    return logStream.writeCurrentValueContent( static_cast< int >( level ) );
}

} } } // namespace Elastic::Apm::Log
