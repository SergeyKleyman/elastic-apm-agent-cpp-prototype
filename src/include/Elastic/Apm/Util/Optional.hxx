#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/optional.hxx"

namespace Elastic { namespace Apm { namespace Util
{

template< typename T >
using Optional = boost::optional< T >;

} } } // namespace Elastic::Apm::Util
