Generates a Dockerfile from which to build an MPACT development environment.

Usage: cmake [-D GCC_VERSION=] [-D MPI_VERSION=] [-D TPL_URL=] [-D NAME=] [-D ZIP=]

GCC_VERSION: should be of the form gcc.y.z. Default value is "gcc-6.4.0"
MPI_VERSION: should be of the form mpi-x.y or mvapich2-x.y. Default value is "mvapich2-2.0"
TPL_URL: should be the url of a git repository containing TPLs to build using cmake. Default value is "https://github.com/CASL/vera_tpls.git"
NAME: Default value is "test-mpact-dev-env"
ZIP: If set, saves the docker image as gzipped NAME.tar.gz. False by default

run cleanup.exe to clean up Cmake files and extraneous executables