#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main() {
  char *str;
  str = malloc(10);
  read(STDIN_FILENO, &str, 8);
  write(STDOUT_FILENO ,8, &str);
  return 0;
}