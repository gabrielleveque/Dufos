#!/bin/bash

PATH_TO_COMMON="common"
PATH_TO_NETWORK="engine/network"

OPT="$1"

if [ -z "$OPT" ] || [ "$OPT" == "-h" ] || [ "$OPT" == "--help" ]; then
    echo "USAGE:"
    echo "\t ./build-handler.sh [opt]\n"
    echo "DESCRIPTION:"
    echo "\t - opt    The operation the handler should do (build or clean)."
fi

if [ "$OPT" == "common" ]; then
    cmake -B build/${OPT} -S ${PATH_TO_COMMON} -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=${OPT}
    cmake --build build/${OPT} --parallel
    exit 0
fi

if [ "$OPT" == "network" ]; then
    cmake -B build/${OPT} -S ${PATH_TO_NETWORK} -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=${OPT}
    cmake --build build/${OPT} --parallel --target install
    exit 0
fi


if [ "$OPT" == "clean" ]; then
    rm -rf build/${OPT}
    find . -type f -name '*.dylib' -delete
    find . -type f -name '*.so' -delete
    exit 0
fi
