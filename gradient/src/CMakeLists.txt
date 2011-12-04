cmake_minimum_required(VERSION 2.8)

INCLUDE_DIRECTORIES(../include/)

SET(LIBGRADIENT_SRC ellipseGradient.cpp linearGradient.cpp pointGradient.cpp)

ADD_LIBRARY(gradient_dynamic SHARED ${LIBGRADIENT_SRC})

SET_TARGET_PROPERTIES(gradient_dynamic PROPERTIES OUTPUT_NAME "gradient")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


