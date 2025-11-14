#!/bin/bash

PATH_TO_COMMON="common"
PATH_TO_NETWORK="network"
PATH_TO_SERVER="server"

OPT="$1"

if [ -z "$OPT" ] || [ "$OPT" == "-h" ] || [ "$OPT" == "--help" ]; then
    echo "USAGE:"
    echo "\t ./build-handler.sh [opt]\n"
    echo "DESCRIPTION:"
    echo "\t - opt    The operation the handler should do (build or clean)."
fi

if [ "$OPT" == "clean" ]; then
    rm -rf build/
    find . -type f -name '*.a' -delete
    find . -type f -name 'dufos_server' -delete -or -name 'dufos_client' -delete
    exit 0
fi

if [ ! -z "$OPT" ]; then
    cmake -B build/${OPT} -S ${OPT} -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=${OPT}
    cmake --build build/${OPT} --parallel
    exit 0
fi
