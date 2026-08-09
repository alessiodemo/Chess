cmake_minimum_required(VERSION 3.2)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE release)
endif()

set(CMAKE_CXX_FLAGS, "-02")
set(CMAKE_CXX_FLAGS_DEBUG, "-02")
set(CMAKE_CXX_FLAGS_RELEASE, "-02")

project(ProgettoFinale)

add_library( chess Scacchiera/chess.h Scacchiera/chess.cpp)

add_library(Pair Scacchiera/Pair.h Scacchiera/Pair.cpp)

add_library(Pezzo Scacchiera/Pezzo.h Scacchiera/Pezzo.cpp)

add_library(Computer Giocatori/Computer.h Giocatori/Computer.cpp)

add_library(GiocatoreUmano Giocatori/GiocatoreUmano.h 
Giocatori/GiocatoreUmano.cpp)

add_library(partita Partite/Metodi.h Partite/griglia.cpp)

add_library(gameSession server/GameSession.h server/GameSession.cpp)

add_executable(scacchiera Partite/griglia.cpp)

add_executable(replay Partite/replay.cpp)

add_executable(server server/main.cpp)
target_include_directories(server PRIVATE third_party/httplib)



target_link_libraries(gameSession
chess
Pair
Pezzo
Computer
GiocatoreUmano)

target_link_libraries(server
gameSession)

if(WIN32)
target_compile_definitions(server PRIVATE _WIN32_WINNT=0x0A00 WINVER=0x0A00)
target_link_libraries(server ws2_32)
endif()

target_link_libraries(scacchiera
chess
Pair
Pezzo
Computer
GiocatoreUmano
partita)

target_link_libraries(replay
chess
Pair
Pezzo
Computer
GiocatoreUmano
partita
)
