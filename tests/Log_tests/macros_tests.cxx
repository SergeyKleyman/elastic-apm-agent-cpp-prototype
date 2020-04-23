#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Impl/Log/macros.hxx"
#include "TestUtil/MockMemoryResource.hxx"
#include "TestUtil/MockLogger.hxx"
#include "TestUtil/abortOnCallToGlobalOperatorNewDelete.hxx"

TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)
TEST_SUITE_BEGIN( macros_tests ) // NOLINT(cert-err58-cpp)

using namespace ElasticApmTests::TestUtil;

#define TEST_CAPTURE_SOURCE_CODE_LOCATION( srcCodeLoc ) \
    do { \
        (srcCodeLoc).filePath = String::fromLiteral( __FILE__ ); \
        (srcCodeLoc).lineNumber = __LINE__; \
        (srcCodeLoc).ppFqFunction = String::fromLiteral( ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME ); \
        (srcCodeLoc).ppFunction = String::fromLiteral( __FUNCTION__ ); \
        (srcCodeLoc).cppFunc = String::fromLiteral( __func__ ); \
    } while ( 0 ) \
    /**/

inline
void assertSourceCodeLocationsEqual( const MockLogRecord::SourceCodeLocation& actual
                                     , const MockLogRecord::SourceCodeLocation& expected
)
{
    UT_ASSERT_EQ( actual.filePath, expected.filePath );
    UT_ASSERT_EQ( actual.lineNumber, expected.lineNumber );
    UT_ASSERT_EQ( actual.ppFqFunction, expected.ppFqFunction );
    UT_ASSERT_EQ( actual.ppFunction, expected.ppFunction );
    UT_ASSERT_EQ( actual.cppFunc, expected.cppFunc );
    UT_ASSERT_EQ( actual.fqClassName, expected.fqClassName );
}

class MockAmbientContextWithLogger
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( MockAmbientContextWithLogger );

    explicit MockAmbientContextWithLogger( MockMemoryResource& testMemResource )
        : _logger{ PmrByteAllocator{ &testMemResource } }
    {}

    MockLogger& logger()
    {
        return _logger;
    }

private:

    MockLogger _logger;
};

TEST_CASE( without_context_expressions ) // NOLINT(cert-err58-cpp)
{
    MockMemoryResource testMemResource;
    MockAmbientContextWithLogger _ambientContext{ testMemResource };

    {
        MockLogRecord::SourceCodeLocation expectedSrcCodeLoc;
        {
            AbortOnCallToGlobalOperatorNewDeleteGuard abortOnCallToGlobalOperatorNewDeleteGuard{ /* shouldAbort: */ true };
            ELASTIC_APM_LOG_CRITICAL( "Test message" ); TEST_CAPTURE_SOURCE_CODE_LOCATION( expectedSrcCodeLoc );
        }
        auto records{ _ambientContext.logger().takeRecords() };
        UT_ASSERT_EQ( records.size(), 1 );
        UT_ASSERT_EQ( records[ 0 ]->level, Level::critical );
        assertSourceCodeLocationsEqual( records[ 0 ]->sourceCodeLocation, expectedSrcCodeLoc );
        UT_ASSERT_EQ( records[ 0 ]->message, "Test message" );
    }
}

// TODO: Sergey Kleyman: Uncomment macros_tests.cxx

//    TEST_CASE( without_any_context ) // NOLINT(cert-err58-cpp)
//    {
//        MockMemoryResource testMemResource;
//        MockLogger logger{ PmrByteAllocator{ &testMemResource } };
//
//        {
//            v1_RecordView::SourceCodeLocation srcCodeLoc;
//            {
//                AbortOnCallToGlobalOperatorNewDeleteGuard abortOnCallToGlobalOperatorNewDeleteGuard{ /* shouldAbort: */ true };
//                ELASTIC_APM_LOG_CRITICAL( logger, "Test message" ); TEST_CAPTURE_SOURCE_CODE_LOCATION( srcCodeLoc );
//            }
//            auto records{ logger.takeRecords() };
//            UT_ASSERT_EQ( records.size(), 1 );
//            UT_ASSERT_EQ( records[ 0 ]->level, Level::critical );
//            assertSourceCodeLocationsEqual( records[ 0 ]->sourceCodeLocation, srcCodeLoc );
//            UT_ASSERT( ! records[ 0 ]->message.ownsStorage() );
//            UT_ASSERT_EQ( records[ 0 ]->message.view(), "Test message" );
//        }
//
//        {
//            v1_RecordView::SourceCodeLocation srcCodeLoc;
//            execAbortingOnCallToGlobalOperatorNewDelete(
//                    [ & ]()
//                    {
//                        ELASTIC_APM_LOG_CRITICAL( logger, "Test message" ); TEST_CAPTURE_SOURCE_CODE_LOCATION( srcCodeLoc ); // NOLINT(bugprone-lambda-function-name)
//                    } );
//            auto records{ logger.takeRecords() };
//            UT_ASSERT_EQ( records.size(), 1 );
//            UT_ASSERT_EQ( records[ 0 ]->level, Level::critical );
//            assertSourceCodeLocationsEqual( records[ 0 ]->sourceCodeLocation, srcCodeLoc );
//            UT_ASSERT( ! records[ 0 ]->message.ownsStorage() );
//            UT_ASSERT_EQ( records[ 0 ]->message.view(), "Test message" );
//        }
//    }
//
//    // TODO: Sergey Kleyman: Uncomment
//    //TEST_CASE( one_element_context ) // NOLINT(cert-err58-cpp)
//    //{
//    //    MockLogger logger;
//    //    int i = 123;
//    //    ELASTIC_APM_LOG_CRITICAL( logger, "Test message", i );
//    //
//    //    UT_ASSERT( true );
//    //}
//    //
//    //TEST_CASE( two_element_context ) // NOLINT(cert-err58-cpp)
//    //{
//    //    MockLogger logger;
//    //    const char s1[] = "abc";
//    //    std::string s2 = "def";
//    //    ELASTIC_APM_LOG_CRITICAL( logger, "Test message", s1, s1 + s2 );
//    //
//    //    UT_ASSERT( true );
//    //}
//
//    TEST_CASE( non_literal_string_as_message ) // NOLINT(cert-err58-cpp)
//    {
//    //    MockMemoryResource testMemResource;
//    //    MockLogger logger{ PmrByteAllocator{ &testMemResource } };
//    //    constexpr std::size_t messageBufferSize = 100;
//    //    char messageBuffer[ messageBufferSize ];
//    //
//    //    {
//    //        {
//    //            AbortOnCallToGlobalOperatorNewDeleteGuard abortOnCallToGlobalOperatorNewDeleteGuard{ /* shouldAbort: */ true };
//    //            ELASTIC_APM_LOG_CRITICAL( logger, "Test message" );
//    //        }
//    //        auto records{ logger.takeRecords() };
//    //        UT_ASSERT_EQ( records.size(), 1 );
//    //        UT_ASSERT_EQ( records[ 0 ]->level, Level::critical );
//    //        UT_ASSERT( ! records[ 0 ]->message.ownsStorage() );
//    //        UT_ASSERT_EQ( records[ 0 ]->message.view(), "Test message" );
//    //    }
//    }

TEST_SUITE_END() // macros_tests // NOLINT(cert-err58-cpp)
TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)
