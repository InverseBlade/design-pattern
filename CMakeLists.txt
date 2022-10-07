cmake_minimum_required(VERSION 3.12)

project(DM)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src/ SRC_LIST)

add_executable(DM ${SRC_LIST})

include_directories(./src)

link_directories(./src)

# target_link_libraries(DM -lglfw3)
