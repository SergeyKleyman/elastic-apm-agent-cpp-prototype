#!/bin/bash

this_script_dir="$( dirname "${BASH_SOURCE[0]}" )"

repo_root_dir=${this_script_dir}/../..

"${repo_root_dir}/tools/Linux/Build_and_Run_example.sh" "${this_script_dir}" || exit
