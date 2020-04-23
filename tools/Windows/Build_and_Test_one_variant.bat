@ECHO OFF
REM ### @ECHO OFF

SETLOCAL

CALL :main %*
IF %ERRORLEVEL% NEQ 0 GOTO exit_this_script

rem ============================================================================
GOTO exit_this_script

rem ############################################################################
rem ### main
rem #########################
:main

PUSHD "%~dp0"
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

SET this_batch_dir=%cd%
SET this_batch_file_name=%~nx0

POPD
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CALL :build_and_test_one_variant %*
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

GOTO:EOF
rem #########################
rem ### main
rem ############################################################################

rem ############################################################################
rem ### build_and_test_one_variant %build_type% %separate_compilation%
rem #########################
:build_and_test_one_variant

SET "build_type=%1"
SET "separate_compilation=%2"

IF "%build_type%"=="" (
    ECHO build_type must not be empty
    EXIT /B 1
)

IF "%separate_compilation%"=="" (
    ECHO separate_compilation must not be empty
    EXIT /B 1
)

ECHO ################################################################################
ECHO ########################################
ECHO ####################
ECHO ##########
ECHO #####
ECHO ### Building and testing variant:
ECHO ###                                build_type: %build_type%
ECHO ###                                separate_compilation: %separate_compilation%
ECHO ###

SET separate_compilation_sub_dir_name=sep_comp
IF "%separate_compilation%" == "0" (
    SET separate_compilation_sub_dir_name=hdr_only
)

SET "build_output_dir=%build_tests_output_root_dir%/%separate_compilation_sub_dir_name%"

IF NOT EXIST "%build_output_dir%" (
    MKDIR "%build_output_dir%"
    IF %ERRORLEVEL% NEQ 0 GOTO:EOF
)

SET "ELASTIC_APM_SEPARATE_COMPILATION_01=%separate_compilation%"

PUSHD "%build_output_dir%"
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CMake %repo_root_dir%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CMake --build . --config %build_type%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CTest --build-config %build_type% --extra-verbose
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

POPD
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

ECHO ### DONE - Building and testing variant:
ECHO ###                                    build_type: %build_type%
ECHO ###                                    separate_compilation: %separate_compilation%
ECHO #####
ECHO ##########
ECHO ####################
ECHO ########################################
ECHO ################################################################################

GOTO:EOF
rem #########################
rem ### build_and_test_one_variant
rem ############################################################################


rem ============================================================================
:exit_this_script

