#pragma once

#include "Elastic/Apm/Util/ISystemClock.hxx"
#include "Elastic/Apm/Util/ISteadyClock.hxx"

namespace Elastic { namespace Apm { namespace Util
{

class ITimeSource
{
public:

    virtual ISystemClock& systemClock() = 0;
    virtual ISteadyClock& steadyClock() = 0;

protected:

    ~ITimeSource() = default;
};

} } } // namespace Elastic::Apm::Util
