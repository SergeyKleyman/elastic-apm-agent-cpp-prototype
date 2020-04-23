#!/bin/bash

example_dir=$1

this_script_dir="$( dirname "${BASH_SOURCE[0]}" )"
# shellcheck source=./z_Set_Env_Vars.sh
. "${this_script_dir}/z_Set_Env_Vars.sh"

build_type=Release
example_name="$( basename "${example_dir}" )"

echo "#####################################################################"
echo "##################################"
echo "################"
echo "###"
echo "### Building and testing variant:"
echo "###                               example_dir: ${example_dir}"
echo "###                               example_name: ${example_name}"
echo "###                               build_type: ${build_type}"
echo "###"
echo

# shellcheck disable=SC2154
build_output_dir="${build_examples_output_root_dir}/${example_name}/${build_type}"

mkdir -p "${build_output_dir}"
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

pushd "${build_output_dir}" || exit

# shellcheck disable=SC2154
echo "################ cmake" "-DCMAKE_BUILD_TYPE=${build_type}" "${example_dir}"
cmake "-DCMAKE_BUILD_TYPE=${build_type}" "${example_dir}" || exit

number_of_cores=$(getconf _NPROCESSORS_ONLN)
# number_of_make_jobs=$((number_of_cores+1))
number_of_make_jobs=${number_of_cores}
echo "################ make -j${number_of_make_jobs}"
make -j${number_of_make_jobs} || exit

### export ELASTIC_APM_MEMORY_TRACKING_LEVEL=OFF
export ELASTIC_APM_ABORT_ON_MEMORY_LEAK=true

### echo "################" "ctest --build-config ${build_type} -VV"
### ctest --build-config "${build_type}" -VV || exit
"${build_output_dir}/${example_name}"

popd > /dev/null || exit

echo
echo "###"
echo "### DONE Building and testing variant:"
echo "###                                   build_type: ${build_type}"
echo "###                                   separate_compilation: ${separate_compilation}"
echo "###"
echo "################"
echo "##################################"
echo "#####################################################################"

