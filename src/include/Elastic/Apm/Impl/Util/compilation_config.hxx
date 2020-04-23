#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config_warnings.hxx"
#include "Elastic/Apm/separate_compilation_config.hxx"

#ifdef ELASTIC_APM_SEPARATE_COMPILATION
#   define ELASTIC_APM_INLINE_FOR_IMPL
#else
#   define ELASTIC_APM_INLINE_FOR_IMPL inline
#endif
