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

CALL %this_batch_dir%/z_Set_Env_Vars.bat
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CALL :build_and_run_example %*
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

GOTO:EOF
rem #########################
rem ### main
rem ############################################################################

rem ############################################################################
rem ### build_and_run_example %example_dir%
rem #########################
:build_and_run_example

SET "example_dir=%1"

IF "%example_dir%"=="" (
    ECHO example_dir must not be empty
    EXIT /B 1
)

IF "%repo_root_dir%"=="" (
    ECHO repo_root_dir must not be empty
    EXIT /B 1
)

SET "build_type=Debug"
rem ### SET "build_type=Release"

FOR %%f in ("%example_dir%") DO SET example_name=%%~nxf

SET "build_output_dir=%build_examples_output_root_dir%/%example_name%/%build_type%"

ECHO ################################################################################
ECHO ########################################
ECHO ####################
ECHO ##########
ECHO #####
ECHO ### Building and running:
ECHO ###                                example_dir: %example_dir%
ECHO ###                                example_name: %example_name%
ECHO ###                                build_type: %build_type%
ECHO ###                                build_output_dir: %build_output_dir%
ECHO ###

IF NOT EXIST "%build_output_dir%" (
    MKDIR "%build_output_dir%"
    IF %ERRORLEVEL% NEQ 0 GOTO:EOF
)

PUSHD "%build_output_dir%"
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CMake %example_dir%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CMake --build . --config %build_type%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

"%build_output_dir%/%build_type%/%example_name%.exe"
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

POPD
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

ECHO ### DONE - Building and running:
ECHO ###                                build_type: %build_type%
ECHO #####
ECHO ##########
ECHO ####################
ECHO ########################################
ECHO ################################################################################

GOTO:EOF
rem #########################
rem ### build_and_run_example
rem ############################################################################


rem ============================================================================
:exit_this_script

