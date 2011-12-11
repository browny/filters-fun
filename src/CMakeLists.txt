cmake_minimum_required(VERSION 2.8)

ADD_EXECUTABLE(main main.cpp fileReader.cpp filterBank.cpp controller.cpp utility.cpp)

FIND_PACKAGE(OpenCV REQUIRED)
TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS}
							${PROJECT_SOURCE_DIR}/lib/libeffect.so
							${PROJECT_SOURCE_DIR}/lib/libgradient.so
							${PROJECT_SOURCE_DIR}/lib/libwindow.so)

FILE(COPY ${PROJECT_SOURCE_DIR}/rc/test.jpg	DESTINATION ${PROJECT_BINARY_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


