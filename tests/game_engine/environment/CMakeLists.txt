cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(
		
        game

        ./test.cpp
        ../../../src/game_engine/environment/environment.cpp
        ../../../src/game_engine/utilities/io_handler.cpp
        ../../../src/game_engine/utilities/map_file_parser.cpp
        ../../../src/game_engine/utilities/population_file_parser.cpp

)
