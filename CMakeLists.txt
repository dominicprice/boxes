cmake_minimum_required (VERSION 3.0)
project(Boxes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
find_package(SFML COMPONENTS graphics window system) 

include_directories(
  "src"
  ${SFML_INCLUDE_DIRS}
)
add_definitions(
  "-D_GLIBCXX_USE_CXX11_ABI=0"
)

set(boxes_src
  "src/game_display.cpp"
  "src/game_logic.cpp"
  "src/main.cpp"
)

add_executable(boxes 
  ${boxes_src}
)
target_link_libraries(boxes 
  ${SFML_LIBRARIES} 
  "-lpthread"
)
