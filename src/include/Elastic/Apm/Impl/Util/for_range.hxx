#pragma once

#define ELASTIC_APM_FOR_RANGE_TYPE( indexVarType, indexVar, rangeBegin, rangeEnd ) \
    for( indexVarType indexVar = rangeBegin ; (indexVar) != rangeEnd ; ++(indexVar) )
/**/

#define ELASTIC_APM_FOR_RANGE( indexVar, rangeBegin, rangeEnd ) \
    ELASTIC_APM_FOR_RANGE_TYPE( unsigned int, indexVar, rangeBegin, rangeEnd )
/**/
