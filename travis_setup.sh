#!/bin/bash

if [ $TRAVIS_OS_NAME = 'linux' ]; then
    # the install step will take care of deploying a newer cmake version
    # first we create a directory for the CMake binaries
    DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
    mkdir ${DEPS_DIR} && cd ${DEPS_DIR}
    # we use wget to fetch the cmake binaries
    travis_retry wget --no-check-certificate https://cmake.org/files/LatestRelease/cmake-3.18.0-Linux-x86_64.tar.gz
    # this is optional, but useful:
    # do a quick md5 check to ensure that the archive we downloaded did not get compromised
    # echo "4d9a9d3351161073a67e49366d701b6fa4b0343781982dc5eef08a02a750d403 *cmake-3.3.2-Linux-x86_64.tar.gz" > cmake_md5.txt
    # md5sum -c cmake_md5.txt
    # extract the binaries; the output here is quite lengthy,
    # so we swallow it to not clutter up the travis console
    tar -xvf cmake-3.18.0-Linux-x86_64.tar.gz > /dev/null
    mv cmake-3.18.0-Linux-x86_64 cmake-install
    # add both the top-level directory and the bin directory from the archive
    # to the system PATH. By adding it to the front of the path we hide the
    # preinstalled CMake with our own.
    PATH=${DEPS_DIR}/cmake-install:${DEPS_DIR}/cmake-install/bin:$PATH
    # don't forget to switch back to the main build directory once you are done
    cd ${TRAVIS_BUILD_DIR}
endif
if [ $TRAVIS_OS_NAME = 'windows' ]; then
    [[ ! -f C:/tools/msys64/msys2_shell.cmd ]] && rm -rf C:/tools/msys64
    choco uninstall -y mingw
    choco upgrade --no-progress -y msys2
    export msys2='cmd //C RefreshEnv.cmd '
    export msys2+='& set MSYS=winsymlinks:nativestrict '
    export msys2+='& C:\\tools\\msys64\\msys2_shell.cmd -defterm -no-start'
    export mingw64="$msys2 -mingw64 -full-path -here -c "\"\$@"\" --"
    export msys2+=" -msys2 -c "\"\$@"\" --"
    $msys2 pacman --sync --noconfirm --needed mingw-w64-x86_64-toolchain
    ## Install more MSYS2 packages from https://packages.msys2.org/base here
    taskkill //IM gpg-agent.exe //F  # https://travis-ci.community/t/4967
    export PATH=/C/tools/msys64/mingw64/bin:$PATH
    export MAKE=mingw32-make  # so that Autotools can find it
    ;;
endif