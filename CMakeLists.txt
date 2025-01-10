cmake_minimum_required(VERSION 3.7)

set (CMAKE_CXX_STANDARD 11)

project (Domotico VERSION 0.1)

include_directories(include)

add_library(Domotico
    include/cp.h
    include/device.h
    include/m.h
    include/system.h
    include/time.h
    src/cp.cpp
    src/device.cpp
    src/m.cpp
    src/system.cpp
    src/time.cpp
)

add_executable(main
    src/main.cpp
)

target_link_libraries(main
    mainb
)