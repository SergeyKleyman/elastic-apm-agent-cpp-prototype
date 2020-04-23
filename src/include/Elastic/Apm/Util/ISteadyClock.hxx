#pragma once

#include "Elastic/Apm/Util/SteadyClockTimePoint.hxx"

namespace Elastic { namespace Apm { namespace Util
{

class ISteadyClock
{
public:

    virtual SteadyClockTimePoint now() = 0;

protected:

    ~ISteadyClock() = default;
};

} } } // namespace Elastic::Apm::Util
