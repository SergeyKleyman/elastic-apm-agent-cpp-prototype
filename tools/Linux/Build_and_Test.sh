#!/bin/bash

this_script_dir="$( dirname "${BASH_SOURCE[0]}" )"
# shellcheck source=./z_Set_Env_Vars.sh
. "${this_script_dir}/z_Set_Env_Vars.sh" || exit

for separate_compilation in 1 0
do
    for build_type in Debug Release
    do
        for use_clang in 1 0
        do
            # shellcheck disable=SC2154
            "${Linux_tools_dir}/Build_and_Test_one_variant.sh" ${use_clang} ${build_type} ${separate_compilation} || exit
        done
    done
done
