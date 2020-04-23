INCLUDE_DIRECTORIES( ${prod_src_include_dir} )

SET( Boost_USE_STATIC_LIBS OFF )
ADD_COMPILE_DEFINITIONS( BOOST_ALL_DYN_LINK )
ADD_COMPILE_DEFINITIONS( BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0 )

# Setting _WIN32_WINNT for Boost.Asio (0x0601 means Windows 7 target)
# https://docs.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt
IF ( WIN32 )
    ADD_COMPILE_DEFINITIONS( _WIN32_WINNT=0x0601 )
ENDIF ()

# https://github.com/boostorg/stacktrace/issues/66
# Order of usefulness (from the most useful one):
#       boost_stacktrace_windbg_cached, boost_stacktrace_windbg,
#       boost_stacktrace_backtrace, [boost_stacktrace_addr2line,]
#       boost_stacktrace_basic, boost_stacktrace_noop
IF ( WIN32 )
    SET( Elastic_APM_Boost_StackTrace_components stacktrace_windbg_cached stacktrace_windbg )
ELSE ()
    SET( Elastic_APM_Boost_StackTrace_components stacktrace_backtrace stacktrace_addr2line stacktrace_basic )
ENDIF ()
SET( Elastic_APM_Boost_StackTrace_components ${Elastic_APM_Boost_StackTrace_components} stacktrace_noop )

SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_StackTrace_components} )
SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_components} unit_test_framework )
SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_components} container )
SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_components} log )
SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_components} filesystem )

FIND_PACKAGE( Boost REQUIRED COMPONENTS ${Elastic_APM_Boost_components} )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )

FIND_PACKAGE( RapidJSON CONFIG REQUIRED )
INCLUDE_DIRECTORIES( ${RAPIDJSON_INCLUDE_DIRS} )

FIND_PACKAGE( OpenSSL REQUIRED )
INCLUDE_DIRECTORIES( ${OPENSSL_INCLUDE_DIR} )

FILE( GLOB_RECURSE tests_source_files *.cxx *.hxx )

SET( source_files ${tests_source_files} ${prod_source_files} )

IF ( NOT WIN32 )
    ADD_LINK_OPTIONS( -rdynamic )
ENDIF ()

ADD_COMPILE_DEFINITIONS( ELASTIC_APM_ASSERT_DEFAULT_LEVEL=all )

ADD_EXECUTABLE( Elastic_APM_Cpp_Agent_tests ${source_files} )

SET( Elastic_APM_Cpp_Agent_tests_link_libraries ${Boost_LIBRARIES} )
SET( Elastic_APM_Cpp_Agent_tests_link_libraries ${Elastic_APM_Cpp_Agent_tests_link_libraries} ${OPENSSL_LIBRARIES} )

IF ( NOT WIN32 )
    SET( Elastic_APM_Cpp_Agent_tests_link_libraries ${Elastic_APM_Cpp_Agent_tests_link_libraries} pthread dl )
ENDIF ()

TARGET_LINK_LIBRARIES( Elastic_APM_Cpp_Agent_tests ${Elastic_APM_Cpp_Agent_tests_link_libraries} )

IF ( MSVC )
    TARGET_COMPILE_OPTIONS( Elastic_APM_Cpp_Agent_tests PRIVATE /Wall /WX )
ENDIF ()
