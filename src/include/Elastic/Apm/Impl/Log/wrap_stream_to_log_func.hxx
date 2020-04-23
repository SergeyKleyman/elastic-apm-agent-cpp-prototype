#pragma once

#include "Elastic/Apm/Impl/Log/streamToLogImpl_base.hxx"
#include "Elastic/Apm/Util/StringView.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

using namespace Elastic::Apm::Util;

template< typename StreamToLogFunc >
struct StreamToLogFuncWrapper
{
    ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( StreamToLogFuncWrapper, noexcept );

    explicit StreamToLogFuncWrapper( StringView exprName
                                     , const StreamToLogFunc& streamToLogFunc
    )
            : exprName{ exprName }
              , streamToLogFunc{ streamToLogFunc }
    {}

    StringView exprName;
    const StreamToLogFunc& streamToLogFunc;
};

template< typename StreamToLogFunc >
struct StreamToLogImpl< StreamToLogFuncWrapper< StreamToLogFunc > >
{
    static StringView preprocessExprToLogNameImpl(
            const StreamToLogFuncWrapper< StreamToLogFunc >& wrapper
            , StringView /* outerName */
    )
    {
        return wrapper.exprName;
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl(
            const StreamToLogFuncWrapper< StreamToLogFunc >& wrapper
            , IStream& logStream
    )
    {
        return wrapper.streamToLogFunc( logStream );
    }
};

template< typename StreamToLogFunc >
StreamToLogFuncWrapper< StreamToLogFunc > makeStreamToLogFuncWrapper(
        StringView outerName
        , const StreamToLogFunc& streamToLogFunc
)
{
    return StreamToLogFuncWrapper< StreamToLogFunc >{ outerName, streamToLogFunc };
}

} } } } // namespace Elastic::Apm::Impl::Log

#define ELASTIC_APM_WRAP_STREAM_TO_LOG_FUNC( exprName, streamToLogCall ) \
    ( Elastic::Apm::Impl::Log::makeStreamToLogFuncWrapper( exprName, streamToLogCall ) )
/**/

#define ELASTIC_APM_WRAP_STREAM_TO_LOG_DIRECT_RETURN( exprName, streamToLogCall ) \
    ELASTIC_APM_WRAP_STREAM_TO_LOG_FUNC( exprName, [&]( ILogStream& logStream ){ return (streamToLogCall); } )
/**/