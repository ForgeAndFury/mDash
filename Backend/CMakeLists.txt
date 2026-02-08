cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--------------------------------------------------------------------
# Source and executable
#--------------------------------------------------------------------
file(GLOB_RECURSE MDASH_SOURCE
    CONFIGURE_DEPENDS
    "Source/*.cxx"
    "Source/*.hxx"
)

# 3. Create the executable
add_executable(mDash ${MDASH_SOURCE})

#--------------------------------------------------------------------
# Compile definitions
#--------------------------------------------------------------------
target_compile_definitions(mDash
    PUBLIC
        $<$<CONFIG:Debug>:MDASH_BUILD_TYPE_DEBUG=1>
        $<$<CONFIG:Release>:MDASH_BUILD_TYPE_RELEASE=1>
        $<$<CONFIG:RelWithDebInfo>:MDASH_BUILD_TYPE_RELWITHDEBINFO=1>
        # $<IF:$<CONFIG:Debug>,SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE,SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_WARN>

)

#--------------------------------------------------------------------
# Include dirs
#--------------------------------------------------------------------
target_include_directories(mDash PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

#--------------------------------------------------------------------
# Dependencies
#--------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF)

set(FMT_INSTALL OFF)
add_subdirectory(Dependencies/fmt)
target_link_libraries(mDash PRIVATE fmt::fmt)

set(SPDLOG_FMT_EXTERNAL ON)
add_subdirectory(Dependencies/spdlog)
target_link_libraries(mDash PRIVATE spdlog::spdlog)

set(JSONCPP_WITH_TESTS OFF)
set(JSONCPP_WITH_CMAKE_PACKAGE OFF)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)
set(BUILD_OBJECT_LIBS OFF)
add_subdirectory(Dependencies/jsoncpp)
target_link_libraries(mDash PRIVATE jsoncpp::jsoncpp)

set(BUILD_EXAMPLES OFF)
set(USE_SPDLOG ON)
add_subdirectory(Dependencies/drogon)


# # 5. Copy the Frontend files to the build directory so the app can find them
# add_custom_command(TARGET mDash POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/Source/Frontend/public
#     ${CMAKE_BINARY_DIR}/public)
