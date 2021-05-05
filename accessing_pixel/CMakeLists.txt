cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0012 NEW)
PROJECT(accessing_pixel)

# Requires OpenCV
FIND_PACKAGE( OpenCV 4.5.0 REQUIRED )
MESSAGE("OpenCV verison: ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE(access_method accessing_method.cpp)
TARGET_LINK_LIBRARIES(access_method ${OpenCV_LIBS})

ADD_EXECUTABLE(access_gray accessingpixel_gray.cpp)
TARGET_LINK_LIBRARIES(access_gray ${OpenCV_LIBS})

ADD_EXECUTABLE(access_color accessingpixel_color.cpp)
TARGET_LINK_LIBRARIES(access_color ${OpenCV_LIBS})

ADD_EXECUTABLE(change_to_gray change_to_gray.cpp)
TARGET_LINK_LIBRARIES(change_to_gray ${OpenCV_LIBS})

ADD_EXECUTABLE(threshold_access_method threshold_accesspixel.cpp)
TARGET_LINK_LIBRARIES(threshold_access_method ${OpenCV_LIBS})