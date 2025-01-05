cmake_minimum_required(VERSION 3.22)
set(BOARD nucleo_f303re)

find_package(Zephyr)
project(PlantMonitor)

file(GLOB sensors
     "src/Sensors/*.h"
     "src/Sensors/*.c"
)

target_include_directories(app PRIVATE src/Sensors/)
target_include_directories(app PRIVATE src/)

target_sources(app PRIVATE src/main.c src/DataTypes.h ${sensors})

