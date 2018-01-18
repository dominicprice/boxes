file(GLOB dll_list ${CMAKE_BINARY_DIR} "*.dll")
install(
  FILES
    dll_list
  DESTINATION
    bin
)