#pragma once

#include "Elastic/Apm/Impl/Util/Cpp_features_detection_pragma.hxx" // ELASTIC_APM_HAS_PRAGMA_CLANG

#ifdef ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS

#   ifndef ELASTIC_APM_SEPARATE_COMPILATION
#       define ELASTIC_APM_SEPARATE_COMPILATION
#   endif

#if defined ( _MSC_VER ) && defined( ELASTIC_APM_UNDER_IDE )
#   pragma warning( push )
#   pragma warning( disable : 4068 ) // unknown pragma
#endif

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic push
#   pragma ide diagnostic ignored "OCUnusedMacroInspection"
#   pragma ide diagnostic ignored "UnusedMacroInspection"
#endif

#   ifndef ELASTIC_APM_SEPARATE_COMPILATION_BOOST_ASIO
#       define ELASTIC_APM_SEPARATE_COMPILATION_BOOST_ASIO
#       define BOOST_ASIO_SEPARATE_COMPILATION
#   endif

#   ifndef ELASTIC_APM_SEPARATE_COMPILATION_BOOST_BEAST
#       define ELASTIC_APM_SEPARATE_COMPILATION_BOOST_BEAST
#       define BOOST_BEAST_SEPARATE_COMPILATION
#   endif

#if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
#   pragma clang diagnostic pop
#endif

#if defined ( _MSC_VER ) && defined( ELASTIC_APM_UNDER_IDE )
#   pragma warning( pop )
#endif

#endif // #ifdef ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS
