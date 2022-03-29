cmake_minimum_required(VERSION 3.12)

project(CSVTablePrinter)

add_library(CSVTable STATIC
"CSVTable.hpp" 
"CSVTable.cpp"
)

add_library(TablePrinter STATIC
"TablePrinter.hpp" 
"TablePrinter.cpp")
target_link_libraries(TablePrinter PUBLIC
CSVTable)

add_executable(${PROJECT_NAME} "CSVTablePrinter.cpp"  )
target_link_libraries(${PROJECT_NAME} PUBLIC
CSVTable
TablePrinter)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)

add_subdirectory(Unittests)