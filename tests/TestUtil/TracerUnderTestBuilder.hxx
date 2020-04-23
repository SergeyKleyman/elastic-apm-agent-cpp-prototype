#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::shared_ptr
#include "Elastic/Apm/TracerBuilder.hxx"
#include "TestUtil/MockMemoryResource.hxx"
#include "TestUtil/MockRawConfigSnapshotSource.hxx"

namespace ElasticApmTests { namespace TestUtil
{

class TracerUnderTestBuilder
{
public:

    ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( TracerUnderTestBuilder );

    TracerUnderTestBuilder()
        : _mockConfigSource{ std::make_shared< MockRawConfigSnapshotSource >( &_mockMemoryResource ) }
    {
        _tracerBuilder.with( sharedPtrToUniqueTypeErasedDeleter( _mockConfigSource ) );
    }

    MockMemoryResource& mockMemoryResource()
    {
        return _mockMemoryResource;
    }

    MockRawConfigSnapshotSource& mockConfigSource()
    {
        return *_mockConfigSource;
    }

    TracerBuilder& wrappedBuilder()
    {
        return _tracerBuilder;
    }

    PTracer build()
    {
        return _tracerBuilder.build();
    }

private:

    MockMemoryResource _mockMemoryResource;
    std::shared_ptr< MockRawConfigSnapshotSource > _mockConfigSource;
    TracerBuilder _tracerBuilder;
};

} } // namespace ElasticApmTests::TestUtil
