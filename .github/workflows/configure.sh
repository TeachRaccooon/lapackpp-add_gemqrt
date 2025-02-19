#!/bin/bash -x

maker=$1
device=$2

if [ "${maker}" = "cmake" ]; then
    rm -rf build
    mkdir -p build
fi

mydir=$(dirname $0)
source ${mydir}/setup_env.sh

print "======================================== Environment"
env

print "======================================== Setup build"
export color=no
export CXXFLAGS="-Werror -Wno-unused-command-line-argument"

rm -rf ${top}/install
if [ "${maker}" = "make" ]; then
    make distclean
    make config prefix=${top}/install \
         || exit 10
fi
if [ "${maker}" = "cmake" ]; then
    (  # Build blaspp first
       git clone https://github.com/icl-utk-edu/blaspp
       mkdir blaspp/build && cd blaspp/build
       cmake -Dcolor=no -Dbuild_tests=no \
             -DCMAKE_INSTALL_PREFIX=${top}/install \
             -Dgpu_backend=${gpu_backend} .. \
             || exit 11
       make -j8 install
    )

    cmake -Dcolor=no \
          -DCMAKE_INSTALL_PREFIX=${top}/install \
          -Dgpu_backend=${gpu_backend} .. \
          || exit 12
fi

print "======================================== Finished configure"
exit 0
