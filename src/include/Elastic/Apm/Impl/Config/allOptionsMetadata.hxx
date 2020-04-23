#pragma once

#include "Elastic/Apm/Impl/Config/initSequenceOptionsMetadata.hxx"
#include "Elastic/Apm/Impl/Config/StringOptionMetadata.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm::Impl::Util;

inline
OptionsMetadata< Snapshot >
allOptionsMetadata( const AmbientContext& ambientContext )
{
    auto retVal = initSequenceOptionsMetadata( ambientContext );

    retVal.push_back( pmrAllocateUnique< StringOptionMetadata< Snapshot > >(
            ambientContext.allocator()
            , /* name: */ PmrString{ "server_url", ambientContext.allocator() }
            , /* snapshotFieldPtr: */ &Snapshot::serverUrl
            , /* defaultValue: */ String::fromLiteral( "http://localhost:8200" )
            , ambientContext ) );

    retVal.push_back( pmrAllocateUnique< StringOptionMetadata< Snapshot > >(
            ambientContext.allocator()
            , /* name: */ PmrString{ "service_name", ambientContext.allocator() }
            , /* snapshotFieldPtr: */ &Snapshot::serviceName
            , /* defaultValue: */ String::fromLiteral( "Unknown C++ service" )
            , ambientContext ) );

    return retVal;
}

} } } } // namespace Elastic::Apm::Impl::Config
