project("AnyonGameEngine")

file(GLOB AGE_HEADERS "*.hpp")
file(GLOB AGE_SOURCES "*.cpp")

if(APPLE)
	set(PLATFORM_NAME "mac")
	file(GLOB AGE_PLATFORM_SOURCES "${PLATFORM_NAME}/*.h" "${PLATFORM_NAME}/*.m" "${PLATFORM_NAME}/*.mm" "${PLATFORM_NAME}/PlatformWrapper.cpp")
endif()

include_directories("${PROJECT_SOURCE_DIR}/${PLATFORM_NAME}")

source_group("" FILES ${AGE_HEADERS} ${AGE_SOURCES})
source_group("${PLATFORM_NAME}" FILES ${AGE_PLATFORM_SOURCES})

add_library("AGE" STATIC ${AGE_HEADERS} ${AGE_SOURCES} ${AGE_PLATFORM_SOURCES})