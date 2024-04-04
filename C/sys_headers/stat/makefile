run_test:get_file_size
# 直接运行测试
	./$^ $^

get_file_size:get_file_size.c
	gcc $^ -o $@

.PHONY: clean
clean:
	-rm get_file_size
