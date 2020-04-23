#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Log/RecordDataRefs.hxx"
#include "Elastic/Apm/Util/SystemClockTimePoint.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

using namespace Elastic::Apm::Log;

class Manager;

class Facade
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Facade );

    explicit Facade( Manager& manager )
              : _manager{ manager }
    {}

    bool isEnabled( Level statementLevel ) const;

    SystemClockTimePoint genTimestamp() const;

    void consume( RecordDataRefs&& recDataRefs );

private:

    Manager& _manager;
};

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
