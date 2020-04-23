#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/chrono/system_clocks.hxx"

namespace Elastic { namespace Apm { namespace Util
{

using SteadyClockTimePoint = boost::chrono::steady_clock::time_point;

} } } // namespace Elastic::Apm::Util
