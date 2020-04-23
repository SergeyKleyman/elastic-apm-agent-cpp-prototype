#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::move
#include "Elastic/Apm/TracerBuilder.hxx"
#include "Elastic/Apm/Impl/initSequence.hxx"
#include "Elastic/Apm/Impl/Tracer.hxx"
#include "Elastic/Apm/Impl/NoopTracer.hxx"

namespace Elastic { namespace Apm
{

ELASTIC_APM_INLINE_FOR_IMPL
PTracer TracerBuilder::build()
{
    using namespace Elastic::Apm::Impl;

    auto cfgSnapWithInitSeqOptsOnly = initSequence( /* ref */ _tracerDependencies );

    if ( ! cfgSnapWithInitSeqOptsOnly->enabled )
    {
        return NoopTracer::create( _tracerDependencies.allocator.get() );
    }

    return Tracer::create( std::move( _tracerDependencies ), std::move( cfgSnapWithInitSeqOptsOnly ) );
}

} } // namespace Elastic::Apm
