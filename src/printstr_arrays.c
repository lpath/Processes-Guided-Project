#include <stdio.h>

void print_str(char *s)
{
	int i;
	char *p = s;

	for (i = 0; s[i] != '\0'; i++) {
		putchar(s[i]);
	}

	for (i = 0; *(s+i) != '\0'; i++) {
		putchar(*(s+i));
	}

	for (; *s != '\0'; s++) {
		putchar(*s);
	}

	s = p;

	while (*s != '\0') {
		putchar(*(s++));
	}
}

int main(void)
{
	print_str("Hello, world!\n");

	return 0;
}
