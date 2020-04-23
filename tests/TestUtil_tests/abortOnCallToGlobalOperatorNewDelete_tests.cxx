#include "TestUtil/unit_test_util.hxx"
#include "TestUtil/abortOnCallToGlobalOperatorNewDelete.hxx"
#include "Elastic/Apm/Impl/Util/repeat_n_times.hxx"

TEST_SUITE_BEGIN( abortOnCallToGlobalOperatorNewDelete_tests ) // NOLINT(cert-err58-cpp)

using namespace ElasticApmTests::TestUtil;

// TODO: Sergey Kleyman: Uncomment
//TEST_CASE( various_allocations ) // NOLINT(cert-err58-cpp)
//{
//    auto test = []( const char* dbgAllocatingCallName, const std::function< void() >& allocatingCall )
//    {
//        bool wereCallsToGlobalOperatorNewDelete = false;
//        {
//            AbortOnCallToGlobalOperatorNewDeleteGuard abortOnCallToGlobalOperatorNewDeleteGuard{ /* shouldAbort: */ true, [ & ]()
//            {
//                wereCallsToGlobalOperatorNewDelete = true;
//            } };
//
//            allocatingCall();
//        }
//
//        UT_ASSERT( wereCallsToGlobalOperatorNewDelete );
//        UT_ASSERT_MSG( wereCallsToGlobalOperatorNewDelete, dbgAllocatingCallName );
//    };
//
//    test( "make_unique", []()
//          {
//              auto p = std::make_unique< char >();
//              UT_ASSERT_NE( p, nullptr );
//          } );
//
//    test( "PmrVector of 100 ints", []()
//          {
//              auto vec = PmrVector< int >();
//              ELASTIC_APM_REPEAT_N_TIMES_VAR_TYPE( int, i, 100 ) vec.push_back( i );
//              UT_ASSERT_EQ( vec.size(), 100 );
//          } );
//}

TEST_SUITE_END() // abortOnCallToGlobalOperatorNewDelete_tests // NOLINT(cert-err58-cpp)
