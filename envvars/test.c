#include <stdio.h>
#include <unistd.h>

extern char** environ;
int main(int argc, char const* argv[]) {
  printf("RUID=%d\n", getuid());
  printf("EUID=%d\n", geteuid());
  int result = open("/tmp/x", 0);
  printf("Permission=%d\n", result);
  for (int i = 0; environ[i] != NULL; ++i) {
    printf("%s\n", environ[i]);
  }
  if (argc < 2) {
  	return 0;
  } else if (*argv[1] == 1) {
  	char* args[1];
  	args[0] = 0;
  	execve("./test", args, NULL);
  }
  return 0;
}