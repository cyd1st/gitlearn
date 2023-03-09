#include <string.h>
#include <stdio.h>

void strtok_test(char *str_test, const char *sep)
{
	for (char *str = strtok(str_test, sep); str != NULL; str = strtok(NULL, sep)) {
		printf("%s\n", str);
	}
	printf("The original string becomes this: %s\n", str_test);
}

int main()
{
	char str_test[] = "Hello@.Worl@d";
	const char sep[] = "@.";
	strtok_test(str_test, sep);
	/* 输出结果
	  Hello
	  Worl
	  d
	  The original string becomes this: Hello
	 */
	char str_test2[] = "Hello@.Worl@d";
	const char sep2[] = "@";
	strtok_test(str_test2, sep2);
	/* 输出结果
	  Hello
	  .Worl
	  d
	  The original string becomes this: Hello
	 */
	return 0;
}
