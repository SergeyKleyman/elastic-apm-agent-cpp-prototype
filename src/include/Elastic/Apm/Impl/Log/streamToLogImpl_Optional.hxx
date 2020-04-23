#pragma once

#include "Elastic/Apm/Util/Optional.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_base.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

template< typename T >
struct StreamToLogImpl< Optional< T >, boost::enable_if_t< HasStreamToLogImpl< T >::value > >
{
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const Optional< T >& val, IStream& logStream )
    {
        if ( ! val ) return logStream.writeCurrentValueContent( nullptr );

        return streamToLog( *val, logStream );
    }
};

} } } } // namespace Elastic::Apm::Impl::Log
