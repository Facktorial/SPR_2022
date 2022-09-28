cmake_minimum_required(VERSION 3.14)
include(cmake/Presets.cmake)

project(spr-tasks-projects CXX)
project(${CMAKE_PROJECT_NAME} DESCRIPTION "C++20 Project of tasks from SPR course at VSB-TUO, 2022")
option(BUILD_DOC "Build documentation" OFF)
option(LIFT_DOCS "Lift docs to folder build_docs" OFF)
option(TESTING "Enable testing" ON)

project(${CMAKE_PROJECT_NAME} VERSION "0.0.1")
message("${CMAKE_PROJECT_NAME} VERSION: ${CMAKE_PROJECT_VERSION}")

message("PROJECT_DESCRIPTION: ${CMAKE_PROJECT_DESCRIPTION}")

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include(cmake/Postsets.cmake)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake")

IF (BUILD_DOC)
    include(cmake/Doxygen.cmake)
    enable_doxygen()
ENDIF (BUILD_DOC)

#include(cmake_problems/minesweaper.cmake)
include(cmake_problems/endians.cmake)
#include(cmake_problems/check_the_check.cmake)
