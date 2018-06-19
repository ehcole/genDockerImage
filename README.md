Generates a Dockerfile from which to build an MPACT development environment. Expect it to take 2-3 hours to run to completion.

Usage: cmake [-D GCC_VERSION=] [-D MPI_VERSION=] [-D TPL_URL=] [-D NAME=] [-D ZIP=]; make

GCC_VERSION: should be of the form gcc.y.z. Default value is "gcc-6.4.0"

MPI_VERSION: should be of the form mpich-x.y or mvapich2-x.y. Default value is "mvapich2-2.0"

TPL_URL: should be the url of a git repository containing TPLs to build using cmake. Default value is "https://github.com/CASL/vera_tpls.git"

NAME: Default value is "test-mpact-dev-env"

ZIP: If set, saves the docker image as gzipped NAME.tar.gz. False by default

Run cleanup.exe to clean up Cmake files and extraneous executables

NOTE: Currently, only https://github.com/CASL/vera_tpls.git and https://github.com/ehcole/MPACT_tpls.git are supported TPL_URLs. Modification would be necessary to allow the use of others. In particular, when building the mpact programming environment (allowing the use of gcc), cmake assumes the use of the above urls. The variable cmakeDir must be set to the appropriate build directory in the image, e.g., /scratch/*repo_name*/TPL_build, which depends on the structure of the repository. Adding this custom logic would require modification of genDockerfile.cpp only. --EHC
