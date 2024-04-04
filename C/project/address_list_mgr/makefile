vpath %.c ./src
vpath %.h ./include
CC=gcc
CFLAGS= -I./include
SRC_LIST=main.c address_list.c

addresslist:$(SRC_LIST)
	$(CC) $(CFLAGS) $^ -o out/addresslist