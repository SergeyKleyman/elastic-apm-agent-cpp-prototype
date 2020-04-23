#pragma once

#include "Elastic/Apm/Impl/Util/assertValid_base.hxx"
#include "Elastic/Apm/Impl/Util/assert_macros.hxx"

#if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "OCUnusedStructInspection"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#endif

template< typename T >
struct AssertValidImpl< T*, boost::enable_if_t< ! HasAssertValidImpl< T >::value > >
{
    static void assertValidImpl( const AmbientContext& ambCtx, const boost::decay_t< T >* ptr )
    {
        ELASTIC_APM_ASSERT_WITH_CONTEXT( ambCtx, ptr != nullptr );
    }
};

template< typename T >
struct AssertValidImpl< T*, boost::enable_if_t< HasAssertValidImpl< T >::value > >
{
    static void assertValidImpl( const AmbientContext& ambCtx, const boost::decay_t< T >* ptr )
    {
        ELASTIC_APM_ASSERT_WITH_CONTEXT( ambCtx, ptr != nullptr );
        assertValid( ambCtx, *ptr );
    }
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

} } } } // namespace Elastic::Apm::Impl::Util

#endif // #if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )
