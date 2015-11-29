#!/bin/bash

if [ ! -d "../kalpana-build" ]; then
  mkdir ../kalpana-build
fi
cd ../kalpana-build

cmake ../kalpana \
  -DCMAKE_BUILD_TYPE=Release \
  -DKALPANA_BUILD_SAMPLES=ON

make -j`nproc` && make test && make package
