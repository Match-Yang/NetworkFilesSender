cmake_minimum_required(VERSION 3.1)

project(NetworkFilesSender LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/plog/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE main ${CMAKE_CURRENT_SOURCE_DIR}/src/main/*)
file(GLOB_RECURSE common ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*)
file(GLOB_RECURSE controller ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/*)
file(GLOB_RECURSE qml ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/qml.qrc)

add_executable(${PROJECT_NAME} ${common} ${controller} ${main} ${qml})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Network)
