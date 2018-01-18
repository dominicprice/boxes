cmake_minimum_required (VERSION 3.0)
project(Boxes)


##############
# Preamble
##############

# Inlucde the toolchain file (vcpkg etc...)
if(CMAKE_TOOLCHAIN_FILE)
  include(${CMAKE_TOOLCHAIN_FILE})
endif()

# Point to the FindSFML.cmake file
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

# Set up compiler flags
set(CMAKE_CXX_STANDARD 14)
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	add_definitions(
	  "-D_GLIBCXX_USE_CXX11_ABI=0"
	)
endif()


##############
# Find libraries
##############

# SFML
find_package(SFML COMPONENTS graphics window system) 


##############
# Source files
##############

set(boxes_src
  "src/game_display.cpp"
  "src/game_logic.cpp"
  "src/main.cpp"
)


##############
# Make targets
##############

add_executable(boxes 
  ${boxes_src}
)
target_include_directories(boxes PUBLIC
  "src"
  "libs/cards/include")
target_link_libraries(boxes 
  ${SFML_LIBRARIES} 
)


##############
# Install targets
##############

# Executable
install(
  TARGETS
    boxes
  RUNTIME DESTINATION
    bin
)

# Resources
install(
  DIRECTORY
    ${CMAKE_SOURCE_DIR}/resources/
  DESTINATION
    share
)

# Shared libraries
if (WIN32)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(
	  FILES
	    "${CMAKE_BINARY_DIR}/freetyped.dll"
		"${CMAKE_BINARY_DIR}/jpeg62.dll"
		"${CMAKE_BINARY_DIR}/libbz2d.dll"
		"${CMAKE_BINARY_DIR}/libpng16d.dll"
		"${CMAKE_BINARY_DIR}/sfml-graphics-d-2.dll"
		"${CMAKE_BINARY_DIR}/sfml-system-d-2.dll"
		"${CMAKE_BINARY_DIR}/sfml-window-d-2.dll"
		"${CMAKE_BINARY_DIR}/zlibd1.dll"
	  DESTINATION
	    bin
	)
  else()
    install(
	  FILES
	    "${CMAKE_BINARY_DIR}/freetype.dll"
		"${CMAKE_BINARY_DIR}/jpeg62.dll"
		"${CMAKE_BINARY_DIR}/libbz2.dll"
		"${CMAKE_BINARY_DIR}/libpng16.dll"
		"${CMAKE_BINARY_DIR}/sfml-graphics-2.dll"
		"${CMAKE_BINARY_DIR}/sfml-system-2.dll"
		"${CMAKE_BINARY_DIR}/sfml-window-2.dll"
		"${CMAKE_BINARY_DIR}/zlibd1.dll"
	  DESTINATION
	    bin
	)
  endif()
endif()