#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Log/RecordDataRefs.hxx"
#include "Elastic/Apm/Impl/Log/Backend/Facade.hxx"
#include "Elastic/Apm/Util/String.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Log;

class Logger
{
public:

    ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( Logger );

    explicit Logger( Backend::Facade& backend, String fqClassName )
            : _backend{ backend }
            , _fqClassName{ std::move( fqClassName ) }
    {}

    bool isEnabled( Level statementLevel ) const
    {
        return _backend.isEnabled( statementLevel );
    }

    void consume( RecordDataRefs&& recDataRefs ) const
    {
        recDataRefs.timestamp = _backend.genTimestamp();
        recDataRefs.sourceCodeLocation.fqClassName = _fqClassName;
        _backend.consume( std::move( recDataRefs ) );
    }

private:

    Backend::Facade& _backend;
    const String _fqClassName;
};

} } } } // namespace Elastic::Apm::Impl::Log
