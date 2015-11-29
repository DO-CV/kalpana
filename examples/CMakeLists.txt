project(DO_Kalpana_Examples)

message(STATUS "  - DO_Kalpana_Examples")

file(GLOB examples_SRC_FILES FILES *.cpp  *.hpp)
foreach (file ${examples_SRC_FILES})
  get_filename_component(filename "${file}" NAME_WE)
  kalpana_add_example(${filename} ${file})
  target_link_libraries(
    ${filename}
    ${DO_Sara_LIBRARIES}
    DO_Kalpana_Core)
endforeach()
