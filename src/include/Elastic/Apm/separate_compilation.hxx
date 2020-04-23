#pragma once

/**
 * This file is meant to be included once, in a translation unit of
 * the program, with the macro ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS (or just ELASTIC_APM_SEPARATE_COMPILATION) defined.
 */

#include "Elastic/Apm/separate_compilation_config.hxx"

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   error Do not include "Elastic/Apm/separate_compilation.hxx" without defining ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS (or just ELASTIC_APM_SEPARATE_COMPILATION) for the whole project
#endif

#include "Elastic/Apm/Impl/TracerBuilder_impl.hxx"
#include "Elastic/Apm/Impl/Log/Backend/visualFormatContextValue_impl.hxx"
#include "Elastic/Apm/Impl/Log/Backend/RecordVisualFormatter_impl.hxx"
#include "Elastic/Apm/Impl/Log/Backend/Manager_impl.hxx"
#include "Elastic/Apm/Impl/Util/SystemClockTimePoint_toLog_impl.hxx"
#include "Elastic/Apm/Impl/Util/platform_impl.hxx"
#include "Elastic/Apm/Impl/Log/defaultSinks_impl.hxx"

/**
 * https://www.boost.org/doc/libs/1_72_0/doc/html/boost_asio/using.html#boost_asio.using.optional_separate_compilation
 *
 *
 */
#ifdef ELASTIC_APM_SEPARATE_COMPILATION_BOOST_ASIO
#   include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/asio/impl/src.hxx"
#   include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/asio/ssl/impl/src.hxx"
#endif

#ifdef ELASTIC_APM_SEPARATE_COMPILATION_BOOST_BEAST
#   include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/beast/src.hxx"
#endif
