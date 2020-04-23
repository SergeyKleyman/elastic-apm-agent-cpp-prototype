#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::size_t

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

template< typename Value >
bool isInInclusiveRange( const Value& rangeFirst, const Value& valueToCheck, const Value& rangeLast )
{
    return ( rangeFirst <= valueToCheck ) && ( valueToCheck <= rangeLast );
}

template< typename T, std::size_t N >
constexpr std::size_t arraySize( T (& /* arr */)[ N ] )
{
    return N;
}

} } } } // namespace Elastic::Apm::Impl::Util
