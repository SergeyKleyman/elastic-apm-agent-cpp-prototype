#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::unique_ptr
#include "TestUtil/TracerUnderTestBuilder.hxx"

namespace ElasticApmTests { namespace TestUtil
{

class DefaultFixture
{
public:

    using PTracerUnderTestBuilder = std::unique_ptr< TracerUnderTestBuilder >;

    static PTracerUnderTestBuilder createTracerUnderTestBuilder();

private:

};

} } // namespace ElasticApmTests::TestUtil
