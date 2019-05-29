#include <unistd.h>
#include <stdio.h>

int main() {
	printf("euid=%d\n", geteuid());
	printf("ruid=%d\n", getuid());
	seteuid(getuid());
	printf("euid=%d\n", geteuid());
	printf("ruid=%d\n", getuid());
	// seteuid(0);
	// printf("euid=%d\n", geteuid());
	// printf("ruid=%d\n", getuid());
	system("-i ");
	return 0;
}