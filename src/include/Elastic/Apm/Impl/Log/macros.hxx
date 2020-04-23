#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::move
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/variadic/to_seq.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/seq/for_each_i.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/control/if.hxx"
#include "Elastic/Apm/Log/RecordDataRefs.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME
#include "Elastic/Apm/Impl/streamToLogImpl.hxx"
#include "Elastic/Apm/Impl/Log/TypeErasedStreamable.hxx"
#include "Elastic/Apm/Impl/Log/BareTypeToLog.hxx"

#define ELASTIC_APM_LOG_IMPL_FILL_SOURCE_CODE_LOCATION( recSrcCodeLoc ) \
    , (recSrcCodeLoc).filePath = __FILE__ \
    , (recSrcCodeLoc).lineNumber = __LINE__ \
    , (recSrcCodeLoc).ppFqFunction = ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME \
    , (recSrcCodeLoc).ppFunction = __FUNCTION__ \
    , (recSrcCodeLoc).cppFunc = __func__ \
/**/

#define ELASTIC_APM_LOG_IMPL_FILL_CONTEXT_EXPRS_ELEMENT( exprIndex, expr ) \
    +(( elasticApmLogRecordDataRefsCtxExprs[ exprIndex - 1 ] = \
        Elastic::Apm::Log::RecordDataRefs::ContextExpr \
        { \
            Elastic::Apm::Util::literalToView( #expr ) \
            , Elastic::Apm::Impl::Log::makeTypeErasedStreamable( expr ) \
        } ), 0) \
/**/

#define ELASTIC_APM_LOG_IMPL_FILL_CONTEXT_EXPRS_FOR_EACH_CALLBACK( reservedByBoostPp, unused_callbackCtx, seqElemIndex, seqElem ) \
    BOOST_PP_IF( \
        seqElemIndex \
        , ELASTIC_APM_LOG_IMPL_FILL_CONTEXT_EXPRS_ELEMENT( seqElemIndex, seqElem ) \
        , /**/ ) \
/**/

#define ELASTIC_APM_LOG_IMPL_FILL_CONTEXT_EXPRS( padding_ctxExprs_seq ) \
    , 0 \
    BOOST_PP_SEQ_FOR_EACH_I( \
        ELASTIC_APM_LOG_IMPL_FILL_CONTEXT_EXPRS_FOR_EACH_CALLBACK \
        , unused_callbackCtx \
        , padding_ctxExprs_seq ) \
/**/

#define ELASTIC_APM_LOG_IMPL_COUNT_CONTEXT_EXPRS_FOR_EACH_CALLBACK( reservedByBoostPp, unused_callbackCtx, seqElemIndex, unused_seqElem ) \
    BOOST_PP_IF( \
        seqElemIndex \
        , +1 \
        , /**/ ) \
/**/

#define ELASTIC_APM_LOG_IMPL_COUNT_CONTEXT_EXPRS( padding_ctxExprs_seq ) \
    BOOST_PP_SEQ_FOR_EACH_I( \
        ELASTIC_APM_LOG_IMPL_COUNT_CONTEXT_EXPRS_FOR_EACH_CALLBACK \
        , unused_callbackCtx \
        , padding_ctxExprs_seq ) \
/**/

#define ELASTIC_APM_LOG_IMPL_DEFINE_TEMP_VARS( padding_ctxExprs_seq ) \
    constexpr unsigned int elasticApmLogRecordDataRefsCtxExprsCount = \
        ELASTIC_APM_LOG_IMPL_COUNT_CONTEXT_EXPRS( padding_ctxExprs_seq ) + 0; \
    \
    Elastic::Apm::Log::RecordDataRefs::ContextExpr \
        elasticApmLogRecordDataRefsCtxExprs[ \
            elasticApmLogRecordDataRefsCtxExprsCount == 0 \
            ? 1 \
            : elasticApmLogRecordDataRefsCtxExprsCount ]; \
    \
    Elastic::Apm::Log::RecordDataRefs elasticApmLogRecordDataRefs{ \
        Elastic::Apm::Util::ArrayView< Elastic::Apm::Log::RecordDataRefs::ContextExpr >{ \
            &( elasticApmLogRecordDataRefsCtxExprs[ 0 ] ) \
            , elasticApmLogRecordDataRefsCtxExprsCount } }; \
/**/

#define ELASTIC_APM_LOG_WITH_LEVEL_IMPL( ambCtx, statementLevel, msg, padding_ctxExprs_seq ) \
    do { \
        if ( (ambCtx).logger().isEnabled( statementLevel ) ) \
        { \
            ELASTIC_APM_LOG_IMPL_DEFINE_TEMP_VARS( padding_ctxExprs_seq ) \
            \
            (ambCtx).logger().consume \
            (( \
                ( \
                    elasticApmLogRecordDataRefs.level = (statementLevel) \
                    \
                    ELASTIC_APM_LOG_IMPL_FILL_SOURCE_CODE_LOCATION( elasticApmLogRecordDataRefs.sourceCodeLocation ) \
                    \
                    , elasticApmLogRecordDataRefs.message = ( msg ) \
                    \
                    ELASTIC_APM_LOG_IMPL_FILL_CONTEXT_EXPRS( padding_ctxExprs_seq ) \
                    \
                ) \
                , std::move( elasticApmLogRecordDataRefs ) \
            )); \
        } \
    } while ( 0 ) \
/**/

#define ELASTIC_APM_LOG_WITH_LEVEL( ambCtx, statementLevel, msg, /* ctxExprs: */ ... ) \
    ELASTIC_APM_LOG_WITH_LEVEL_IMPL( ambCtx, statementLevel, msg, BOOST_PP_VARIADIC_TO_SEQ( dummy_padding /* ctxExprs: */ , ##__VA_ARGS__ ) ) \
/**/

#define ELASTIC_APM_LOG_CRITICAL( msg, /* ctxExprs: */ ... ) ELASTIC_APM_LOG_WITH_LEVEL( _ambientContext, Elastic::Apm::Log::Level::critical, msg /* ctxExprs: */ , ##__VA_ARGS__ )
#define ELASTIC_APM_LOG_ERROR( msg, /* ctxExprs: */ ... ) ELASTIC_APM_LOG_WITH_LEVEL( _ambientContext, Elastic::Apm::Log::Level::error, msg /* ctxExprs: */ , ##__VA_ARGS__ )
#define ELASTIC_APM_LOG_WARNING( msg, /* ctxExprs: */ ... ) ELASTIC_APM_LOG_WITH_LEVEL( _ambientContext, Elastic::Apm::Log::Level::warning, msg /* ctxExprs: */ , ##__VA_ARGS__ )
#define ELASTIC_APM_LOG_NOTICE( msg, /* ctxExprs: */ ... ) ELASTIC_APM_LOG_WITH_LEVEL( _ambientContext, Elastic::Apm::Log::Level::notice, msg /* ctxExprs: */ , ##__VA_ARGS__ )
#define ELASTIC_APM_LOG_INFO( msg, /* ctxExprs: */ ... ) ELASTIC_APM_LOG_WITH_LEVEL( _ambientContext, Elastic::Apm::Log::Level::info, msg /* ctxExprs: */ , ##__VA_ARGS__ )
#define ELASTIC_APM_LOG_DEBUG( msg, /* ctxExprs: */ ... ) ELASTIC_APM_LOG_WITH_LEVEL( _ambientContext, Elastic::Apm::Log::Level::debug, msg /* ctxExprs: */ , ##__VA_ARGS__ )
#define ELASTIC_APM_LOG_TRACE( msg, /* ctxExprs: */ ... ) ELASTIC_APM_LOG_WITH_LEVEL( _ambientContext, Elastic::Apm::Log::Level::trace, msg /* ctxExprs: */ , ##__VA_ARGS__ )
