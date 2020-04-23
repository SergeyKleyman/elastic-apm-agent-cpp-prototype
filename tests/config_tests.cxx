#include "TestUtil/unit_test_util.hxx"

TEST_SUITE_BEGIN( config_tests ) // NOLINT(cert-err58-cpp)

namespace BoostTestData = boost::unit_test::data;

auto boolValues = BoostTestData::make( { false, true } ); // NOLINT(cert-err58-cpp)

DATA_TEST_CASE( enabled_valid
                , boolValues * boolValues
                , isEnabledOptSet, enabledOptVal ) // NOLINT(cert-err58-cpp)
{
    // Enabled is not true only when option is set and it's value is false
    const bool expectedIsEnabled = ! ( isEnabledOptSet && ! enabledOptVal );

    auto tracerBuilder = createTracerUnderTestBuilder();
    if ( isEnabledOptSet )
    {
        tracerBuilder->mockConfigSource().setCurrentSnapshot( { { "enabled", enabledOptVal ? "TRue" : "FaLSe" } } );
    }
    auto tracer = tracerBuilder->build();
    UT_ASSERT_EQ( tracer->isNoop(), ! expectedIsEnabled );
}

DATA_TEST_CASE( enabled_invalid
                , BoostTestData::make( { "", " ", "a", "abc", "123" } )
                , enabledOptVal ) // NOLINT(cert-err58-cpp)
{
    auto tracerBuilder = createTracerUnderTestBuilder();
    tracerBuilder->mockConfigSource().setCurrentSnapshot( { { "enabled", enabledOptVal } } );
    auto tracer = tracerBuilder->build();
    UT_ASSERT( ! tracer->isNoop() );
}

TEST_SUITE_END() // config_tests // NOLINT(cert-err58-cpp)
