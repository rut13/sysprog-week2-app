cmake_minimum_required(VERSION 3.23)
project(week2tutorial_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fpermissive)

add_executable(week2tutorial_app main.cpp PluginWrapper.cpp)

add_custom_command(
        TARGET ${PROJECT_NAME}  PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/../sysprog-week2-lowercase/cmake-build-debug/libsysprog_week2_lowercase.dll
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/plugins/libsysprog_week2_lowercase.plug)

add_custom_command(
        TARGET ${PROJECT_NAME}  PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/../sysprog-week2-uppercase/cmake-build-debug/libsysprog_week2_uppercase.dll
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/plugins/libsysprog_week2_uppercase.plug)