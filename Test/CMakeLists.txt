cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

project (Test)

if (MSVC)
	add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4018 /wd4005 /wd4996 /nologo" )
endif(MSVC)

if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")


	#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -O2" )
endif(EMSCRIPTEN)



add_executable (Test main.cpp)
