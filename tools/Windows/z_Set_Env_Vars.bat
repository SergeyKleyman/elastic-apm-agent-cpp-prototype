PUSHD "%~dp0"
SET this_batch_dir=%cd%
SET this_batch_file_name=%~nx0
POPD

SET "Windows_tools_dir=%this_batch_dir%"
SET "repo_root_dir=%Windows_tools_dir%/../.."
SET "build_tests_output_root_dir=%repo_root_dir%/_GENERATED/_BUILD_Tests_Windows"
SET "build_examples_output_root_dir=%repo_root_dir%/_GENERATED/_BUILD_Examples_Windows"
