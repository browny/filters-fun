cmake_minimum_required(VERSION 2.8)

ADD_EXECUTABLE(main main.cpp fileReader.cpp filterBank.cpp controller.cpp utility.cpp)

FIND_PACKAGE(OpenCV REQUIRED)

TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS})
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(main 	${PROJECT_SOURCE_DIR}/lib/libeffect.so
							${PROJECT_SOURCE_DIR}/lib/libgradient.so
							${PROJECT_SOURCE_DIR}/lib/libwindow.so)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux") 

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
TARGET_LINK_LIBRARIES(main 	${PROJECT_SOURCE_DIR}/lib/libeffect.dylib
							${PROJECT_SOURCE_DIR}/lib/libgradient.dylib
							${PROJECT_SOURCE_DIR}/lib/libwindow.dylib)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

FILE(COPY ${PROJECT_SOURCE_DIR}/rc/test.jpg	DESTINATION ${PROJECT_BINARY_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


