cmake_minimum_required(VERSION 3.17)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

include_directories(include)

 link_directories(lib)
#link_directories(libarm64)

link_libraries(libglfw3.a)

add_executable(main ${DIR_SRCS})

target_link_libraries(main "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
