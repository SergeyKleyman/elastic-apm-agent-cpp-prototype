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

CALL %this_batch_dir%/z_Set_Env_Vars.bat
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CALL :build_and_test_separate_compilation_variants
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

GOTO:EOF
rem #########################
rem ### main
rem ############################################################################

rem ############################################################################
rem ### build_and_test_separate_compilation_variants
rem #########################
:build_and_test_separate_compilation_variants

rem ### separate_compilation: 1 (on)
CALL :build_and_test_build_type_variants 1
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

rem ### separate_compilation: 0 (off)
CALL :build_and_test_build_type_variants 0
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

GOTO:EOF
rem #########################
rem ### build_and_test_separate_compilation_variants
rem ############################################################################

rem ############################################################################
rem ### build_and_test_build_type_variants %separate_compilation%
rem #########################
:build_and_test_build_type_variants

SET "separate_compilation=%1"

IF "%separate_compilation%"=="" (
    ECHO separate_compilation must not be empty
    EXIT /B 1
)

CALL :build_and_test_one_variant Debug %separate_compilation%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

CALL :build_and_test_one_variant Release %separate_compilation%
IF %ERRORLEVEL% NEQ 0 GOTO:EOF

GOTO:EOF
rem #########################
rem ### build_and_test_build_type_variants
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

CALL %this_batch_dir%/Build_and_Test_one_variant.bat %build_type% %separate_compilation%

GOTO:EOF
rem #########################
rem ### build_and_test_one_variant
rem ############################################################################


rem ============================================================================
:exit_this_script

