cmake_minimum_required (VERSION 2.6)

set(PROJECT ray-tracing-practice)
project (${PROJECT})

set(DIR_SRC_1 ${PROJECT_SOURCE_DIR}/src/in-one-weekend)
set(DIR_SRC_2 ${PROJECT_SOURCE_DIR}/src/the-next-week)

include_directories(
${PROJECT_SOURCE_DIR}
${DIR_SRC_1}
${DIR_SRC_2}
${PROJECT_SOURCE_DIR}/third-party
)

file(GLOB_RECURSE SRC_LIST_1 ${PROJECT_SOURCE_DIR} 
${DIR_SRC_1}/*.cpp 
${DIR_SRC_1}/*.h 
)

file(GLOB_RECURSE SRC_LIST_2 ${PROJECT_SOURCE_DIR} 
${DIR_SRC_2}/*.cpp 
${DIR_SRC_2}/*.h 
)

add_executable (${PROJECT}
${SRC_LIST_1}
${SRC_LIST_2}
main.cpp
)

source_group("InOneWeekend" FILES ${SRC_LIST_1})
source_group("TheNextWeekend" FILES ${SRC_LIST_2})

