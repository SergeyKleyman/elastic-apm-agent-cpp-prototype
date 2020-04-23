#pragma once

#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Impl/Util/basic_util.hxx"
#include "Elastic/Apm/Impl/Util/repeat_n_times.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

inline
bool containsNewLine( StringView strView )
{
    for ( char c : strView ) if ( c == '\n' || c == '\r' ) return true;
    return false;
}

inline
char toUpperCase( char c )
{
    if ( ! isInInclusiveRange( 'a', c, 'z' ) ) return c;
    return static_cast< char >( ( c - 'a' ) + 'A' );
}

inline
void toUpperCaseInplace( char* bufferBegin, std::size_t bufferLength )
{
    ELASTIC_APM_REPEAT_N_TIMES_VAR( i, bufferLength )
    {
        bufferBegin[ i ] = toUpperCase( bufferBegin[ i ] );
    }
}

inline
bool areEqualIgnoringCase( char c1, char c2 )
{
    return toUpperCase( c1 ) == toUpperCase( c2 );
}

inline
bool areEqualIgnoringCase( StringView strVw1, StringView strVw2 )
{
    if ( strVw1.length() != strVw2.length() ) return false;

    ELASTIC_APM_REPEAT_N_TIMES_VAR( i, strVw1.length() )
    {
        if ( ! areEqualIgnoringCase( strVw1[ i ], strVw2[ i ] ) ) return false;
    }

    return true;
}

} } } } // namespace Elastic::Apm::Impl::Util
