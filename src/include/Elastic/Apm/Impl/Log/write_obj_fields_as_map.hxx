#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/variadic/to_seq.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/seq/for_each_i.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/stringize.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/tuple/elem.hxx"

#define ELASTIC_APM_WRITE_OBJ_FIELD_WITH_AUTO_NAME( field ) ( BOOST_PP_STRINGIZE( field ), field )

#define ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP_FOR_ONE_FIELD( nameFieldTuple ) \
    { \
        auto fieldValueStream = mapStream->add( BOOST_PP_TUPLE_ELEM( 0, nameFieldTuple ) ); \
        if ( ! fieldValueStream ) return false; \
        \
        if ( ! Elastic::Apm::Impl::Log::streamToLog( BOOST_PP_TUPLE_ELEM( 1, nameFieldTuple ), *fieldValueStream ) ) return false; \
    } \
/**/

#define ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP_FOR_EACH_CALLBACK( reservedByBoostPp, unused_callbackCtx, seqElemIndex, seqElem ) \
    BOOST_PP_IF( \
        seqElemIndex \
        , ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP_FOR_ONE_FIELD( seqElem ) \
        , /**/ ) \
/**/

#define ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP( logStream, /* fields: */ ... ) \
    do { \
        auto mapStream = (logStream).beginMap(); \
        if ( ! mapStream ) return false; \
        \
        BOOST_PP_SEQ_FOR_EACH_I( \
            ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP_FOR_EACH_CALLBACK \
            , unused_callbackCtx \
            , BOOST_PP_VARIADIC_TO_SEQ( dummy_padding /* fields: */ , ##__VA_ARGS__ ) ) \
        \
        if ( ! mapStream->end() ) return false; \
    } while( 0 ) \
/**/
