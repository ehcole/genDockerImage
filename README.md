Generates a Dockerfile to from which to build an MPACT development environment.

Usage: cmake -D GCC_VERSION -D MPI_VERSION -D TPL_URL [NAME] [ZIP]

GCC_VERSION should be of the form gcc.y.z
MPI_VERSION should be of the form mpi-x.y or mvapich2-x.y
TPL_URL should be the url of a git repository clone into
NAME is optional. Default: test-mpact-dev-env
ZIP is optional. If set to true, saves the docker image as a tar.gz. Set to false by default.
