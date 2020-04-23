CMAKE_MINIMUM_REQUIRED( VERSION 3.15 )

IF ( WIN32 )
    # From https://github.com/microsoft/vcpkg/blob/master/docs/users/integration.md#using-an-environment-variable-instead-of-a-command-line-option
    IF ( DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE )
        SET( CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
             CACHE STRING "" )
        MESSAGE( "Set CMAKE_TOOLCHAIN_FILE to ${CMAKE_TOOLCHAIN_FILE}" )
    ENDIF ()
ENDIF ()

PROJECT(
        Elastic_APM_Cpp_Agent_example_command_line_app
        VERSION 0.1.0
        DESCRIPTION "Example command line app for Elastic APM C++ Agent"
        HOMEPAGE_URL "https://github.com/SergeyKleyman/elastic-apm-agent-cpp-prototype"
        LANGUAGES CXX
)

INCLUDE( CTest )

SET( repo_root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../.. )
SET( Elastic_APM_Cpp_Agent_include_dir ${repo_root_dir}/src/include )

INCLUDE_DIRECTORIES( ${Elastic_APM_Cpp_Agent_include_dir} )

ADD_COMPILE_DEFINITIONS( ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS )

ADD_COMPILE_DEFINITIONS( CMAKE_PROJECT_DESCRIPTION="${CMAKE_PROJECT_DESCRIPTION}" )

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
SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_components} container )
SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_components} log )
SET( Elastic_APM_Boost_components ${Elastic_APM_Boost_components} filesystem )

FIND_PACKAGE( Boost REQUIRED COMPONENTS ${Elastic_APM_Boost_components} )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )

FIND_PACKAGE( RapidJSON CONFIG REQUIRED )
INCLUDE_DIRECTORIES( ${RAPIDJSON_INCLUDE_DIRS} )

FIND_PACKAGE( OpenSSL REQUIRED )
INCLUDE_DIRECTORIES( ${OPENSSL_INCLUDE_DIR} )

FILE( GLOB_RECURSE app_source_files *.cxx *.hxx )

SET( source_files ${app_source_files} )

IF ( NOT WIN32 )
    ADD_LINK_OPTIONS( -rdynamic )
ENDIF ()

ADD_COMPILE_DEFINITIONS( ELASTIC_APM_ASSERT_DEFAULT_LEVEL=all )

ADD_EXECUTABLE( command_line_app ${source_files} )

SET( libraries_to_link ${Boost_LIBRARIES} )
SET( libraries_to_link ${libraries_to_link} ${OPENSSL_LIBRARIES} )

IF ( NOT WIN32 )
    SET( libraries_to_link ${libraries_to_link} pthread dl )
ENDIF ()

TARGET_LINK_LIBRARIES( command_line_app ${libraries_to_link} )

ADD_TEST( NAME command_line_app COMMAND command_line_app )
