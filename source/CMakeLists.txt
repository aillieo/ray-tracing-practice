cmake_minimum_required (VERSION 2.6)

set(PROJECT ray-tracing-practice)
project (${PROJECT})

set(DIR_SRC ${PROJECT_SOURCE_DIR}/src)

include_directories(
${PROJECT_SOURCE_DIR}
${DIR_SRC}
${PROJECT_SOURCE_DIR}/third-party
${DIR_SRC}/common
${DIR_SRC}/in-one-weekend
)

file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCE_DIR} 
${DIR_SRC}/*.cpp 
${DIR_SRC}/*.h 
${DIR_SRC}/*.c 
${DIR_SRC}/*.hpp
)

add_executable (${PROJECT}
${SRC_LIST}
main.cpp
)
