cmake_minimum_required(VERSION 3.17)
project(bomberman)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(Irrlicht_DIR "${CMAKE_MODULE_PATH}/Irrlicht")

find_package(Irrlicht REQUIRED)

include_directories(${Irrlicht_INCLUDE_DIRS})
FILE(GLOB sources "src/*.cpp")
FILE(GLOB includes "include/*.hpp")

include_directories(
        "/usr/include/irrlicht"
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} ${sources} ${includes})


target_link_libraries(${PROJECT_NAME} ${Irrlicht_LIBRARIES})
target_link_libraries(${PROJECT_NAME} -lsfml-audio)


set(DLL_IRRLICHT ${Irrlicht_DIR}/Irrlicht.dll)
file(GLOB DLL_FILES ${DLL_IRRLICHT})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${DLL_IRRLICHT} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES ${DLL_FILES} DESTINATION bin)
