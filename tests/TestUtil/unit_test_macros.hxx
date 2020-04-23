#pragma once

#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_HAS_PRAGMA_CLANG
#include "TestUtil/DefaultFixture.hxx"

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "OCUnusedMacroInspection"
#endif

#define BOOST_TEST_DYN_LINK

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic/fwd.hpp>
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"

#define TEST_CASE( testCaseName ) BOOST_FIXTURE_TEST_CASE( testCaseName, ElasticApmTests::TestUtil::DefaultFixture )

#define DATA_TEST_CASE( testCaseName, dataSet, var1, /* var2, ... */ ... ) \
    BOOST_DATA_TEST_CASE_F( ElasticApmTests::TestUtil::DefaultFixture, testCaseName, dataSet, var1 ,##__VA_ARGS__ )
/**/

// #define TEST_CASE_TEMPLATE( test_name, type_name, TL ) BOOST_AUTO_TEST_CASE_TEMPLATE( test_name, type_name, TL )

#define TEST_SUITE_BEGIN( ... ) BOOST_AUTO_TEST_SUITE( __VA_ARGS__ )
#define TEST_SUITE_END() BOOST_AUTO_TEST_SUITE_END()
#define TEST_SUITE_END() BOOST_AUTO_TEST_SUITE_END()

#define UT_ASSERT( cond, /* ctx */ ... ) BOOST_REQUIRE( cond )
#define UT_ASSERT_MSG( cond, /* ctx */ ... ) BOOST_REQUIRE_MESSAGE( cond , ##__VA_ARGS__ )
#define UT_ASSERT_EQ( actual, expected, /* ctx */ ... ) BOOST_REQUIRE_EQUAL( actual, expected )
#define UT_ASSERT_NE( actual, expected, /* ctx */ ... ) BOOST_REQUIRE_NE( actual, expected )
