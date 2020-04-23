#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::declval
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
#include "Elastic/Apm/Impl/Log/BareTypeToLog.hxx"
#include "Elastic/Apm/Log/IStream.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

using namespace Elastic::Apm::Log;

template< typename T, typename Enabled = void >
struct StreamToLogImpl
{
//    static StringView preprocessExprToLogNameImpl( const T& t, StringView outerName )
//    {
//        // return ...
//    }

//    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
//    static bool streamToLogImpl( const T& t, IStream& logStream )
//    {
//        // return ...
//    }
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

#define ELASTIC_APM_DEFINE_STREAM_TO_LOG_IMPL_DETECTOR_EX( DetectorName, streamToLogExpr, returnType ) \
    namespace Internals \
    { \
    \
        template< typename T > \
        static auto \
        helper_for_##DetectorName( int ) \
        -> boost::enable_if_t< std::is_same< decltype( streamToLogExpr ), returnType >::value, std::true_type >; \
        \
        template< typename > \
        static auto \
        helper_for_##DetectorName( ... ) \
        -> std::false_type; \
    \
    } /* namespace Internals */ \
    \
    template< typename T > \
    struct DetectorName : decltype( Internals::helper_for_##DetectorName< BareTypeToLog< T > >( 0 ) )::type \
    {}; \
/**/

#define ELASTIC_APM_DEFINE_STREAM_TO_LOG_IMPL_DETECTOR( DetectorName, streamToLogExpr ) \
    ELASTIC_APM_DEFINE_STREAM_TO_LOG_IMPL_DETECTOR_EX( DetectorName, streamToLogExpr, /* returnType: */ bool ) \
/**/

ELASTIC_APM_DEFINE_STREAM_TO_LOG_IMPL_DETECTOR_EX(
        Has_preprocessExprToLogNameImpl
        , StreamToLogImpl< T >::preprocessExprToLogNameImpl( std::declval< const T& >(), std::declval< StringView >() )
        , /* returnType: */ StringView
)

ELASTIC_APM_DEFINE_STREAM_TO_LOG_IMPL_DETECTOR(
        HasStreamToLogImpl
        , StreamToLogImpl< T >::streamToLogImpl( std::declval< const T& >(), std::declval< IStream& >() )
)

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

template< typename T >
boost::enable_if_t< Has_preprocessExprToLogNameImpl< T >::value, StringView >
preprocessExprToLogName( const T& t, StringView outerName )
{
    return StreamToLogImpl< BareTypeToLog< T > >::preprocessExprToLogNameImpl( t, outerName );
}

template< typename T >
boost::enable_if_t< ! Has_preprocessExprToLogNameImpl< T >::value, StringView >
preprocessExprToLogName( const T& /* t */, StringView outerName )
{
    return outerName;
}

template< typename T >
ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
bool streamToLog( const T& t, IStream& logStream )
{
    static_assert( HasStreamToLogImpl< T >::value, "Type has to have streamToLogImpl() to be loggable" );

    return StreamToLogImpl< BareTypeToLog< T > >::streamToLogImpl( t, logStream );
}

//
// To investigate why some streamToLog< Xyz > does not compile
//
//    inline
//    void f()
//    {
//        StreamToLogImpl< BareTypeToLog< Xyz > >::streamToLogImpl( xyz, *static_cast< Stream* >( nullptr ) );
//    }

} } } } // namespace Elastic::Apm::Impl::Log
