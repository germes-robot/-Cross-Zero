cmake_minimum_required(VERSION 3.15)
project(HW_02)



set(flags "-lncurses")
set(superflags "-Werror -Wall -Wextra -pedantic -lncurses")

SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${superflags}")
set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(/usr/include/)


add_executable(test src/StdioBoardView.cpp include/StdioBoardView.h
        src/Board.cpp include/Board.h test/Test.cpp include/Test.h test/BoardTest.cpp
        include/BoardTest.h test/test.cpp)

add_executable(HW_02 src/main.cpp
        src/StdioBoardView.cpp
        include/StdioBoardView.h
        src/Board.cpp
        include/Board.h src/NCursesBoardView.cpp include/NCursesBoardView.h)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries (HW_02 ${CURSES_LIBRARIES})
endif()
