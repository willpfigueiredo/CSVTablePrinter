cmake_minimum_required(VERSION 3.12)

project(CSVTablePrinter)

add_executable(${PROJECT_NAME} "CSVTablePrinter.cpp" "CSVTable.hpp" "CSVTable.cpp" "TablePrinter.hpp" "TablePrinter.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)