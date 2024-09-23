CCC=g++
CCFLAGS=-Wall -std=c++11
TARGET_DIR:=out

07: 07_ICompare.cpp
	$(CCC) $^ -o $(TARGET_DIR)/$@ $(CCFLAGS)

06: 06_Compare.cpp
	$(CCC) $^ -o $(TARGET_DIR)/$@ $(CCFLAGS)

05: 05_Erase_HtmlStripper.cpp 03_ReplaceAll.cpp
	$(CCC) $^ -o $(TARGET_DIR)/$@ $(CCFLAGS)

03: 03_Replace.cpp 03_ReplaceAll.cpp
	$(CCC) $^ -o $(TARGET_DIR)/$@ $(CCFLAGS)

all: check_dir 03 05 06 07

clean:
	rm -rf $(TARGET_DIR)

check_dir:
ifeq ("$(wildcard $(TARGET_DIR))", "")
	mkdir $(TARGET_DIR)
endif

# .DEFAULT_GOAL := all