cmake_minimum_required(VERSION 3.28)

# Set output directory
set(MDASH_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<LOWER_CASE:$<CONFIG>>")
set(MDASH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/$<LOWER_CASE:$<CONFIG>>")
#                                                     #  Linux        Windows
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MDASH_LIB_DIR})  #  .a           .lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MDASH_BIN_DIR})  #  .so          .dll (explicit loading)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MDASH_BIN_DIR})  #  executable   .exe, .dll (implicit loading)

project(mDash)

add_subdirectory(Backend)
