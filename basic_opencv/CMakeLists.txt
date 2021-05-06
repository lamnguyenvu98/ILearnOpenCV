cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0012 NEW)

PROJECT(basic_opencv)
FIND_PACKAGE(OpenCV 4.5.0 REQUIRED)
MESSAGE("OpenCV verison: ${OpenCV_VERSION}")
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE(basic_matrix_operation basic_matrix_operation.cpp)
TARGET_LINK_LIBRARIES(basic_matrix_operation ${OpenCV_LIBS})

ADD_EXECUTABLE(basic_filestorage basic_filestorage.cpp)
TARGET_LINK_LIBRARIES(basic_filestorage ${OpenCV_LIBS})