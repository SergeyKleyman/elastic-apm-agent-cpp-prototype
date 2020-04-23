#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Impl/Util/TimeSource.hxx"
#include "Elastic/Apm/Util/pmrAllocateUniqueTypeErasedDeleter.hxx"
#include "Elastic/Apm/Config/EnvVarsRawSnapshotSource.hxx"
#include "Elastic/Apm/Log/CompositeSink.hxx"
#include "Elastic/Apm/Log/defaultSinks.hxx"
#include "Elastic/Apm/Impl/Log/Backend/Manager.hxx"
#include "Elastic/Apm/Impl/Config/initSequenceOptionsMetadata.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"
#include "Elastic/Apm/Impl/Config/Parser.hxx"
#include "Elastic/Apm/Impl/Config/Snapshot.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

using namespace Elastic::Apm;
using namespace Elastic::Apm::Impl::Util;

inline
void fillInDefaultDependencies( /* ref */ TracerDependencies& tracerDependencies )
{
    setToDefaultIfNotProvidedByUser(
            tracerDependencies.timeSource
            , [ & ]()
            {
                return pmrAllocateUniqueTypeErasedDeleter< TimeSource >( tracerDependencies.allocator.get() );
            } );

    setToDefaultIfNotProvidedByUser(
            tracerDependencies.logSink
            , [ & ]()
            {
                return Apm::Log::CompositeSink::create( Apm::Log::defaultSinks( tracerDependencies.allocator.get() )
                                                        , tracerDependencies.allocator.get() );
            } );

    setToDefaultIfNotProvidedByUser(
            tracerDependencies.configSource
            , [ & ]()
            {
                return Config::createDefaultPrefixEnvVarsRawSnapshotSource( tracerDependencies.allocator.get() );
            } );
}

inline
Config::PSnapshot parseInitSequenceOptions( const TracerDependencies& tracerDependencies )
{
    Log::Backend::Manager tempLogBackendManager{ tracerDependencies.allocator.get()
                                                 , tracerDependencies.timeSource.get()->systemClock()
                                                 , *tracerDependencies.logSink.get() };

    AmbientContextRoot ambientContextRoot{ tracerDependencies.allocator.get()
                                   , tempLogBackendManager.loggerFactory() };

    AmbientContext ambientContext{ ambientContextRoot, /* fqClassName */ String::fromLiteral( __func__ ) };

    Config::Parser< Config::Snapshot > configParser{ Config::initSequenceOptionsMetadata( ambientContext )
                                                     , ambientContext };

    return configParser.parse( *tracerDependencies.configSource.get()->currentSnapshot() );
}

inline
Config::PSnapshot initSequence( /* ref */ TracerDependencies& tracerDependencies )
{
    fillInDefaultDependencies( /* out */ tracerDependencies );
    return parseInitSequenceOptions( tracerDependencies );
}

} } } // namespace Elastic::Apm::Impl
