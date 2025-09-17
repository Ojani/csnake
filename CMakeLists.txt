cmake_minimum_required(VERSION 3.10)
project(csnake)

# Include all header files in the include folder
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
  src/main.c
  src/Map.c
  src/Snake.c
  src/Apple.c
)

add_executable(csnake ${SOURCES})

# Link with ncurses
find_package(Curses REQUIRED)
target_link_libraries(csnake ${CURSES_LIBRARIES})