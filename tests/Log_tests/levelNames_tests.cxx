#include "TestUtil/unit_test_util.hxx"

TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)

TEST_CASE( levelNames_test ) // NOLINT(cert-err58-cpp)
{
    using namespace Elastic::Apm::Log;
    using namespace Elastic::Apm::Util;

    UT_ASSERT_EQ( *levelName( Level::off ), literalToView( "OFF" ) );
    UT_ASSERT_EQ( *levelName( Level::critical ), literalToView( "CRITICAL" ) );
    UT_ASSERT_EQ( *levelName( Level::error ), literalToView( "ERROR" ) );
    UT_ASSERT_EQ( *levelName( Level::warning ), literalToView( "WARNING" ) );
    UT_ASSERT_EQ( *levelName( Level::notice ), literalToView( "NOTICE" ) );
    UT_ASSERT_EQ( *levelName( Level::info ), literalToView( "INFO" ) );
    UT_ASSERT_EQ( *levelName( Level::debug ), literalToView( "DEBUG" ) );
    UT_ASSERT_EQ( *levelName( Level::trace ), literalToView( "TRACE" ) );
    UT_ASSERT_EQ( *levelName( Level::all ), literalToView( "ALL" ) );

    UT_ASSERT( ! levelName( static_cast< Level >( static_cast< uint8_t >( Level::all ) + 1 ) ) );
    UT_ASSERT( ! levelName( static_cast< Level >( static_cast< uint8_t >( Level::all ) + 10 ) ) );
}

TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)
