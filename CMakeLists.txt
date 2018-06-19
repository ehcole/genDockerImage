cmake_minimum_required (VERSION 2.8.12)
project (genDockerImage)

if ( NOT GCC_VERSION )
   set (GCC_VERSION "gcc-6.4.0")
   message ("No GCC_VERSION specified. Using default: gcc-6.4.0")
endif()

if ( NOT MPI_VERSION )
   set (MPI_VERSION "mvapich2-2.0")
   message ("No MPI_VERSION specified. Using default: mvapich2-2.0")
endif()

if ( NOT TPL_URL )
   set (TPL_URL "https://github.com/CASL/vera_tpls.git")
   set (TPL_BUILD_DIR "/vera_tpls/TPL_build/")
   message ("No TPL_URL specified. Using default: https://github.com/CASL/vera_tpls.git")
elseif ( NOT TPL_BUILD_DIR )
   message (FATAL_ERROR "TPL_BUILD_DIR not specified. Aborting.")
endif()

if ( NAME )
   set (name ${NAME})
else()
   set (name "test-mpact-dev-env")
   message ("No NAME specified. Using default: test-mpact-dev-env")
endif()

if ( ZIP )
   set (zip "true")
else()
   set (zip "false")
endif()

set(genDockerfile_SOURCES genDockerfile.cpp)
add_executable(cleanup cleanup.cpp)
add_executable(genDockerfile genDockerfile.cpp)
add_custom_target(genDockerfile_run
	COMMAND genDockerfile ${GCC_VERSION} ${MPI_VERSION} ${TPL_URL} ${TPL_BUILD_DIR} ${name} ${zip}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	SOURCES ${genDockerfile_SOURCES}
)
add_dependencies(cleanup genDockerfile_run)

