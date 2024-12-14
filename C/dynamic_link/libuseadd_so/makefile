CC = gcc
CFLAGS = -Wall -fPIC
OUT_DIR = ../out

all: $(OUT_DIR)/libuseadd.so
	@echo "build libuseadd.so"

$(OUT_DIR)/libuseadd.so: $(OUT_DIR)/useadd.o
	$(CC) -shared $^ -o $@

$(OUT_DIR)/useadd.o: use_add.c
	$(CC) -fPIC -c $^ -o $@

clean:
	rm -f $(OUT_DIR)/libuseadd.so