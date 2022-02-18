cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)

project(Base LANGUAGES C)

make_static_library(Base)

target_link_libraries(Base PUBLIC UxTheme.lib)

target_precompile_headers(Base PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Base/Base.h")