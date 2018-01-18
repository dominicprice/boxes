cmake_minimum_required (VERSION 3.0)
project(Boxes)

include_directories(
  "src"
  ${SFML_INCLUDE_DIRS}
)

set(boxes_src
  "src/game_display.cpp"
  "src/game_logic.cpp"
  "src/main.cpp"
)

add_executable(boxes boxes_src)
target_link_libraries(boxes ${SFML_LIBRARIES})
