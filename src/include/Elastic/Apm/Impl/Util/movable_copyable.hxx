#pragma once

#define ELASTIC_APM_COPY_CTOR_DEFAULT_IMPL( className ) \
    className( const className& ) = default \

#define ELASTIC_APM_MOVE_CTOR_DEFAULT_IMPL( className, /* noExceptSpec: */ ... ) \
    className( className&& ) /* noExceptSpec: */ __VA_ARGS__ = default \

#define ELASTIC_APM_COPY_ASSIGN_DEFAULT_IMPL( className ) \
    className& operator = ( const className& ) = default \

#define ELASTIC_APM_MOVE_ASSIGN_DEFAULT_IMPL( className, /* noExceptSpec: */ ... ) \
    className& operator = ( className&& ) /* noExceptSpec: */ __VA_ARGS__ = default \

#define ELASTIC_APM_COPY_CTOR_DELETE( className ) \
    className( const className& ) = delete \

#define ELASTIC_APM_MOVE_CTOR_DELETE( className ) \
    className( className&& ) = delete \

#define ELASTIC_APM_COPY_ASSIGN_DELETE( className ) \
    className& operator = ( const className& ) = delete \

#define ELASTIC_APM_MOVE_ASSIGN_DELETE( className ) \
    className& operator = ( className&& ) = delete \

////////////////////////////////////////////////////////////////////////////////
///
///
#define ELASTIC_APM_MOVABLE_AND_COPYABLE( className, /* noExceptSpec */ ... ) \
    ELASTIC_APM_MOVE_CTOR_DEFAULT_IMPL( className, /* noExceptSpec: */ ##__VA_ARGS__ ); \
    ELASTIC_APM_MOVE_ASSIGN_DEFAULT_IMPL( className, /* noExceptSpec: */ ##__VA_ARGS__ ); \
    \
    ELASTIC_APM_COPY_CTOR_DEFAULT_IMPL( className ); \
    ELASTIC_APM_COPY_ASSIGN_DEFAULT_IMPL( className ) \
    /**/
///
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///
///
#define ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( className ) \
    ELASTIC_APM_MOVE_CTOR_DELETE( className ); \
    ELASTIC_APM_MOVE_ASSIGN_DELETE( className ); \
    \
    ELASTIC_APM_COPY_CTOR_DELETE( className ); \
    ELASTIC_APM_COPY_ASSIGN_DELETE( className ) \
    /**/
///
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///
///
#define ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( className, /* noExceptSpec */ ... ) \
    ELASTIC_APM_MOVE_CTOR_DEFAULT_IMPL( className, /* noExceptSpec: */ ##__VA_ARGS__ ); \
    ELASTIC_APM_MOVE_ASSIGN_DEFAULT_IMPL( className, /* noExceptSpec: */ ##__VA_ARGS__ ); \
    \
    ELASTIC_APM_COPY_CTOR_DELETE( className ); \
    ELASTIC_APM_COPY_ASSIGN_DELETE( className ) \
    /**/
///
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///
///
#define ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( className, /* noExceptSpec */ ... ) \
    ELASTIC_APM_MOVE_CTOR_DEFAULT_IMPL( className, /* noExceptSpec: */ ##__VA_ARGS__ ); \
    ELASTIC_APM_MOVE_ASSIGN_DELETE( className ); \
    \
    ELASTIC_APM_COPY_CTOR_DELETE( className ); \
    ELASTIC_APM_COPY_ASSIGN_DELETE( className ) \
    /**/
///
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///
///
#define ELASTIC_APM_COPY_CONSTRUCTIBLE_BUT_NOT_COPY_ASSIGNABLE( className ) \
    ELASTIC_APM_COPY_CTOR_DEFAULT_IMPL( className ); \
    ELASTIC_APM_COPY_ASSIGN_DELETE( className ) \
    /**/
///
///
////////////////////////////////////////////////////////////////////////////////
