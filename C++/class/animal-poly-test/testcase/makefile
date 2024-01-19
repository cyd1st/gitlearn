# 定义变量
CPP = g++
GTEST_DIR = ../../../third_party/googletest-1.14.0/googletest
INCLUDES = -I$(GTEST_DIR)/include
LIBS = -L$(GTEST_DIR)/../build/lib -lgtest -lgtest -lpthread

# 源文件和目标文件
OUT_DIR = ../out/testcase
# 判断输出目录是否存在，不存在则创建
ifeq ($(wildcard $(OUT_DIR)),)
$(shell mkdir -p $(OUT_DIR))
endif

SRC = test_Dog.cpp
OBJ = $(addprefix $(OUT_DIR)/, $(SRC:.cpp=.o))
EXECUTABLE = $(addprefix $(OUT_DIR)/, test_Dog)

# DEBUG
# $(info SRC = $(SRC))
# $(info OBJ = $(OBJ))

# 编译
all:$(EXECUTABLE)


$(EXECUTABLE): $(OBJ)
	$(CPP) $(INCLUDES) -o $@ $(OBJ) $(LIBS)

$(OUT_DIR)/%.o: %.cpp
	$(CPP) $(INCLUDES) -c -o $@ $<


# 清理
clean:
	rm -rf $(OBJ) $(OUT_DIR)

# 运行测试
run:
	./$(EXECUTABLE)
