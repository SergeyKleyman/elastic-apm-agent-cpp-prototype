#pragma once

#include "Elastic/Apm/Util/ITimeSource.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

class TimeSource
        : public ITimeSource
{
public:

    ISystemClock& systemClock() override
    {
        return _systemClock;
    }

    ISteadyClock& steadyClock() override
    {
        return _steadyClock;
    }

private:

    struct SystemClock: public ISystemClock
    {
        SystemClockTimePoint now() override
        {
            return boost::chrono::system_clock::now();
        }
    };

    struct SteadyClock: public ISteadyClock
    {
        SteadyClockTimePoint now() override
        {
            return boost::chrono::steady_clock::now();
        }
    };

private:

    SystemClock _systemClock;
    SteadyClock _steadyClock;
};

} } } } // namespace Elastic::Apm::Impl::Util
