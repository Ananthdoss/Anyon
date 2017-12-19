project("Anyon")

file(GLOB ANYON_SOURCES "*.hpp" "*.cpp")

if(APPLE)
	set(PLATFORM_NAME "mac")
	set(RENDERER_NAME "gl")

	add_definitions(-DANYON_APPLE -DANYON_MAC -DANYON_GL)

	file(GLOB ANYON_PLATFORM_SOURCES "${PLATFORM_NAME}/*.h" "${PLATFORM_NAME}/*.m" "${PLATFORM_NAME}/*.mm" "${PLATFORM_NAME}/PlatformWrapper.cpp")
endif()

include_directories("${PROJECT_SOURCE_DIR}/${PLATFORM_NAME}")
source_group("${PLATFORM_NAME}" FILES ${ANYON_PLATFORM_SOURCES})

include_directories("${PROJECT_SOURCE_DIR}/${RENDERER_NAME}")
file(GLOB ANYON_RENDERER_SOURCES "${RENDERER_NAME}/*.hpp" "${RENDERER_NAME}/*.cpp")
source_group("${RENDERER_NAME}" FILES ${ANYON_RENDERER_SOURCES})

source_group("" FILES ${ANYON_SOURCES})

add_library("Anyon" STATIC ${ANYON_SOURCES} ${ANYON_PLATFORM_SOURCES} ${ANYON_RENDERER_SOURCES})
