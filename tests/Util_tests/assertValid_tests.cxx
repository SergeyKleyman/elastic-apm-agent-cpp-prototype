#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Impl/Util/assertValid.hxx"
#include "Elastic/Apm/Impl/initSequence.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/smart_ptr/make_unique.hxx"

TEST_SUITE_BEGIN( assertValid_tests ) // NOLINT(cert-err58-cpp)

using namespace Elastic::Apm::Impl;
using namespace Elastic::Apm::Impl::Util;
using namespace ElasticApmTests::TestUtil;

class MockAmbientContextRoot
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( MockAmbientContextRoot );

    explicit MockAmbientContextRoot( TracerDependencies tracerDependencies, AssertLevel assertLevel )
            : _tracerDependencies{ std::move( tracerDependencies ) }
              , _logBackendManager{ _tracerDependencies.allocator.get()
                                   , _tracerDependencies.timeSource.get()->systemClock()
                                   , *_tracerDependencies.logSink.get() }
              , _root{ _tracerDependencies.allocator.get(), _logBackendManager.loggerFactory(), assertLevel }
    {}

    const AmbientContextRoot& root() const
    {
        return _root;
    }

private:

    TracerDependencies _tracerDependencies;
    Backend::Manager _logBackendManager;
    AmbientContextRoot _root;
};

std::unique_ptr< MockAmbientContextRoot > createMockAmbientContextRoot( AssertLevel assertLevel )
{
    TracerDependencies tracerDependencies;

    tracerDependencies.configSource.set(
            pmrAllocateUniqueTypeErasedDeleter< MockRawConfigSnapshotSource >(
                    tracerDependencies.allocator.get()
                    , tracerDependencies.allocator.get() )
            , /* isProvided: */ true );

    initSequence( /* ref */ tracerDependencies );
    return boost::make_unique< MockAmbientContextRoot >( std::move( tracerDependencies ), assertLevel );
}

class MyClass_with_assertValidImpl_method
{
public:

    mutable unsigned int assertValidImplCallCount = 0;

    #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
    #   pragma clang diagnostic push
    #   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
    #endif

    void assertValidImpl( const AmbientContext& /* ambCtx */ ) const
    {
        ++assertValidImplCallCount;
    }

    #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
    #   pragma clang diagnostic pop
    #endif
};

class MyClass_with_assertValidImpl_via_ADL
{
public:

    mutable unsigned int assertValidImplCallCount = 0;
};

inline
void assertValidImpl( const AmbientContext& /* ambCtx */ , const MyClass_with_assertValidImpl_via_ADL& obj )
{
    ++obj.assertValidImplCallCount;
}

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "NotImplementedFunctions"
#   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#   pragma ide diagnostic ignored "OCUnusedStructInspection"
#   pragma ide diagnostic ignored "OCSimplifyInspection"
#endif

static_assert( ! HasAssertValidImpl< void >::value, "" );
static_assert( ! HasAssertValidImpl< bool >::value, "" );
static_assert( ! HasAssertValidImpl< int >::value, "" );
static_assert( ! HasAssertValidImpl< const int& >::value, "" );
static_assert( HasAssertValidImpl< void* >::value, "" );
static_assert( HasAssertValidImpl< const void* >::value, "" );
static_assert( HasAssertValidImpl< int* >::value, "" );
static_assert( HasAssertValidImpl< const int* >::value, "" );
static_assert( HasAssertValidImpl< const int [] >::value, "" );

static_assert( HasAssertValidImpl< MyClass_with_assertValidImpl_method >::value, "" );
static_assert( HasAssertValidImpl< const MyClass_with_assertValidImpl_method& >::value, "" );
static_assert( HasAssertValidImpl< MyClass_with_assertValidImpl_method* >::value, "" );
static_assert( HasAssertValidImpl< const MyClass_with_assertValidImpl_method* >::value, "" );
static_assert( HasAssertValidImpl< MyClass_with_assertValidImpl_method[] >::value, "" );
static_assert( HasAssertValidImpl< const MyClass_with_assertValidImpl_method[] >::value, "" );
static_assert( HasAssertValidImpl< MyClass_with_assertValidImpl_method** >::value, "" );

static_assert( HasAssertValidImpl< MyClass_with_assertValidImpl_via_ADL >::value, "" );
static_assert( HasAssertValidImpl< const MyClass_with_assertValidImpl_via_ADL& >::value, "" );
static_assert( HasAssertValidImpl< MyClass_with_assertValidImpl_via_ADL* >::value, "" );
static_assert( HasAssertValidImpl< const MyClass_with_assertValidImpl_via_ADL* >::value, "" );
static_assert( HasAssertValidImpl< const MyClass_with_assertValidImpl_via_ADL (&)[] >::value, "" );

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

TEST_CASE( assertValidImpl_method ) // NOLINT(cert-err58-cpp)
{
    auto mockAmbientContextRoot = createMockAmbientContextRoot( AssertLevel::O_1 );
    AmbientContext _ambientContext{ mockAmbientContextRoot->root(), String::fromLiteral( "dummy_class_name" ) };
    MyClass_with_assertValidImpl_method obj;
    UT_ASSERT_EQ( obj.assertValidImplCallCount, 0 );

    ELASTIC_APM_ASSERT_VALID( obj );

    UT_ASSERT_EQ( obj.assertValidImplCallCount, 1 );

    ELASTIC_APM_ASSERT_VALID( &obj );

    UT_ASSERT_EQ( obj.assertValidImplCallCount, 2 );
}

TEST_CASE( assertValidImpl_via_ADL ) // NOLINT(cert-err58-cpp)
{
    auto mockAmbientContextRoot = createMockAmbientContextRoot( AssertLevel::O_1 );
    AmbientContext _ambientContext{ mockAmbientContextRoot->root(), String::fromLiteral( "dummy_class_name" ) };
    MyClass_with_assertValidImpl_via_ADL obj;

    #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
    #   pragma clang diagnostic push
    #   pragma clang diagnostic ignored "-Wuninitialized"
    #endif

    UT_ASSERT_EQ( obj.assertValidImplCallCount, 0 );

    ELASTIC_APM_ASSERT_VALID( obj );

    UT_ASSERT_EQ( obj.assertValidImplCallCount, 1 );

    #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
    #   pragma clang diagnostic pop
    #endif
}

TEST_SUITE_END() // assertValid_tests // NOLINT(cert-err58-cpp)
