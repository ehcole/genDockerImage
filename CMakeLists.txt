cmake_minimum_required (VERSION 2.8.12)
project (genDockerImage)

include_directories ("${PROJECT_SOURCE_DIR}/build")
add_subdirectory (build)
execute_process(COMMAND "docker build -t test-mpact-dev-env ./build")
execute_process(COMMAND "docker save test-mpact-dev-env | gzip > test-mpact-dev-env.tar.gz")

