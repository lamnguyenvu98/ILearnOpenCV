cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0012 NEW)

PROJECT(basic_graphical_user)
FIND_PACKAGE(OpenCV 4.5.0 REQUIRED)
MESSAGE("OpenCV verison: ${OpenCV_VERSION}")
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE(basic_gui basic_gui.cpp)
TARGET_LINK_LIBRARIES(basic_gui opencv_highgui opencv_core)

ADD_EXECUTABLE(slider_mouse_event slider_mouse_event.cpp)
TARGET_LINK_LIBRARIES(slider_mouse_event opencv_highgui opencv_core opencv_imgproc)

ADD_EXECUTABLE(gui_qt gui_qt.cpp)
TARGET_LINK_LIBRARIES(gui_qt ${OpenCV_LIBS})

ADD_EXECUTABLE(opengl_support opengl_support.cpp)
TARGET_LINK_LIBRARIES(opengl_support ${OpenCV_LIBS} -lglut -lGL -lGLU)