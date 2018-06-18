cmake_minimum_required (VERSION 2.8.12)
project (genDockerImage)



set(genDockerfile_SOURCES genDockerfile.cpp)
add_executable(run, build.cpp)
add_executable(genDockerfile genDockerfile.cpp)
add_custom_target(genDockerfile_run
	COMMAND genDockerfile ${GCC_VERSION} ${MPICH_VERSION} ${TPL_URL}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	SOURCES ${genDockerfile_SOURCES}
)
add_dependencies(run, genDockerfile_run)
set (clean_up "rm run")
execute_process (COMMAND clean_up)
