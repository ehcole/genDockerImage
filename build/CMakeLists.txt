add_executable(genDockerfile genDockerfile.cpp)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/genDockerfile.cpp
	DEPENDS genDockerfile
	COMMAND genDockerfile GCC_VERSION MPICH_VERSION TPL_URL
)
include_directories ( ${CMAKE_CURRENT_BINARY_DIR} )

