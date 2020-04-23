#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Util/ArrayView.hxx"

TEST_SUITE_BEGIN( ArrayView_tests ) // NOLINT(cert-err58-cpp)

using namespace Elastic::Apm::Util;

TEST_CASE( construct_ArrayView_from_static_array ) // NOLINT(cert-err58-cpp)
{
    int ar[] = { 0, 1, 2, 3 };
    auto arVw = ArrayView< int >( ar );

    UT_ASSERT_EQ( arVw.size(), 4 );
    UT_ASSERT_EQ( arVw.begin(), &( ar[ 0 ] ) );
}

TEST_CASE( construct_ArrayView_from_begin_size ) // NOLINT(cert-err58-cpp)
{
    int ar[] = { 0, 1, 2, 3, 4, 5 };
    auto arVw = ArrayView< int >( &( ar[ 2 ] ), 2 );

    UT_ASSERT_EQ( arVw.size(), 2 );
    UT_ASSERT_EQ( arVw.begin(), &( ar[ 2 ] ) );
}

TEST_SUITE_END() // ArrayView_tests // NOLINT(cert-err58-cpp)
