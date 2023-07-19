#!/bin/bash

export aSamplePath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo ${CASROOT}

echo 1
echo $(ps -o comm= $PPID)
echo 2


if [ -e "custom.sh" ]; then
  source "./custom.sh" $*;
fi


# export CASROOT=/home/bensay/Development/OCCT-lib
source ${CASROOT}bin/env.sh $*

if [ "${QTDIR}" != "" ]; then
  export PATH=${QTDIR}/bin:${PATH}
else
  aQMakePath=`which qmake`
  echo "Environment variable \"QTDIR\" not defined.. Define it in \"custom.sh\" script."
  if [ -x "$aQMakePath" ]; then
    echo "qmake from PATH will be used instead."
  else
    exit 1
  fi
fi

host=`uname -s`
export STATION=$host
export RES_DIR=${aSamplePath}/${STATION}/res

echo ${RES_DIR}
