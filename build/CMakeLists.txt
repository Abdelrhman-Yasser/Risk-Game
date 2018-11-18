cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(
		
        game

        ../src/main.cpp

        ../src/game_controller/game_controller.cpp
        ../src/game_controller/environment/environment.cpp
        ../src/game_controller/utilities/file_handler.cpp
        ../src/game_controller/player/player.cpp

        ../src/game_controller/player/player_factory.cpp
        ../src/game_controller/player/humans/human.cpp
        ../src/game_controller/player/agents/greedy_agent.cpp


)
