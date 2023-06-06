SET(OUT_NAME Common)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
SET(APPLICATION_DIR ${CMAKE_SOURCE_DIR}/CommonLib/Common)

file(GLOB SRC ${APPLICATION_DIR}/*.*)
SOURCE_GROUP(Src FILES ${SRC})


if(${BUILD_SHARED_LIBS} STREQUAL "On")
    add_library(
    	${OUT_NAME} SHARED 
    	${SRC}
		)
    ADD_DEFINITIONS(-DCOMMON_LIBRARY)
	#说明1.DCOMMON_LIBRARY中COMMON为库名称
else()
    add_library(
    	${OUT_NAME} STATIC 
    	${SRC}
    	)
    ADD_DEFINITIONS(-DCOMMON_LIBRARY_STATIC)
	#说明2.DCOMMON_LIBRARY_STATIC中COMMON为库名称
endif()

target_link_libraries(
    ${OUT_NAME}
	${OPENSCENEGRAPH_LIBRARIES}
	#说明3.此处添加依赖库
	)