#pragma once

#include "Elastic/Apm/Impl/Util/assertValid_base.hxx"

#if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCUnusedStructInspection"
#endif

//
// Example of a class with standalone assertValidImpl function that is found via ADL (argument dependent lookup):
//
//        #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
//        #   pragma clang diagnostic push
//        #   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
//        #endif
//
//        inline
//        void assertValidImpl( const AmbientContext& ambCtx, const Xyz& xyz )
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
static auto
has_assertValidImpl_via_ADL_helper( int )
-> decltype( assertValidImpl( std::declval< const AmbientContext& >(), std::declval< const T& >() ), std::true_type{} );

template< typename >
static auto
has_assertValidImpl_via_ADL_helper( ... )
-> std::false_type;

template< typename T >
struct has_assertValidImpl_via_ADL : decltype( has_assertValidImpl_via_ADL_helper< boost::decay_t< T > >( 0 ) )::type
{
};

template< typename T >
void invoke_assertValidImpl_via_ADL( const AmbientContext& ambCtx, const T& t )
{
    assertValidImpl( ambCtx, t );
}

} // namespace Internals

template< typename T >
struct AssertValidImpl< T, boost::enable_if_t< Internals::has_assertValidImpl_via_ADL< T >::value > >
{
    static void assertValidImpl( const AmbientContext& ambCtx, const T& t )
    {
        Internals::invoke_assertValidImpl_via_ADL( ambCtx, t );
    }
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

} } } } // namespace Elastic::Apm::Impl::Util

#endif // #if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )
