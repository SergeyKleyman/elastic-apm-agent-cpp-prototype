#pragma once

#include "Elastic/Apm/Impl/Util/PmrBoostVector.hxx"

namespace Elastic { namespace Apm { namespace Util
{

template< typename T >
using PmrVector = Impl::Util::PmrBoostVector< T >;

} } } // namespace Elastic::Apm::Util
