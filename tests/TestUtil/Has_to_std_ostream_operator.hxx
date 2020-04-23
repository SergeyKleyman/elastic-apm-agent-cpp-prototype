#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/ostream.hxx" // std::ostream
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::declval
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx" // std::true_type
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx" // boost::decay_t

namespace ElasticApmTests { namespace TestUtil
{

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

template< typename T >
static auto
has_to_std_ostream_operator_helper( int )
-> decltype( std::declval< std::ostream& >() << std::declval< const T& >() , std::true_type{} );

template< typename >
static auto
has_to_std_ostream_operator_helper( ... )
-> std::false_type;

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

template< typename T >
struct Has_to_std_ostream_operator : decltype( has_to_std_ostream_operator_helper< boost::decay_t< T > >( 0 ) )::type
{
};

} } // namespace ElasticApmTests::TestUtil
