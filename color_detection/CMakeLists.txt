cmake_minimum_required(VERSION 3.0)
PROJECT(color_detection)
FIND_PACKAGE(OpenCV 4.5.0 REQUIRED)
MESSAGE("OpenCV verison: ${OpenCV_VERSION}")
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS})

ADD_EXECUTABLE(color_detect_webcam color_detect_webcam.cpp)
TARGET_LINK_LIBRARIES(color_detect_webcam ${OpenCV_LIBS})