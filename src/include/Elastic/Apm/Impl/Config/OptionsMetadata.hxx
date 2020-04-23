#pragma once

#include "Elastic/Apm/Util/PmrVector.hxx"
#include "Elastic/Apm/Util/PmrUniquePtr.hxx"
#include "Elastic/Apm/Impl/Config/IOptionMetadata.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

template< class SnapshotType >
using OptionsMetadata = PmrVector< PmrUniquePtr< IOptionMetadata< SnapshotType > > >;

} } } } // namespace Elastic::Apm::Impl::Config
