cmake_minimum_required(VERSION 3.17)
project(B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel)

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB sources "src/*.cpp")

include_directories(
        "/usr/include/irrlicht"
        ${PROJECT_SOURCE_DIR}/include
)
link_libraries(Irrlicht)
add_executable(bomberman ${sources} include/PowerUp.hpp)
