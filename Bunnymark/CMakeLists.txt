cmake_minimum_required (VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)

project (Bunnymark)

if (MSVC)
	add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4018 /wd4005 /wd4996 /nologo" )
endif(MSVC)


add_executable (Bunnymark main.cpp)



if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	add_definitions("-std=c++14")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 --use-preload-plugins")
	set_target_properties(Bunnymark PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s USE_SDL_IMAGE=2 --use-preload-plugins --preload-file ../data")

elseif()
	include(FindPkgConfig)
	pkg_search_module(SDL2 REQUIRED sdl2)
	pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)

	include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

	target_link_libraries(Bunnymark ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )
endif(EMSCRIPTEN)
