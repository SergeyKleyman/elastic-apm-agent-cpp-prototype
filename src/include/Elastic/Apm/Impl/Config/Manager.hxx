#pragma once

#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Config/Parser.hxx"
#include "Elastic/Apm/Impl/Config/SnapshotSource.hxx"
#include "Elastic/Apm/Impl/Config/allOptionsMetadata.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm;

class Manager
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Manager );

    explicit Manager( IRawSnapshotSource& rawSnapshotSource, const AmbientContext& ambientContext )
        : _parser{ allOptionsMetadata( ambientContext ), ambientContext }
        , _rawSnapshotSource{ rawSnapshotSource }
        , _snapshotSource{ _parser.parse( *_rawSnapshotSource.currentSnapshot() ) }
    {}

    SnapshotSource& snapshotSource()
    {
        return _snapshotSource;
    }

private:

    const Parser< Snapshot > _parser;
    IRawSnapshotSource& _rawSnapshotSource;
    SnapshotSource _snapshotSource;
};

} } } } // namespace Elastic::Apm::Impl::Config
