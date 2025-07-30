cmake_minimum_required(VERSION 3.20)
project(rpi-blinky)

find_package(Boost REQUIRED COMPONENTS program_options)

# Lets use C++23 
set(CMAKE_CXX_COMPILER g++-14)
set(CMAKE_C_COMPILER gcc-14)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(findGRPC)
include(generate_proto)

generate_proto(${CMAKE_CURRENT_SOURCE_DIR}/grpc/blinky.proto)

add_library(ledlib
    src/gpiodLed.cc
    src/simLed.cc
)

target_link_libraries(ledlib gpiod)

add_library(blinky_grpc
    src/blinky_service.cc
    ${CMAKE_CURRENT_BINARY_DIR}/blinky.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/blinky.grpc.pb.cc
)
target_link_libraries(blinky_grpc ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF} ledlib Boost::program_options) # Ideally we abstract gpio with an interface, but for simplicity we link directly to gpiod here.

target_include_directories(blinky_grpc PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(blinky src/blinky.cc)
target_link_libraries(blinky blinky_grpc)

install(TARGETS blinky
    DESTINATION ${CMAKE_INSTALL_BINDIR} RUNTIME_DEPENDENCY_SET runtime_targets)
install(RUNTIME_DEPENDENCY_SET runtime_targets PRE_EXCLUDE_REGEXES "." PRE_INCLUDE_REGEXES "gpio"
DESTINATION ${CMAKE_INSTALL_LIBDIR})