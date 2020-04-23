#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_via_ADL.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_HAS_PRAGMA_CLANG

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-pragmas"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#endif

TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)
TEST_SUITE_BEGIN( Has_streamToLogImpl_via_ADL_tests ) // NOLINT(cert-err58-cpp)

using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Impl;
using namespace Elastic::Apm::Impl::Log;

static_assert( ! Has_streamToLogImpl_via_ADL< int >::value, "" );
static_assert( ! Has_streamToLogImpl_via_ADL< float >::value, "" );
static_assert( ! Has_streamToLogImpl_via_ADL< void >::value, "" );

enum class MyEnum_with_streamToLogImpl
{
    a,
    b,
};

ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
inline
bool streamToLogImpl( const MyEnum_with_streamToLogImpl& val, IStream& logStream )
{
    return logStream.writeCurrentValueContent( static_cast< int >( val ) );
}

static_assert( Has_streamToLogImpl_via_ADL< MyEnum_with_streamToLogImpl >::value, "" );
static_assert( Has_streamToLogImpl_via_ADL< const MyEnum_with_streamToLogImpl& >::value, "" );

enum class MyEnum_without_streamToLogImpl
{
    a,
    b,
};

static_assert( ! Has_streamToLogImpl_via_ADL< MyEnum_without_streamToLogImpl >::value, "" );
static_assert( ! Has_streamToLogImpl_via_ADL< const MyEnum_without_streamToLogImpl& >::value, "" );

TEST_SUITE_END() // Has_streamToLogImpl_via_ADL_tests // NOLINT(cert-err58-cpp)
TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif
