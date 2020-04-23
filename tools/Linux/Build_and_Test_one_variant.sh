#!/bin/bash

use_clang=$1
build_type=$2
separate_compilation=$3

this_script_dir="$( dirname "${BASH_SOURCE[0]}" )"
# shellcheck source=./z_Set_Env_Vars.sh
. "${this_script_dir}/z_Set_Env_Vars.sh"

echo "#####################################################################"
echo "##################################"
echo "################"
echo "###"
echo "### Building and testing variant:"
echo "###                               use_clang: ${use_clang}"
echo "###                               build_type: ${build_type}"
echo "###                               separate_compilation: ${separate_compilation}"
echo "###                               Env vars: CC: \"${CC}\". CXX: \"${CXX}\"."
echo "###"
echo

export ELASTIC_APM_CMAKE_USE_CLANG=${use_clang}
cxx_sub_dir_name=cxx
if [ ${use_clang} -eq "1" ]; then
    export CC=clang
    export CXX=clang++
    cxx_sub_dir_name=clang
fi

separate_compilation_sub_dir_name=sep_comp
if [ ${separate_compilation} -eq "0" ]; then
    separate_compilation_sub_dir_name=hdr_only
fi

# shellcheck disable=SC2154
build_output_dir="${build_tests_output_root_dir}/${cxx_sub_dir_name}/${build_type}/${separate_compilation_sub_dir_name}"

mkdir -p "${build_output_dir}"
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

pushd "${build_output_dir}" || exit

export ELASTIC_APM_SEPARATE_COMPILATION_01=${separate_compilation}

# shellcheck disable=SC2154
echo "################ cmake" "-DCMAKE_BUILD_TYPE=${build_type}" "${repo_root_dir}"
cmake "-DCMAKE_BUILD_TYPE=${build_type}" "${repo_root_dir}" || exit

number_of_cores=$(getconf _NPROCESSORS_ONLN)
# number_of_make_jobs=$((number_of_cores+1))
number_of_make_jobs=${number_of_cores}
echo "################ make -j${number_of_make_jobs}"
make -j${number_of_make_jobs} || exit

### export ELASTIC_APM_MEMORY_TRACKING_LEVEL=OFF
export ELASTIC_APM_ABORT_ON_MEMORY_LEAK=true

echo "################" "ctest --build-config ${build_type} -VV"

ctest --build-config "${build_type}" -VV || exit

popd || exit

echo
echo "###"
echo "### DONE Building and testing variant:"
echo "###                                   build_type: ${build_type}"
echo "###                                   separate_compilation: ${separate_compilation}"
echo "###"
echo "################"
echo "##################################"
echo "#####################################################################"

