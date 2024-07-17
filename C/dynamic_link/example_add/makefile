CC = gcc
CFLAGS = -Wall -fPIC
OUT_DIR = ../out

all: $(OUT_DIR)/libadd.so
	@echo "build libadd.so"

$(OUT_DIR)/libadd.so: $(OUT_DIR)/add.o
	$(CC) -shared -o $@ $^

$(OUT_DIR)/add.o: add.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/libadd.so