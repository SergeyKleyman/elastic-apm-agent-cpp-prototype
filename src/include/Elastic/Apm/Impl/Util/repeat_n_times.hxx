#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/cat.hxx"

#define ELASTIC_APM_REPEAT_N_TIMES_VAR_TYPE( indexVarType, indexVar, numberOfTimes ) \
    for( indexVarType indexVar = 0 ; indexVar != numberOfTimes ; ++indexVar )
/**/

#define ELASTIC_APM_REPEAT_N_TIMES_VAR( indexVar, numberOfTimes ) \
    ELASTIC_APM_REPEAT_N_TIMES_VAR_TYPE( unsigned int, indexVar, numberOfTimes )
/**/

#define ELASTIC_APM_REPEAT_N_TIMES( numberOfTimes ) \
    ELASTIC_APM_REPEAT_N_TIMES_VAR( BOOST_PP_CAT( elastic_apm_repeat_n_times_dummy_indexVar_, __LINE__ ), numberOfTimes )
/**/
