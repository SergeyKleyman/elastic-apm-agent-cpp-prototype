CMAKE_MINIMUM_REQUIRED( VERSION 3.15 )

IF ( DEFINED ENV{CLION_IDE} )
    ADD_COMPILE_DEFINITIONS( ELASTIC_APM_UNDER_IDE )
ENDIF ()

IF ( WIN32 )
    # From https://github.com/microsoft/vcpkg/blob/master/docs/users/integration.md#using-an-environment-variable-instead-of-a-command-line-option
    IF ( DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE )
        SET( CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
             CACHE STRING "" )
        MESSAGE( "Set CMAKE_TOOLCHAIN_FILE to ${CMAKE_TOOLCHAIN_FILE}" )
    ENDIF ()
ENDIF ()

PROJECT(
        Elastic_APM_Cpp_Agent
        VERSION 0.1.0
        DESCRIPTION "Elastic APM C++ Agent Prototype"
        HOMEPAGE_URL "https://github.com/SergeyKleyman/elastic-apm-agent-cpp-prototype"
        LANGUAGES CXX
)

INCLUDE( CTest )

# Assuming gcc is the default
SET( ELASTIC_APM_CMAKE_USE_CLANG 0 )
IF ( DEFINED ENV{ELASTIC_APM_CMAKE_USE_CLANG} )
    SET( ELASTIC_APM_CMAKE_USE_CLANG $ENV{ELASTIC_APM_CMAKE_USE_CLANG} )
ENDIF ()

MESSAGE( "CXX env var: \"$ENV{CXX}\". CC env var: \"$ENV{CC}\". ELASTIC_APM_CMAKE_USE_CLANG env var: \"$ENV{ELASTIC_APM_CMAKE_USE_CLANG}\"." )
IF ( ${ELASTIC_APM_CMAKE_USE_CLANG} EQUAL 0 )
    MESSAGE( "Using default C++ compiler" )
ELSE ()
    MESSAGE( "Using Clang C++ compiler" )

    SET (CMAKE_C_FLAGS_INIT                "-Wall -std=c99")
    SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
    SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

    SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
    SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
ENDIF ()

SET( CMAKE_CXX_STANDARD 11 )
SET( CMAKE_CXX_STANDARD_REQUIRED ON )

# Always include srcdir and builddir in include path
# This saves typing ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY} in
# about every subdir
# since cmake 2.4.0
SET( CMAKE_INCLUDE_CURRENT_DIR ON )

# Put the include dirs which are in the source or build tree
# before all other include dirs, so the headers in the sources
# are preferred over the already installed ones
# since cmake 2.4.1
SET( CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON )

# Use colored output
# since cmake 2.4.0
SET( CMAKE_COLOR_MAKEFILE ON )

# Create the compile command database for clang by default
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Always build with -fPIC
SET( CMAKE_POSITION_INDEPENDENT_CODE ON )

# Avoid source tree pollution
SET( CMAKE_DISABLE_SOURCE_CHANGES ON )
SET( CMAKE_DISABLE_IN_SOURCE_BUILD ON )

SET( repo_root_dir ${CMAKE_CURRENT_SOURCE_DIR} )
SET( prod_src_include_dir ${repo_root_dir}/src/include )

INCLUDE_DIRECTORIES( ${prod_src_include_dir} )

FILE( GLOB_RECURSE prod_source_files "${prod_src_include_dir}/*.hxx" )

SET( ELASTIC_APM_SEPARATE_COMPILATION_01 1 )
IF ( DEFINED ENV{ELASTIC_APM_SEPARATE_COMPILATION_01} )
    SET( ELASTIC_APM_SEPARATE_COMPILATION_01 $ENV{ELASTIC_APM_SEPARATE_COMPILATION_01} )
ENDIF ()

IF ( ${ELASTIC_APM_SEPARATE_COMPILATION_01} EQUAL 0 )
    MESSAGE( "Not adding compile definition ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS" )
ELSE ()
    MESSAGE( "Adding compile definition ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS" )
    ADD_COMPILE_DEFINITIONS( ELASTIC_APM_SEPARATE_COMPILATION_AND_DEPS )
ENDIF ()

ADD_SUBDIRECTORY( tests )

ADD_TEST( NAME Elastic_APM_Cpp_Agent_tests COMMAND Elastic_APM_Cpp_Agent_tests )
