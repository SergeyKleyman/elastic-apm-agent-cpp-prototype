@ECHO OFF
REM ### @ECHO OFF

SETLOCAL

PUSHD "%~dp0"
SET this_batch_dir=%cd%
SET this_batch_file_name=%~nx0
POPD

CALL %this_batch_dir%/z_Set_Env_Vars.bat
IF %ERRORLEVEL% NEQ 0 GOTO exit_this_script

IF EXIST "%build_tests_output_root_dir%" (
    DEL /Q /S "%build_tests_output_root_dir%"
    IF %ERRORLEVEL% NEQ 0 GOTO exit_this_script
)

CALL %Windows_tools_dir%/Build_and_Test.bat
IF %ERRORLEVEL% NEQ 0 GOTO exit_this_script

rem ============================================================================
GOTO exit_this_script

rem ============================================================================
:exit_this_script

