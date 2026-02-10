cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries")

#--------------------------------------------------------------------
# Source and executable
#--------------------------------------------------------------------
file(GLOB_RECURSE MDASH_SOURCE
    CONFIGURE_DEPENDS
    "Source/*.cxx"
    "Source/*.hxx"
)

add_executable(mdash ${MDASH_SOURCE})

#--------------------------------------------------------------------
# Compile definitions
#--------------------------------------------------------------------
target_compile_definitions(mdash PRIVATE
    $<$<CONFIG:Debug>:MDASH_BUILD_TYPE_DEBUG=1>
    $<$<CONFIG:Release>:MDASH_BUILD_TYPE_RELEASE=1>
    $<$<CONFIG:RelWithDebInfo>:MDASH_BUILD_TYPE_RELWITHDEBINFO=1>
    # $<IF:$<CONFIG:Debug>,SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE,SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_WARN>
)

#--------------------------------------------------------------------
# Include dirs
#--------------------------------------------------------------------
target_include_directories(mdash PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

#--------------------------------------------------------------------
# Dependencies
#--------------------------------------------------------------------

# fmt
set(FMT_INSTALL ON CACHE BOOL "Required because drogon and trantor need it" FORCE)
add_subdirectory(Dependencies/fmt)

# spdlog
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "Use external fmt library" FORCE)
set(SPDLOG_INSTALL ON CACHE BOOL "Required because drogon and trantor need it" FORCE)
add_subdirectory(Dependencies/spdlog)

# drogon
set(BUILD_EXAMPLES OFF CACHE BOOL "Build drogon examples" FORCE)
add_subdirectory(Dependencies/drogon)

# link libraries
target_link_libraries(mdash PRIVATE 
    fmt::fmt
    spdlog::spdlog
    drogon
)

# Hack for drogon and trantor spdlog support
target_link_libraries(drogon PUBLIC spdlog::spdlog)
target_compile_definitions(drogon PUBLIC DROGON_SPDLOG_SUPPORT SPDLOG_FMT_EXTERNAL)
target_link_libraries(trantor PUBLIC spdlog::spdlog)
target_compile_definitions(trantor PUBLIC TRANTOR_SPDLOG_SUPPORT SPDLOG_FMT_EXTERNAL)
