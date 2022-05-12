all:sscanf_s test
# finish
	@echo "--finish--"

CC := gcc
VAPATH =./securec/include
INCLUDE := -I./securec/include
LIB = -L./securec


sscanf_s : test_sscanf_s.c
	$(CC) $^ -lboundscheck $(LIB) $(INCLUDE) -o out/$@

# test
x:=foo
y=$(x)b
x+:=$(y)


.PHONY:clean
clean:
	rm -rf *.o out/sscanf_s

.PHONY:test
	@echo "x=>$(x)"
	@echo "y=>$(y)"