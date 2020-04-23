#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/TracerDependencies.hxx"
#include "Elastic/Apm/ITracer.hxx"

namespace Elastic { namespace Apm
{

using Impl::PLogSink;
using Util::PmrByteAllocator;
using Impl::PRawConfigSnapshotSource;
using Impl::PTimeSource;
using Impl::PEventSink;

class TracerBuilder
{
public:

    ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( TracerBuilder );

    TracerBuilder() = default;

    TracerBuilder& with( const PmrByteAllocator& allocator )
    {
        _tracerDependencies.allocator.set( allocator, /* isProvided: */ true );
        return *this;
    }

    TracerBuilder& with( PLogSink logSink )
    {
        _tracerDependencies.logSink.set( std::move( logSink ), /* isProvided: */ true );
        return *this;
    }

    TracerBuilder& with( PRawConfigSnapshotSource configSource )
    {
        _tracerDependencies.configSource.set( std::move( configSource ), /* isProvided: */ true );
        return *this;
    }

    TracerBuilder& with( PTimeSource timeSource )
    {
        _tracerDependencies.timeSource.set( std::move( timeSource ), /* isProvided: */ true );
        return *this;
    }

    TracerBuilder& with( PEventSink eventSink )
    {
        _tracerDependencies.eventSink.set( std::move( eventSink ), /* isProvided: */ true );
        return *this;
    }

    PTracer build();

private:

    Impl::TracerDependencies _tracerDependencies;
};

} } // namespace Elastic::Apm

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   include "Elastic/Apm/Impl/TracerBuilder_impl.hxx"
#endif
