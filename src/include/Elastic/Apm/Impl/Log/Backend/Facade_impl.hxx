#pragma once

#include "Elastic/Apm/Impl/Log/Backend/Facade.hxx"
#include "Elastic/Apm/Impl/Log/Backend/Manager.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Util;

ELASTIC_APM_INLINE_FOR_IMPL
bool Facade::isEnabled( Level statementLevel ) const
{
    return _manager.isEnabled( statementLevel );
}

ELASTIC_APM_INLINE_FOR_IMPL
void Facade::consume( RecordDataRefs&& recDataRefs )
{
    _manager.consume( std::move( recDataRefs ) );
}

ELASTIC_APM_INLINE_FOR_IMPL
SystemClockTimePoint Facade::genTimestamp() const
{
    return _manager.genTimestamp();
}

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
