#pragma once

//
// We use boost::chrono instead of std::chrono because:
//
//      1) std::chrono::system_clock in C++11 is not guaranteed to use Unix epoch.
//
//      2) std::chrono in C++11 doesn't have I/O.
//
// Both of the features above were added only in C++20.
//
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/chrono/system_clocks.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdint.hxx" // int64_t

namespace Elastic { namespace Apm { namespace Util
{

//
// NOTE: SystemClockTimePoint must be a time point type that uses Unix epoch (midnight UTC of January 1, 1970)
//
using SystemClockTimePoint = boost::chrono::system_clock::time_point;

inline
int64_t toMicrosecondsSinceUnixEpoch( SystemClockTimePoint timePoint )
{
    return boost::chrono::duration_cast< boost::chrono::microseconds >( timePoint.time_since_epoch() ).count();
}

} } } // namespace Elastic::Apm::Util
