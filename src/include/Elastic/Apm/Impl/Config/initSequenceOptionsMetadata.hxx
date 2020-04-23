#pragma once

#include "Elastic/Apm/Impl/Config/OptionsMetadata.hxx"
#include "Elastic/Apm/Impl/Config/Snapshot.hxx"
#include "Elastic/Apm/Impl/Util/pmrAllocateUnique.hxx"
#include "Elastic/Apm/Impl/Config/BoolOptionMetadata.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm::Impl::Util;

inline
OptionsMetadata< Snapshot >
initSequenceOptionsMetadata( const AmbientContext& ambientContext )
{
    OptionsMetadata< Snapshot > retVal;

    retVal.push_back( pmrAllocateUnique< BoolOptionMetadata< Snapshot > >(
            ambientContext.allocator()
            , /* name: */ PmrString{ "enabled", ambientContext.allocator() }
            , /* snapshotFieldPtr: */ &Snapshot::enabled
            , /* defaultValue: */ true
            , ambientContext ) );

    return retVal;
}

} } } } // namespace Elastic::Apm::Impl::Config
