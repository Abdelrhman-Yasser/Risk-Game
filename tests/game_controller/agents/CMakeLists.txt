cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(
		
        game

        ./test.cpp

        ../../../src/game_controller/utilities/io_handler.cpp
        ../../../src/game_controller/utilities/file_parser.cpp

        ../../../src/game_controller/environment/environment.cpp
        ../../../src/game_controller/game_controller.cpp

        ../../../src/graphics_controller/cli_controller/game_set_visualizer.cpp

        ../../../src/game_controller/player/player_factory.cpp
        ../../../src/game_controller/player/player.cpp
        ../../../src/game_controller/player/humans/human.cpp
        ../../../src/game_controller/player/agents/simple_agents/passive_agent.cpp
        ../../../src/game_controller/player/agents/simple_agents/aggressive_agent.cpp


)
