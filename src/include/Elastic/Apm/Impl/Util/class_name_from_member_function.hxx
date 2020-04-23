#pragma once

#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx"
#include "Elastic/Apm/Util/String.hxx"

#define ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION \
    Elastic::Apm::Util::String::fromLiteral( ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME )
/**/
