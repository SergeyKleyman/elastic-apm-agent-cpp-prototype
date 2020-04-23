#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_method.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_HAS_PRAGMA_CLANG

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-pragmas"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#endif

TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)
TEST_SUITE_BEGIN( Has_streamToLogImpl_method_tests ) // NOLINT(cert-err58-cpp)

using namespace Elastic::Apm::Impl::Log;

static_assert( ! Has_streamToLogImpl_method< int >::value, "" );
static_assert( ! Has_streamToLogImpl_method< float >::value, "" );
static_assert( ! Has_streamToLogImpl_method< void >::value, "" );

class MyClass_with_correct_streamToLogImpl_method
{
public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool streamToLogImpl( IStream& ) const;
};

static_assert( Has_streamToLogImpl_method< MyClass_with_correct_streamToLogImpl_method >::value, "" );
static_assert( Has_streamToLogImpl_method< MyClass_with_correct_streamToLogImpl_method& >::value, "" );
static_assert( Has_streamToLogImpl_method< const MyClass_with_correct_streamToLogImpl_method& >::value, "" );
static_assert( Has_streamToLogImpl_method< volatile MyClass_with_correct_streamToLogImpl_method& >::value, "" );
static_assert( ! Has_streamToLogImpl_method< MyClass_with_correct_streamToLogImpl_method* >::value, "" );
static_assert( ! Has_streamToLogImpl_method< const MyClass_with_correct_streamToLogImpl_method* >::value, "" );

static_assert( HasStreamToLogImpl< MyClass_with_correct_streamToLogImpl_method >::value, "" );
static_assert( HasStreamToLogImpl< const volatile MyClass_with_correct_streamToLogImpl_method& >::value, "" );

class MyClass_with_correct_static_streamToLogImpl_method
{
public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( IStream& );
};

static_assert( Has_streamToLogImpl_method< MyClass_with_correct_static_streamToLogImpl_method >::value, "" );
static_assert( Has_streamToLogImpl_method< MyClass_with_correct_static_streamToLogImpl_method& >::value, "" );
static_assert( Has_streamToLogImpl_method< const MyClass_with_correct_static_streamToLogImpl_method& >::value, "" );
static_assert( Has_streamToLogImpl_method< volatile MyClass_with_correct_static_streamToLogImpl_method& >::value, "" );
static_assert( ! Has_streamToLogImpl_method< MyClass_with_correct_static_streamToLogImpl_method* >::value, "" );
static_assert( ! Has_streamToLogImpl_method< const MyClass_with_correct_static_streamToLogImpl_method* >::value, "" );

static_assert( HasStreamToLogImpl< MyClass_with_correct_static_streamToLogImpl_method >::value, "" );
static_assert( HasStreamToLogImpl< const volatile MyClass_with_correct_static_streamToLogImpl_method& >::value, "" );

class MyClass_with_no_params_streamToLogImpl_method
{
public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool streamToLogImpl() const;
};

static_assert( ! Has_streamToLogImpl_method< MyClass_with_no_params_streamToLogImpl_method >::value, "" );

class MyClass_return_void_streamToLogImpl_method
{
public:

    void streamToLogImpl( IStream& ) const; // return type is void instead of bool
};

static_assert( ! Has_streamToLogImpl_method< MyClass_return_void_streamToLogImpl_method >::value, "" );

class MyClass_return_not_bool_streamToLogImpl_method
{
public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    int streamToLogImpl( IStream& ) const;
};

static_assert( ! Has_streamToLogImpl_method< MyClass_return_not_bool_streamToLogImpl_method >::value, "" );

class MyClass_streamToLogImpl_not_const_method
{
public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool streamToLogImpl( IStream& ) /* const */;
};

static_assert( ! Has_streamToLogImpl_method< MyClass_streamToLogImpl_not_const_method >::value, "" );

struct DifferentLogStream
{
};

class MyClass_with_DifferentLogStream_streamToLogImpl_method
{
public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool streamToLogImpl( DifferentLogStream& ) const;
};

static_assert( ! Has_streamToLogImpl_method< MyClass_with_DifferentLogStream_streamToLogImpl_method >::value, "" );

TEST_SUITE_END() // Has_streamToLogImpl_method_tests // NOLINT(cert-err58-cpp)
TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif
