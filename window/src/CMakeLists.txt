cmake_minimum_required(VERSION 2.8)

INCLUDE_DIRECTORIES(../include/)

SET(LIBWINDOW_SRC gammaEditWindow.cpp imgEditWindow.cpp)

ADD_LIBRARY(window_dynamic SHARED ${LIBWINDOW_SRC})

SET_TARGET_PROPERTIES(window_dynamic PROPERTIES OUTPUT_NAME "window")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


