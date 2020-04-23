#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::shared_ptr
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Log/Level.hxx"
#include "Elastic/Apm/Util/String.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm;
using namespace Elastic::Apm::Util;

struct Snapshot
{
    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Snapshot );

    Snapshot() = default;

    bool enabled = false;
    String serverUrl;
    String serviceName;

//    Log::Level logLevel = Log::Level::off;
//    String logFile;
};

using PSnapshot = std::shared_ptr< const Snapshot >;

} } } } // namespace Elastic::Apm::Impl::Config
