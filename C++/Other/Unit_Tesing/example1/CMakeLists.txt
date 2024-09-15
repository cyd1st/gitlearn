cmake_minimum_required(VERSION 3.10)
project(FactorialTest)

# 设置项目根目录
set(ROOT ../../../)

# 设置 Google Test 的源码目录，
# 注意使用 googletest-1.14.0 而不是 googletest-1.14.0/googletest
set(GTEST_SRC_DIR ${ROOT}/third_party/googletest-1.14.0/)

# 将 Google Test 作为一个子项目添加进来
add_subdirectory(${GTEST_SRC_DIR} googletest)

# 包含必要的目录
include_directories(${GTEST_SRC_DIR}/include ${GTEST_SRC_DIR})

# 查找所有测试文件
file(GLOB TEST_SOURCES "tests/*.cpp")

# 添加可执行文件
add_executable(FactorialTest ${TEST_SOURCES})

# 链接库
target_link_libraries(FactorialTest gtest gtest_main)

# 添加一个自定义目标，用于运行所有测试
add_custom_target(run_tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/FactorialTest
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running all unit tests"
    VERBATIM
)

message("To run all tests: cmake --build . --target run_tests")