#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Impl/streamToLogImpl.hxx"

TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)
TEST_SUITE_BEGIN( HasStreamToLogImpl_tests ) // NOLINT(cert-err58-cpp)

using namespace Elastic::Apm::Impl::Log;
using namespace ElasticApmTests::TestUtil;

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCUnusedStructInspection"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

static_assert( HasStreamToLogImpl< bool >::value, "" );
static_assert( HasStreamToLogImpl< int >::value, "" );
static_assert( HasStreamToLogImpl< const intmax_t& >::value, "" );
static_assert( HasStreamToLogImpl< const volatile unsigned long long& >::value, "" );
static_assert( HasStreamToLogImpl< float >::value, "" );
static_assert( HasStreamToLogImpl< double >::value, "" );
static_assert( HasStreamToLogImpl< const String& >::value, "" );
static_assert( HasStreamToLogImpl< const StringView& >::value, "" );

static_assert( HasStreamToLogImpl< decltype( "" ) >::value, "" );
static_assert( HasStreamToLogImpl< decltype( "1" ) >::value, "" );
static_assert( HasStreamToLogImpl< decltype( "abc" ) >::value, "" );
static_assert( HasStreamToLogImpl < char( & ) [1] >::value, "" );
static_assert( HasStreamToLogImpl< char[1] >::value, "" );

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

TEST_SUITE_END() // HasStreamToLogImpl_tests // NOLINT(cert-err58-cpp)
TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)
