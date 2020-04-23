#!/bin/bash

# shellcheck disable=SC2155
export Linux_tools_dir="$( dirname "${BASH_SOURCE[0]}" )"
export repo_root_dir="${Linux_tools_dir}/../.."
export build_tests_output_root_dir="${repo_root_dir}/_GENERATED/_BUILD_Tests_Linux"
export build_examples_output_root_dir="${repo_root_dir}/_GENERATED/_BUILD_Examples_Linux"
