cmake_minimum_required(VERSION 3.12)
project(mp3looper C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Use pkg-config to find sndfile
find_package(PkgConfig REQUIRED)
pkg_check_modules(SNDFILE REQUIRED sndfile)

find_library(LAME_LIBRARY NAMES mp3lame)
find_path(LAME_INCLUDE_DIR lame/lame.h)

if(NOT LAME_LIBRARY OR NOT LAME_INCLUDE_DIR)
	message(FATAL_ERROR "lame library not found")
endif()

find_library(MATH_LIBRARY m)

include_directories(
	include
	${LAME_INCLUDE_DIR}
	${SNDFILE_INCLUDE_DIRS}
	${MPG123_INCLUDE_DIRS}
)

link_directories(${SNDFILE_LIBRARY_DIRS})

file(GLOB_RECURSE SRC_FILES 
	src/*.c
	include/*.h
)

pkg_check_modules(MPG123 REQUIRED libmpg123)

add_executable(mp3_loop
	${SRC_FILES}
)

target_link_libraries(mp3_loop
	${SNDFILE_LIBRARIES}
	${LAME_LIBRARY}
	${MPG123_LIBRARIES}
	${MATH_LIBRARY}
)


install(TARGETS mp3_loop
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)

