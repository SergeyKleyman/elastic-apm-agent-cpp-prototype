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
// Example of a class with streamToLogImpl method:
//
//    class MyClass
//    {
//    public:
//
//        #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
//        #   pragma clang diagnostic push
//        #   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
//        #endif
//
//        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
//        bool streamToLogImpl( Log::IStream& logStream ) const
//        {
//            ...
//        }
//
//        #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
//        #   pragma clang diagnostic pop
//        #endif
//
//    };

ELASTIC_APM_DEFINE_STREAM_TO_LOG_IMPL_DETECTOR(
        Has_streamToLogImpl_method
        , std::declval< const T& >().streamToLogImpl( std::declval< IStream& >() )
)

template< typename T >
struct StreamToLogImpl< T, boost::enable_if_t< Has_streamToLogImpl_method< T >::value > >
{
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const T& t, IStream& logStream )
    {
        return t.streamToLogImpl( logStream );
    }
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

} } } } // namespace
