#pragma once

#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

namespace Internals
{

template< typename T >
struct IsStringCharHelper : std::integral_constant< bool
                                                    , std::is_same< T, char >::value
                                                      || std::is_same< T, wchar_t >::value
                                                      #ifdef __cpp_char8_t
                                                      || std::is_same< T, char8_t >::value
                                                      #endif
                                                      || std::is_same< T, char16_t >::value
                                                      || std::is_same< T, char32_t >::value>
{
};

template< typename T >
struct IsSignedNumericIntegerHelper
        : std::integral_constant< bool, std::is_integral< T >::value
                                        && ( !IsStringCharHelper< T >::value )
                                        && std::is_signed< T >::value >
{
};

template< typename T >
struct IsUnsignedNumericIntegerHelper
        : std::integral_constant< bool, std::is_integral< T >::value
                                        && ( !IsStringCharHelper< T >::value )
                                        && ( !std::is_same< T, bool >::value )
                                        && std::is_unsigned< T >::value >
{
};

template< typename T >
struct IsNumericIntegerHelper
        : std::integral_constant< bool, IsSignedNumericIntegerHelper< T >::value || IsUnsignedNumericIntegerHelper< T >::value >
{
};

} // namespace Internals

template< typename T >
struct IsStringChar : Internals::IsStringCharHelper< boost::remove_cv_ref_t< T > >
{
};

static_assert( IsStringChar< char >::value, "" );
static_assert( IsStringChar< wchar_t >::value, "" );
#ifdef __cpp_char8_t
static_assert( IsStringChar< char8_t >::value, "" );
#endif
static_assert( IsStringChar< char16_t >::value, "" );
static_assert( IsStringChar< char32_t >::value, "" );
static_assert( IsStringChar< const char >::value, "" );
static_assert( IsStringChar< const wchar_t& >::value, "" );
static_assert( IsStringChar< char16_t& >::value, "" );
static_assert( IsStringChar< const volatile char32_t& >::value, "" );

static_assert( !IsStringChar< unsigned char >::value, "" );
static_assert( !IsStringChar< signed char >::value, "" );
static_assert( !IsStringChar< int >::value, "" );
static_assert( !IsStringChar< double >::value, "" );
static_assert( !IsStringChar< IsStringChar< char > >::value, "" );

template< typename T >
struct IsSignedNumericInteger : Internals::IsSignedNumericIntegerHelper< boost::remove_cv_ref_t< T > >
{
};

static_assert( IsSignedNumericInteger< signed char >::value, "" );
static_assert( IsSignedNumericInteger< const short >::value, "" );
static_assert( IsSignedNumericInteger< volatile signed short >::value, "" );
static_assert( IsSignedNumericInteger< const int& >::value, "" );
static_assert( IsSignedNumericInteger< volatile signed int& >::value, "" );
static_assert( IsSignedNumericInteger< const volatile long& >::value, "" );
static_assert( IsSignedNumericInteger< signed long >::value, "" );
static_assert( IsSignedNumericInteger< long long >::value, "" );
static_assert( IsSignedNumericInteger< signed long long >::value, "" );
static_assert( IsSignedNumericInteger< intmax_t >::value, "" );
static_assert( !IsSignedNumericInteger< bool >::value, "" );
static_assert( !IsSignedNumericInteger< char >::value, "" );
static_assert( !IsSignedNumericInteger< unsigned char >::value, "" );
static_assert( !IsSignedNumericInteger< unsigned short >::value, "" );
static_assert( !IsSignedNumericInteger< unsigned int >::value, "" );
static_assert( !IsSignedNumericInteger< unsigned long >::value, "" );
static_assert( !IsSignedNumericInteger< uintmax_t >::value, "" );

template< typename T >
struct IsUnsignedNumericInteger : Internals::IsUnsignedNumericIntegerHelper< boost::remove_cv_ref_t< T > >
{
};

static_assert( IsUnsignedNumericInteger< unsigned char >::value, "" );
static_assert( IsUnsignedNumericInteger< const unsigned short >::value, "" );
static_assert( IsUnsignedNumericInteger< volatile unsigned int >::value, "" );
static_assert( IsUnsignedNumericInteger< const volatile unsigned long >::value, "" );
static_assert( IsUnsignedNumericInteger< const unsigned long long& >::value, "" );
static_assert( IsUnsignedNumericInteger< const volatile uintmax_t& >::value, "" );
static_assert( !IsUnsignedNumericInteger< bool >::value, "" );
static_assert( !IsUnsignedNumericInteger< char >::value, "" );
static_assert( !IsUnsignedNumericInteger< signed char >::value, "" );
static_assert( !IsUnsignedNumericInteger< short >::value, "" );
static_assert( !IsUnsignedNumericInteger< int >::value, "" );
static_assert( !IsUnsignedNumericInteger< signed int >::value, "" );
static_assert( !IsUnsignedNumericInteger< intmax_t >::value, "" );

template< typename T >
struct IsNumericInteger : Internals::IsNumericIntegerHelper< boost::remove_cv_ref_t< T > >
{
};

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

} } } } // namespace
