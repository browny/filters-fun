cmake_minimum_required(VERSION 2.8)

SET(LIBEFFECT_SRC blur.cpp bokeh.cpp gamma.cpp noise.cpp vignet.cpp)

ADD_LIBRARY(effect_dynamic SHARED ${LIBEFFECT_SRC})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	# Mac OS X specific code
	TARGET_LINK_LIBRARIES(
		effect_dynamic
		${PROJECT_SOURCE_DIR}/lib/libopencv_core.2.3.1.dylib
		${PROJECT_SOURCE_DIR}/lib/libopencv_highgui.2.3.1.dylib
		${PROJECT_SOURCE_DIR}/lib/libopencv_imgproc.2.3.1.dylib
		${PROJECT_SOURCE_DIR}/lib/libopencv_features2d.2.3.1.dylib
	)
	SET(OperatingSystem "Mac OS X")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	# Linux specific code
	TARGET_LINK_LIBRARIES(
		effect_dynamic
		${PROJECT_SOURCE_DIR}/lib/libopencv_core.so.2.3.1
		${PROJECT_SOURCE_DIR}/lib/libopencv_highgui.so.2.3.1
		${PROJECT_SOURCE_DIR}/lib/libopencv_imgproc.so.2.3.1
		${PROJECT_SOURCE_DIR}/lib/libopencv_features2d.so.2.3.1
	)
	SET(OperatingSystem "Linux")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

SET_TARGET_PROPERTIES(effect_dynamic PROPERTIES OUTPUT_NAME "effect")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


