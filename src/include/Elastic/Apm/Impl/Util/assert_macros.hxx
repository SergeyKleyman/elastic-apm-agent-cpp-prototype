#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdlib.hxx" // std::abort
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/stringize.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/cat.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_CURRENT_FUNCTION_PP_FQ_NAME
#include "Elastic/Apm/Impl/Util/assert_config.hxx"
#include "Elastic/Apm/Impl/Util/basic_macros.hxx"
#include "Elastic/Apm/Impl/Util/AssertionFailedException.hxx"

#if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )

// TODO: Sergey Kleyman: Implement: Better formatting in ELASTIC_APM_RAW_ASSERT with __LINE__

#define ELASTIC_APM_RAW_ASSERT( cond, /* msg, ctxExprs: */ ... ) \
    do { \
        if ( ! (cond) ) \
        { \
            throw Elastic::Apm::Impl::Util::AssertionFailedException{ \
                Elastic::Apm::Util::String::fromLiteral( \
                    "Assertion " #cond " failed." \
                    " File: " __FILE__ \
                    " Line: " BOOST_PP_STRINGIZE( __LINE__ ) \
                ) \
            }; \
        } \
    } while ( 0 ) \

#define ELASTIC_APM_ASSERT_WITH_LEVEL( ambCtx, statementLevel, cond, /* msg, ctxExprs: */ ... ) \
    do { \
        if ( (ambCtx).assertLevel() >= (statementLevel) ) \
        { \
            ELASTIC_APM_RAW_ASSERT( cond /* msg, ctxExprs: */ , ##__VA_ARGS__ ); \
        } \
    } while ( 0 ) \
/**/

#define ELASTIC_APM_ASSERT_CALL_IF_LEVEL_ENABLED( ambCtx, statementLevel, assertingCall ) \
    do { \
        if ( (ambCtx).assertLevel() >= (statementLevel) ) \
        { \
            assertingCall; \
        } \
    } while ( 0 ) \
/**/

#else // #if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )

#define ELASTIC_APM_RAW_ASSERT( cond, /* msg, ctxExprs: */ ... ) ELASTIC_APM_NOOP_STATEMENT
#define ELASTIC_APM_ASSERT_WITH_LEVEL( level, cond, /* msg: */ ... ) ELASTIC_APM_NOOP_STATEMENT
#define ELASTIC_APM_ASSERT_CALL_IF_LEVEL_ENABLED( ambCtx, statementLevel, callable ) ELASTIC_APM_NOOP_STATEMENT

#endif // #if ( ELASTIC_APM_ASSERT_ENABLED_01 != 0 )

#define ELASTIC_APM_ASSERT_WITH_CONTEXT( ambCtx, cond, /* msg, ctxExprs: */ ... ) \
    ELASTIC_APM_ASSERT_WITH_LEVEL( ambCtx, Elastic::Apm::Impl::Util::AssertLevel::O_1, cond /* msg, ctxExprs: */ , ##__VA_ARGS__ )

#define ELASTIC_APM_ASSERT( cond, /* msg, ctxExprs: */ ... ) \
    ELASTIC_APM_ASSERT_WITH_CONTEXT( _ambientContext, cond /* msg, ctxExprs: */ , ##__VA_ARGS__ )

#define ELASTIC_APM_ASSERT_O_N( cond, /* msg, ctxExprs: */ ... ) \
    ELASTIC_APM_ASSERT_WITH_LEVEL( _ambientContext, Elastic::Apm::Impl::Util::AssertLevel::O_n, cond /* msg, ctxExprs: */ , ##__VA_ARGS__ )

#define ELASTIC_APM_ASSERT_CALL_IF_O_1_ENABLED( assertingCall ) \
    ELASTIC_APM_ASSERT_CALL_IF_LEVEL_ENABLED( _ambientContext, Elastic::Apm::Impl::Util::AssertLevel::O_1, assertingCall )

#define ELASTIC_APM_ASSERT_CALL_IF_O_N_ENABLED( assertingCall ) \
    ELASTIC_APM_ASSERT_CALL_IF_LEVEL_ENABLED( _ambientContext, Elastic::Apm::Impl::Util::AssertLevel::O_n, assertingCall )
