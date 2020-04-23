#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm.hxx"

TEST_SUITE_BEGIN( API_tests ) // NOLINT(cert-err58-cpp)

using Elastic::Apm::TracerBuilder;
using Elastic::Apm::PTracer;

TracerBuilder tracerBuilderForTest()
{
    return TracerBuilder();
}

TEST_CASE( just_build_Tracer ) // NOLINT(cert-err58-cpp)
{
    PTracer tracer = tracerBuilderForTest().build();
}

TEST_SUITE_END() // API_tests // NOLINT(cert-err58-cpp)
