#!/bin/bash
#gcc-6.4.0
cmake -D GCC_VERSION=gcc-6.4.0 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mpich_gcc-6_4_0

cmake -D GCC_VERSION=gcc-6.4.0 -D MPI_VERSION=mvapich2-2.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mvapich_gcc-6_4_0

cmake -D GCC_VERSION=gcc-6.4.0 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mpich_gcc-6_4_0

cmake -D GCC_VERSION=gcc-6.4.0 -D MPI_VERSION=mvapich-2.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mvapich_gcc-6_4_0

#gcc-5.4.0
cmake -D GCC_VERSION=gcc-5.4.0 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mpich_gcc-5_4_0

cmake -D GCC_VERSION=gcc-5.4.0 -D MPI_VERSION=mvapich2-2.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mvapich_gcc-5_4_0

cmake -D GCC_VERSION=gcc-5.4.0 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mpich_gcc-5_4_0

cmake -D GCC_VERSION=gcc-5.4.0 -D MPI_VERSION=mvapich-2.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mvapich_gcc-5_4_0

#gcc-4.9.3
cmake -D GCC_VERSION=gcc-4.9.3 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mpich_gcc-4_9_3

cmake -D GCC_VERSION=gcc-4.9.3 -D MPI_VERSION=mvapich2-2.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mvapich_gcc-4_9_3

cmake -D GCC_VERSION=gcc-4.9.3 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mpich_gcc-4_9_3

cmake -D GCC_VERSION=gcc-4_9_3 -D MPI_VERSION=mvapich-2.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mvapich_gcc-4_9_3

#gcc-4.8.5
cmake -D GCC_VERSION=gcc-4.8.5 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mpich_gcc-4_8_5

cmake -D GCC_VERSION=gcc-4.8.5 -D MPI_VERSION=mvapich2-2.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mvapich_gcc-4_8_5

cmake -D GCC_VERSION=gcc-4.8.5 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mpich_gcc-4_8_5

cmake -D GCC_VERSION=gcc-4.8.5 -D MPI_VERSION=mvapich-2.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mvapich_gcc-4_8_5

#gcc-4.8.3
cmake -D GCC_VERSION=gcc-4.8.3 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mpich_gcc-4_8_3

cmake -D GCC_VERSION=gcc-4.8.3 -D MPI_VERSION=mvapich2-2.0 -D TPL_URL=https://github.com/CASL/vera_tpls -D TPL_BUILD_DIR=/vera_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mvapich_gcc-4_8_3

cmake -D GCC_VERSION=gcc-4.8.3 -D MPI_VERSION=mpich-3.3.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mpich_gcc-4_8_3

cmake -D GCC_VERSION=gcc-4.8.3 -D MPI_VERSION=mvapich-2.0 -D TPL_URL=https://github.com/ehcole/MPACT_tpls -D TPL_BUILD_DIR=/MPACT_tpls/TPL_build .
make
./cleanup
mv Dockerfile dockerfiles/Dockerfile_mkl_mvapich_gcc-4_8_3
