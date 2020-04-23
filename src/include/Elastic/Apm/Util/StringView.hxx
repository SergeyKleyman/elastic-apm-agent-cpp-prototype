#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/utility/string_view.hxx"

namespace Elastic { namespace Apm { namespace Util
{

using StringView = boost::string_view;

template< std::size_t N >
constexpr StringView literalToView( const char (& stringLiteral )[ N ] )
{
    return { &( stringLiteral[ 0 ] ), N - 1 };
}

} } } // namespace Elastic::Apm::Util
