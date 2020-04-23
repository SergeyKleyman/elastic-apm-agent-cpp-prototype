#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_HAS_PRAGMA_CLANG

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "OCUnusedMacroInspection"
#endif

#define BOOST_TEST_MODULE Elastic_APM_Cpp_Agent_tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <boost/test/unit_test.hpp>
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"

// entry point:
int main( int argc, char* argv[] )
{
    return boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
}
