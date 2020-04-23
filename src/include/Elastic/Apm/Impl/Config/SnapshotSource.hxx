#pragma once

#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Config/Snapshot.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm;

class SnapshotSource
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( SnapshotSource );

    explicit SnapshotSource( PSnapshot snapshot )
        : _snapshot{ std::move( snapshot ) }
    {}

    PSnapshot currentSnapshot() const
    {
        return _snapshot;
    }

private:

    PSnapshot _snapshot;
};

} } } } // namespace Elastic::Apm::Impl::Config
