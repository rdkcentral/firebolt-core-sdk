#!/bin/bash
usage()
{
   echo "options:"
   echo "    -t test path"
   echo "    -s sysroot path"
   echo "    -f firebolt path"
   echo "    -c clear build"
   echo "    -h : help"
   echo
   echo "usage: "
   echo "    ./build.sh -t testpath -c -f fireboltpath -s sysrootpath"
}

TestPath="."
FireboltPath=${FIREBOLT_PATH}
SysrootPath=${SYSROOT_PATH}
ClearBuild="N"
while getopts t:s:f:ch flag
do
    case "${flag}" in
        t) TestPath="${OPTARG}";;
        s) SysrootPath="${OPTARG}";;
        f) FireboltPath="${OPTARG}";;
        c) ClearBuild="Y";;
        h) usage && exit 1;;
    esac
done

if [ "${ClearBuild}" == "Y" ];
then
    rm -rf ${TestPath}/build
fi

echo "TestPath"
echo "${TestPath}"
echo "FireboltPath"
echo ${FireboltPath}
cmake -B${TestPath}/build -S${TestPath} -DSYSROOT_PATH=${SysrootPath} -DFIREBOLT_PATH=${FireboltPath}
cmake --build ${TestPath}/build
