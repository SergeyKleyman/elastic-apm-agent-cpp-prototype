#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Util/StringView.hxx"

TEST_SUITE_BEGIN( StringView_tests ) // NOLINT(cert-err58-cpp)

TEST_CASE( literalToView_test ) // NOLINT(cert-err58-cpp)
{
    using Elastic::Apm::Util::literalToView;

    UT_ASSERT_EQ( literalToView( "" ).begin(), "" );
    UT_ASSERT_EQ( literalToView( "a" ).begin(), "a" );
    UT_ASSERT_EQ( literalToView( "abc" ).begin(), "abc" );
}

TEST_SUITE_END() // StringView_tests // NOLINT(cert-err58-cpp)
