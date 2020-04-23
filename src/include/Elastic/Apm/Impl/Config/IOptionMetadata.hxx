#pragma once

#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Util/String.hxx"
#include "Elastic/Apm/Impl/Config/IRawSnapshot_ex.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Config;

template< class SnapshotType >
class IOptionMetadata
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( IOptionMetadata );

    IOptionMetadata() = default;
    virtual ~IOptionMetadata() = default;

    virtual void parse( const IRawSnapshot& rawSnapshot, /* out */ SnapshotType& dstSnapshot ) const = 0;
};

} } } } // namespace Elastic::Apm::Impl::Config
