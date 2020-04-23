@ECHO OFF
REM ### @ECHO OFF

SETLOCAL

CALL :main
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

SET repo_root_dir=%this_batch_dir%/../..

CALL %repo_root_dir%/tools/Windows/Build_and_Run_example.bat %this_batch_dir%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

GOTO:EOF
rem #########################
rem ### main
rem ############################################################################

rem ============================================================================
:exit_this_script

