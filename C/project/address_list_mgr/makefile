vpath %.c ./src
vpath %.h ./include
CC=gcc
CFLAGS=-I./include
SRC_LIST=main.c address_list.c
TARGET_DIR=out

all: check_dir addresslist

addresslist: $(SRC_LIST)
	$(CC) $(CFLAGS) $^ -o $(TARGET_DIR)/$@

check_dir:
ifeq ("$(wildcard $(TARGET_DIR))", "")
	mkdir $(TARGET_DIR)
endif

clean:
	rm -rf $(TARGET_DIR)

# .PHONY: all clean