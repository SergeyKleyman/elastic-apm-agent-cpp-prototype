#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::declval
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx" // std::true_type
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx" // boost::decay_t
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_HAS_PRAGMA_CLANG
#include "Elastic/Apm/Impl/Util/assert_config.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"
#include "Elastic/Apm/Impl/Log/BareTypeToLog.hxx"

#if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Impl::Log;

template< typename T, typename Enabled = void >
struct AssertValidImpl
{
//    static void assertValidImpl( const AmbientContext& ambCtx, const T& t )
//    {
//        // ...
//    }
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

namespace Internals
{

template< typename T >
static auto
has_assertValidImpl_helper( int )
-> decltype( AssertValidImpl< T >::assertValidImpl( std::declval< const AmbientContext& >(), std::declval< const T& >() ), std::true_type{} );

template< typename >
static auto
has_assertValidImpl_helper( ... )
-> std::false_type;

} // namespace Internals

template< typename T >
struct HasAssertValidImpl : decltype( Internals::has_assertValidImpl_helper< BareTypeToLog< T > >( 0 ) )::type
{
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

template< typename T >
void assertValid( const AmbientContext& ambCtx, const T& t )
{
    static_assert( HasAssertValidImpl< T >::value, "Type has to have assertValidImpl()" );

    AssertValidImpl< boost::decay_t< T > >::assertValidImpl( ambCtx, t );
}

} } } } // namespace Elastic::Apm::Impl::Util

#endif // #if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )
