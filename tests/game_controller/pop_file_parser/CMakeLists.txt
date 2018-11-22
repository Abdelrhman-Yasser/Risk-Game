cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(
		
        game

        ./test.cpp

        ../../../src/game_controller/utilities/io_handler.cpp
        ../../../src/game_controller/utilities/population_file_parser.cpp

)
