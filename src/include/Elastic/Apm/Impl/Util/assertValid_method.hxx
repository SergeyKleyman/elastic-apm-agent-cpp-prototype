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
// Example of a class with assertValidImpl method:
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
//        void assertValidImpl( const AmbientContext& ambCtx ) const
//        {
//            ...
//        }
//
//        #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
//        #   pragma clang diagnostic pop
//        #endif
//
//    };

namespace Internals
{

template< typename T >
static auto
has_assertValidImpl_method_helper( int )
-> decltype( std::declval< const T& >().assertValidImpl( std::declval< const AmbientContext& >() ), std::true_type{} );

template< typename >
static auto
has_assertValidImpl_method_helper( ... )
-> std::false_type;

template< typename T >
struct has_assertValidImpl_method : decltype( has_assertValidImpl_method_helper< BareTypeToLog< T > >( 0 ) )::type
{
};

} // namespace Internals

template< typename T >
struct AssertValidImpl< T, boost::enable_if_t< Internals::has_assertValidImpl_method< T >::value > >
{
    static void assertValidImpl( const AmbientContext& ambCtx, const T& t )
    {
        t.assertValidImpl( ambCtx );
    }
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

} } } } // namespace Elastic::Apm::Impl::Util

#endif // #if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )
