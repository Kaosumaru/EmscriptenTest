cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

project (Bunnymark)

if (MSVC)
	add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4018 /wd4005 /wd4996 /nologo" )
endif(MSVC)

if (EMSCRIPTEN)

endif(EMSCRIPTEN)



add_executable (Bunnymark main.cpp)

if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")

	add_definitions("-std=c++14")
	#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -O2" )

	set_target_properties(Bunnymark PROPERTIES LINK_FLAGS "-s USE_SDL=2 --preload-file bunny.png")

endif(EMSCRIPTEN)
