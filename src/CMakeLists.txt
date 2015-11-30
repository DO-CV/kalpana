set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)

if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()


kalpana_dissect_version(${DO_Kalpana_VERSION})


# Set output directories.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Create the following libraries.
set(DO_Kalpana_LIBRARIES 2D 3D Plot)
foreach (library ${DO_Kalpana_LIBRARIES})
  kalpana_glob_directory(${DO_Kalpana_SOURCE_DIR}/${library})
  kalpana_create_common_variables("${library}")
  kalpana_generate_library("${library}")

  if (NOT ${library} STREQUAL "Plot")
    target_link_libraries(DO_Kalpana_${library}
      Qt5::Core Qt5::Widgets Qt5::OpenGL)
  endif ()
endforeach ()
