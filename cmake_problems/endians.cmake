set(TASK_NAME One_Little_Endian)
set(TASK_NAME_DEV One_Little_Endian_dev)
set(SRC_name endians)

set(SUBMIT_FOLDER tasks-independent)

set(SRC_dev
	"${CMAKE_PROJECT_NAME}/${TASK_NAME}/${SRC_name}_dev.cpp"
	"${CMAKE_PROJECT_NAME}/${TASK_NAME}/${SRC_name}_main_dev.cpp"
)
set(SRC
	"${CMAKE_PROJECT_NAME}/${TASK_NAME}/${SRC_name}.cpp"
	"${CMAKE_PROJECT_NAME}/${TASK_NAME}/${SRC_name}_main.cpp"
)

set(TESTS_dev "${CMAKE_PROJECT_NAME}/${TASK_NAME}/tests/tests_dev.cpp")
set(TESTS "${CMAKE_PROJECT_NAME}/${TASK_NAME}/tests/tests.cpp")

set(HEADERS	
	# ${CMAKE_PROJECT_NAME}/include/example.h"
)

#add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/${TASK_NAME}/tests)

execute_process(COMMAND mkdir ${TASK_NAME})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${TASK_NAME}")

add_executable(${TASK_NAME_DEV} ${SRC_dev} ${HEADERS})
add_executable("tests_${TASK_NAME_DEV}" ${TESTS_dev} ${HEADERS})

set(CMAKE_CXX_STANDARD 11)
add_executable(${TASK_NAME} ${SRC} ${HEADERS})
add_executable("tests_${TASK_NAME}" ${TESTS} ${HEADERS})
set(CMAKE_CXX_STANDARD 20)

execute_process(COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/${TASK_NAME}/${SRC_name}.cpp" ${CMAKE_CURRENT_SOURCE_DIR}/${SUBMIT_FOLDER})

execute_process(
     #COMMAND sed 1d "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/${TASK_NAME}/${SRC_name}_main.cpp" | cat >> "${CMAKE_CURRENT_SOURCE_DIR}/${SUBMIT_FOLDER}/${SRC_name}.cpp"
	 COMMAND bash "-c" "sed 1d ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/${TASK_NAME}/${SRC_name}_main.cpp | cat >> ${CMAKE_CURRENT_SOURCE_DIR}/${SUBMIT_FOLDER}/${SRC_name}.cpp"
 )
