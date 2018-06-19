Generates a Dockerfile from which to build an MPACT development environment. Expect it to take 2-3 hours to run to completion.

Usage: cmake [-D GCC_VERSION=] [-D MPI_VERSION=] [-D TPL_URL= -D TPL_BUILD_DIR= ] [-D NAME=] [-D ZIP=]; make

GCC_VERSION: should be of the form gcc.y.z. Default value is "gcc-6.4.0"

MPI_VERSION: should be of the form mpich-x.y or mvapich2-x.y. Default value is "mvapich2-2.0"

TPL_URL: should be the url of a git repository containing TPLs to build using cmake. Default value is "https://github.com/CASL/vera_tpls.git"

TPL_BUILD_DIR: must be specified if TPL_URL is specified. Path to TPL_build directory within TPL git repo. E.g., if vera_tpls are used, TPL_BUILD_DIR should be "/vera_tpl/TPL_build/". That is the default value if TPL_URL is not specified.

NAME: Default value is "test-mpact-dev-env"

ZIP: If set, saves the docker image as gzipped NAME.tar.gz. False by default

Run cleanup.exe to clean up Cmake files and extraneous executables
