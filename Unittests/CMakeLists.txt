set(FETCHCONTENT_QUIET OFF CACHE BOOL "Disabling FetchContent quiet mode" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  #for windows

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(CSVTable_test "CSVTable_test.cpp")
target_link_libraries(CSVTable_test gtest_main pthread CSVTable)
target_include_directories(CSVTable_test PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(TablePrinter_test "TablePrinter_test.cpp")
target_link_libraries(TablePrinter_test gtest_main gmock_main pthread TablePrinter)
target_include_directories(TablePrinter_test PRIVATE ${CMAKE_SOURCE_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/data.csv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/datawill.csv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/dataEmpty.csv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/dataOne.csv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})