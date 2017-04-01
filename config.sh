#! /bin/bash

cmake .. \
-DCMAKE_C_COMPILER=/usr/local/bin/mpicc \
-DCMAKE_CXX_COMPILER=/usr/local/bin/mpicxx \
-DSCOREC_PREFIX=/home/feimi/pumi/install \
-DCMAKE_CXX_FLAGS="-O2 -g -Wall" \
