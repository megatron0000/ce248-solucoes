#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	printf("RUID=%d\n", getuid());
	printf("EUID=%d\n", geteuid());
	int result = open("/tmp/x", 0);
	printf("Permission=%d\n", result);
	return 0; 
}