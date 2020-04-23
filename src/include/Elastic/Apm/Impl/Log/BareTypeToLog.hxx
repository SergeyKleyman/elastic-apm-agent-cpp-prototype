#pragma once

#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

namespace Internals
{

template< typename T, typename Enabled = void >
struct BareTypeToLogHelper
{
    using type = T;
};

} // namespace Internals

template< typename T >
using BareTypeToLog = typename Internals::BareTypeToLogHelper< T >::type;

namespace Internals
{

template< typename T >
struct BareTypeToLogHelper< T, boost::enable_if_t< std::is_same< boost::decay_t< T >, T >::value && ! std::is_pointer< T >::value > >
{
    using type = T;
};

template< typename T >
struct BareTypeToLogHelper< T, boost::enable_if_t< ! std::is_same< boost::decay_t< T >, T >::value > >;

template< typename T >
struct BareTypeToLogHelper< T* >
{
    using type = BareTypeToLog< T >*;
};

template< typename T >
struct BareTypeToLogHelper< T, boost::enable_if_t< ! std::is_same< boost::decay_t< T >, T >::value > >
{
    using type = BareTypeToLog< boost::decay_t< T > >;
};

} // namespace Internals

// TODO: Sergey Kleyman: Uncomment
static_assert( std::is_same< BareTypeToLog< int >, int >::value, "" );
static_assert( std::is_same< BareTypeToLog< int& >, int >::value, "" );
static_assert( std::is_same< BareTypeToLog< const int& >, int >::value, "" );
static_assert( std::is_same< BareTypeToLog< int* >, int* >::value, "" );
static_assert( std::is_same< BareTypeToLog< const int* >, int* >::value, "" );
static_assert( std::is_same< BareTypeToLog< int*& >, int* >::value, "" );
static_assert( std::is_same< BareTypeToLog< const int*& >, int* >::value, "" );
static_assert( std::is_same< BareTypeToLog< int (&) [5] >, int* >::value, "" );
static_assert( std::is_same< BareTypeToLog< const int (&) [5] >, int* >::value, "" );
static_assert( std::is_same< BareTypeToLog< const int* (&) [5] >, int** >::value, "" );
static_assert( std::is_same< BareTypeToLog< char [1] >, char* >::value, "" );
static_assert( std::is_same< BareTypeToLog< const char [1] >, char* >::value, "" );
static_assert( std::is_same< BareTypeToLog< decltype( "" ) >, char* >::value, "" );
static_assert( std::is_same< BareTypeToLog< decltype( "1" ) >, char* >::value, "" );


#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

} } } } // namespace Elastic::Apm::Impl::Log
