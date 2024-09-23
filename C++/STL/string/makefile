CFLAGS=-Wall


05: 05_Erase_HtmlStripper.cpp 03_ReplaceAll.cpp
	g++ $^ -o out/$@ $(CFLAGS)

03: 03_Replace.cpp 03_ReplaceAll.cpp
	g++ $^ -o out/$@ $(CFLAGS)

all: 05 03

# .DEFAULT_GOAL := all