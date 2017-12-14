project("Anyon")

file(GLOB ANYON_HEADERS "*.hpp")
file(GLOB ANYON_SOURCES "*.cpp")

if(APPLE)
	set(PLATFORM_NAME "mac")
	file(GLOB ANYON_PLATFORM_SOURCES "${PLATFORM_NAME}/*.h" "${PLATFORM_NAME}/*.m" "${PLATFORM_NAME}/*.mm" "${PLATFORM_NAME}/PlatformWrapper.cpp")
endif()

include_directories("${PROJECT_SOURCE_DIR}/${PLATFORM_NAME}")

source_group("" FILES ${ANYON_HEADERS} ${ANYON_SOURCES})
source_group("${PLATFORM_NAME}" FILES ${ANYON_PLATFORM_SOURCES})

add_library("Anyon" STATIC ${ANYON_HEADERS} ${ANYON_SOURCES} ${ANYON_PLATFORM_SOURCES})