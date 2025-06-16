# CMakeList.txt : CMake project for HxDGraal, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.27)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# CMake setup
set(BUILD_SHARED_LIBS ON)
set(CMAKE_SHARED_LIBRARY_ENABLE_EXPORTS ON)
set(ENABLE_EXPORTS ON)

# Project setup
project(HxDGraal LANGUAGES CXX)

# Add library.
add_library(HxDGraal SHARED)

# Annoying.
#include(GenerateExportHeader)
#generate_export_header(HxDGraal)

# Compiler setup
set_property(TARGET HxDGraal PROPERTY CXX_STANDARD 23)
target_compile_definitions(HxDGraal PUBLIC UNICODE _UNICODE)

# Includes
target_include_directories(HxDGraal PRIVATE "include")
target_sources(HxDGraal PUBLIC FILE_SET HEADERS BASE_DIRS "include")

# Source
add_subdirectory(src)

# Install
install(TARGETS HxDGraal)
