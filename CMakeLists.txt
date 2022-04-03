cmake_minimum_required(VERSION 3.12)

project(CSVTablePrinter)

add_library(CSVTable 
"CSVTable.hpp" 
"CSVTable.cpp"
)

add_library(TablePrinter 
"TablePrinter.hpp" 
"TablePrinter.cpp")
target_link_libraries(TablePrinter 
CSVTable)

add_executable(${PROJECT_NAME} "CSVTablePrinter.cpp"  )
target_link_libraries(${PROJECT_NAME} 
CSVTable
TablePrinter)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

add_subdirectory(Unittests)

