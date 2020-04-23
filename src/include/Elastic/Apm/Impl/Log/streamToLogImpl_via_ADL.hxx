#pragma once

#include "Elastic/Apm/Impl/Log/streamToLogImpl_base.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCUnusedStructInspection"
#endif

//
// Example of a class with standalone streamToLogImpl function that is found via ADL (argument dependent lookup):
//
//        #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
//        #   pragma clang diagnostic push
//        #   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
//        #endif
//
//        inline
//        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
//        bool
//        streamToLogImpl( const Xyz& xyz, Log::IStream& logStream )
//        {
//            ...
//        }
//
//        #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
//        #   pragma clang diagnostic pop
//        #endif

namespace Internals
{

template< typename T >
ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
bool invoke_streamToLogImpl_via_ADL( const T& t, IStream& logStream )
{
    return streamToLogImpl( t, logStream );
}

} // namespace Internals

ELASTIC_APM_DEFINE_STREAM_TO_LOG_IMPL_DETECTOR(
        Has_streamToLogImpl_via_ADL
        , streamToLogImpl( std::declval< const T& >(), std::declval< IStream& >() )
)

template< typename T >
struct StreamToLogImpl< T, boost::enable_if_t< Has_streamToLogImpl_via_ADL< T >::value > >
{
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const T& t, IStream& logStream )
    {
        return Internals::invoke_streamToLogImpl_via_ADL( t, logStream );
    }
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

} } } } // namespace Elastic::Apm::Impl::Log
