#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/container/pmr/vector.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

template< typename T >
using PmrBoostVector = boost::container::pmr::vector< T >;

} } } } // namespace Elastic::Apm::Impl::Util
