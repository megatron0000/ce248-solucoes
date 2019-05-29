#include <unistd.h>

int main(int argc, char const *argv[]) {
	char* args[2];
	args[0] = "./test";
	args[1] = "1";
	execve("./test", args, NULL);
	return 0; 
}