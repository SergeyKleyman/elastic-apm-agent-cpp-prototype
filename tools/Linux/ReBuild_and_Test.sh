#!/bin/bash

this_script_dir="$( dirname "${BASH_SOURCE[0]}" )"
# shellcheck source=./z_Set_Env_Vars.sh
. "${this_script_dir}/z_Set_Env_Vars.sh" || exit

rm -rf "${build_tests_output_root_dir:?}/" || exit

# shellcheck disable=SC2154
"${Linux_tools_dir}/Build_and_Test.sh" || exit
