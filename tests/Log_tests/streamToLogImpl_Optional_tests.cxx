#include "TestUtil/unit_test_util.hxx"

TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)
TEST_SUITE_BEGIN( streamToLogImpl_Optional_tests ) // NOLINT(cert-err58-cpp)

using namespace Elastic::Apm::Impl::Log;
using namespace ElasticApmTests::TestUtil;

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCUnusedStructInspection"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

// TODO: Sergey Kleyman: Implement: streamToLogImpl_Optional_tests

static_assert( HasStreamToLogImpl< Optional< int > >::value, "" );

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

TEST_SUITE_END() // streamToLogImpl_pointers_tests // NOLINT(cert-err58-cpp)
TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)
