cmake_minimum_required(VERSION 2.8.12)
set(DO_Kalpana_VERSION 0.1.0)

project(Kalpana)

if (POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif ()

# List of build options.
option(KALPANA_BUILD_SAMPLES "Build samples in Kalpana libraries" OFF)


# ============================================================================ #
# Set default build type to Release mode.
set(CMAKE_BUILD_TYPE "Release"
  CACHE STRING "Build type options are: Debug, Release")

set(BUILD_SHARED_LIBS ${KALPANA_BUILD_SHARED_LIBS})


# ============================================================================ #
# State the list of dependencies.
if (WIN32)
  set(DO_Sara_DIR "C:/Program Files/DO-Sara")
else ()
  set(DO_Sara_DIR /usr/include)
endif ()

set(DO_Kalpana_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DO_Kalpana_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/DO/Kalpana)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${DO_Sara_DIR}/include/DO/Sara/cmake)

# Use custom CMake macros.
include(kalpana_configure_cxx_compiler)
include(kalpana_macros)


# ============================================================================ #
# Build the following directories.
#
include_directories(
  ${DO_Sara_INCLUDE_DIRS}
  src)

# Group projects by category.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)

if (KALPANA_BUILD_SAMPLES)
  add_subdirectory(examples)
endif ()
