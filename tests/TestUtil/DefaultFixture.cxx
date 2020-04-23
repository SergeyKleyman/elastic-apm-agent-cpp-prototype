#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/smart_ptr/make_unique.hxx"
#include "TestUtil/DefaultFixture.hxx"

namespace ElasticApmTests { namespace TestUtil
{

std::unique_ptr< TracerUnderTestBuilder > DefaultFixture::createTracerUnderTestBuilder()
{
    return boost::make_unique< TracerUnderTestBuilder >();
}

} } // namespace ElasticApmTests::TestUtil
