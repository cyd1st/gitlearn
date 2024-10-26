CC = clang++
CCFLAGS = -Wall -g
CC_SHARED_FLAGS = -fPIC
LDFLAGS = -shared
OUT_DIR = out

$(shell mkdir -p $(OUT_DIR))

all: DataLogger 01_DataGen 01_DataScan

DataLogger: 01_DataLogger.cpp
	$(CC) $^ -o $(OUT_DIR)/lib$@.so $(CCFLAGS) $(CC_SHARED_FLAGS) $(LDFLAGS)

01_DataGen: 01_DataGen.cpp 01_DataLogger.cpp
	$(CC) $^ -o $(OUT_DIR)/$@ $(CCFLAGS)

01_DataScan: 01_DataScan.cpp 01_DataLogger.cpp
	$(CC) $^ -o $(OUT_DIR)/$@ $(CCFLAGS)