cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Set to your project name!
set(GAME_NAME "Game")

set(BUILD_TESTING OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

project(${GAME_NAME})

file(GLOB GAME_SOURCES "*.hpp" "*.cpp")

source_group("" FILES ${GAME_SOURCES})

include_directories("${PROJECT_SOURCE_DIR}/Anyon")

if(APPLE)
	set(CMAKE_XCODE_ATTRIBUTE_GCC_ENABLE_OBJC_EXCEPTIONS NO)
	set(CMAKE_XCODE_ATTRIBUTE_GCC_ENABLE_CPP_EXCEPTIONS NO)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit -framework QuartzCore -framework OpenGL")
endif()

add_executable(${GAME_NAME} MACOSX_BUNDLE ${GAME_SOURCES})

add_subdirectory("Anyon")

target_link_libraries(${GAME_NAME} "Anyon")
