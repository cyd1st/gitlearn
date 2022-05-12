all:sscanf_s
# finish
	@echo "--finish--"

CC := gcc
VAPATH =./securec/include
INCLUDE := -I./securec/include
LIB = -L./securec

sscanf_s : test_sscanf_s.c
	$(CC) $^ -lboundscheck $(LIB) $(INCLUDE) -o out/$@


.PHONY:clean
clean:
	rm -rf *.o out/sscanf_s

.PHONY:test
# test
x:=foo
y=$(x)b
x+:=$(y)
test:
	@echo "x=>$(x)"
	@echo "y=>$(y)"