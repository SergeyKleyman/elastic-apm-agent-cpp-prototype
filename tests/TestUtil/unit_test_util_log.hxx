// TODO: Sergey Kleyman: Uncomment

//    #pragma once
//
//    #include "unit_test_util_allocator.hxx"
//    #include "Elastic/Apm/Impl/Log/Logger.hxx"
//    #include "TestUtil/MockLogger.hxx"
//    #include "unit_test_macros.hxx"
//
//    namespace ElasticApmTests { namespace TestUtil
//    {
//
//    using namespace Elastic::Apm::Impl::Log;
//
//    // TODO: Sergey Kleyman: Remove streamToLogRecordContextValueForTest if I don't need it anymore
//    template< typename T >
//    v1_RecordContextValue streamToLogRecordContextValueForTest( const T& t )
//    {
//        auto logger = MockLogger{ allocatorUsingGlobalNewDelete() };
//        return toValue_via_streamToLog( t, logger );
//    }
//
//    // TODO: Sergey Kleyman: Move to appropriate ???_tests.cxx
//    inline
//    void assertSourceCodeLocationsEqual( const v1_RecordView::SourceCodeLocation& actual, const v1_RecordView::SourceCodeLocation& expected )
//    {
//        UT_ASSERT_EQ( actual.filePath, expected.filePath );
//        UT_ASSERT_EQ( actual.lineNumber, expected.lineNumber );
//        UT_ASSERT_EQ( actual.ppFqFunction, expected.ppFqFunction );
//        UT_ASSERT_EQ( actual.ppFunction, expected.ppFunction );
//        UT_ASSERT_EQ( actual.cppFunc, expected.cppFunc );
//    }
//
//    } } // namespace ElasticApmTests::TestUtil
