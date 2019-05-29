#include <unistd.h>
#include <stdio.h>

int some_function() {
	return 0;
}

int main() {
	some_function();
	setuid(0);
	printf("euid=%d\n", geteuid());
	printf("ruid=%d\n", getuid());
	return  0;
}