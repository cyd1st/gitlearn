cmake_minimum_required(VERSION 3.14)
project(FileHandlerTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含gtest
add_subdirectory(../../../third_party/googletest-1.14.0 ${CMAKE_CURRENT_BINARY_DIR}/gtest)

include_directories(
    ${PROJECT_SOURCE_DIR}/..
    ${gtest_SOURCE_DIR}/include
)

set(CMAKE_CXX_FLAGS "-fsanitize=address -g")
set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=address")

add_executable(test_file_handler
    test_file_handler.cpp
    ../file_handler.cpp
)

target_link_libraries(test_file_handler
    gtest_main
    pthread
    -lasan
)

# 添加测试清理目标
add_custom_target(clean_tests
    COMMAND ${CMAKE_COMMAND} -E remove 
        readonly.txt
        empty.txt
        nonexistent.txt
    COMMENT "Cleaning test generated files"
)

# 将清理目标与测试关联
add_test(
    NAME cleanup_test_files
    COMMAND ${CMAKE_BUILD_TOOL} clean_tests
)
