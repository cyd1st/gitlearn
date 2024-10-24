CC = clang++
TARGET_DIR = out
CCFLAGS = -Wall -g

# 创建输出目录（如果不存在）
$(shell mkdir -p $(TARGET_DIR))

# 获取目录下的所有cpp文件
SOURCES := $(wildcard *.cpp)

# 排除特定的 .cpp 文件（这些文件将单独处理）
EXCLUDE_FILES = 01_MyFILEClass.cpp 02_MyFILEClassTest.cpp 
EXCLUDE_FILES += 03_MyDate.cpp 03_Ostream.cpp
EXCLUDE_FILES += 15_CPPCHECK.cpp
SOURCES := $(filter-out $(EXCLUDE_FILES), $(SOURCES))

# 从源文件名生成目标文件名（去掉.cpp后缀，并加上输出目录路径）
TARGETS := $(addprefix $(TARGET_DIR)/, $(SOURCES:.cpp=))

# 特殊处理的目标
TARGETS += $(TARGET_DIR)/02_MyFILEClassTest
TARGETS += $(TARGET_DIR)/03_Ostream

# 默认目标：编译所有的源文件
all: $(TARGETS)

# 为每个目标文件定义规则
$(TARGET_DIR)/%: %.cpp
	$(CC) $(CCFLAGS) -o $@ $<

# 特殊处理 02_MyFILEClassTest 目标
$(TARGET_DIR)/02_MyFILEClassTest: 01_MyFILEClass.cpp 02_MyFILEClassTest.cpp
	$(CC) $(CCFLAGS) -o $@ $^

# 特殊处理 03_Ostream 目标
$(TARGET_DIR)/03_Ostream: 03_MyDate.cpp 03_Ostream.cpp
	$(CC) $(CCFLAGS) -o $@ $^

# 清理生成的目标文件
clean:
	rm -f $(TARGETS)