cmake_minimum_required(VERSION 3.16)
project(B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB sources "src/*.cpp")
FILE(GLOB includes "include/*.hpp")

include_directories(
        "/usr/include/irrlicht"
        ${PROJECT_SOURCE_DIR}/include
)
link_libraries(Irrlicht)
add_executable(bomberman ${sources} include/EventHandling.hpp include/button_enum.hpp include/AppContext.hpp src/help_functions.cpp include/help_functions.hpp include/menu.hpp src/EventHandling.cpp)