add_executable(genDockerfile genDockerfile.cpp)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/genDockerfile
	COMMAND genDockerfile ${GCC_VERSION} ${MPICH_VERSION} ${TPL_URL}
	DEPENDS genDockerfile 
)
include_directories ( ${CMAKE_CURRENT_BINARY_DIR} )

