#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Util/String.hxx"

TEST_SUITE_BEGIN( String_tests ) // NOLINT(cert-err58-cpp)

using namespace Elastic::Apm::Util;

TEST_CASE( asView_test ) // NOLINT(cert-err58-cpp)
{
    UT_ASSERT_EQ( String().view().length(), 0 );
    UT_ASSERT_EQ( String::fromLiteral( "" ).view().begin(), "" );
    UT_ASSERT_EQ( String::fromLiteral( "abc" ).view().begin(), "abc" );
}

TEST_CASE( PmrString_to_String ) // NOLINT(cert-err58-cpp)
{
    UT_ASSERT_EQ( String( PmrString( "" ) ).view().length(), 0 );
    UT_ASSERT_EQ( String( PmrString( "abc" ) ).view().length(), 3 );
}

TEST_SUITE_END() // StringView_tests // NOLINT(cert-err58-cpp)
