#pragma once

#include "Elastic/Apm/Util/SystemClockTimePoint.hxx"

namespace Elastic { namespace Apm { namespace Util
{

class ISystemClock
{
public:

    virtual SystemClockTimePoint now() = 0;

protected:

    ~ISystemClock() = default;
};

} } } // namespace Elastic::Apm::Util
