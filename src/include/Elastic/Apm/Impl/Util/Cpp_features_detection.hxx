#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/current_function.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection_pragma.hxx"
#include "Elastic/Apm/Impl/Util/compilation_config.hxx"

#ifdef __has_cpp_attribute
#   define ELASTIC_APM_HAS_CPP_ATTRIBUTE( attr ) __has_cpp_attribute( attr )
#else
#   define ELASTIC_APM_HAS_CPP_ATTRIBUTE( attr ) (0)
#endif


////////////////////////////////////////////////////////////////////////////////
//
// ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE - [[nodiscard]]
//

#ifndef ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    // clang-6 accepts [[nodiscard]] with -std=c++14, but warns about it -pedantic
#   if ELASTIC_APM_HAS_CPP_ATTRIBUTE( nodiscard ) && ! ( defined( __clang__ ) && ( __cplusplus < 201703L ) )
#       define ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE [[nodiscard]]
#   elif defined( __clang__ )  // deliberately not GCC
#       define ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE __attribute__(( warn_unused_result ))
#   elif defined( _MSC_VER ) // Visual C++
// _Must_inspect_result_ expands into this
#       define ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE \
          __declspec("SAL_name" \
                     "(" \
                     "\"_Must_inspect_result_\"" \
                     "," \
                     "\"\"" \
                     ","  \
                     "\"2\"" \
                     ")") __declspec("SAL_begin") __declspec("SAL_post") __declspec("SAL_mustInspect") __declspec("SAL_post") __declspec("SAL_checkReturn") __declspec("SAL_end")
#   else
#       define ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
#   endif
#endif
//
// ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE - [[nodiscard]]
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME
//

#define ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME BOOST_CURRENT_FUNCTION

//
// ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME
//
////////////////////////////////////////////////////////////////////////////////
