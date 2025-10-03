#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  printf("Testing performance counters:\n");
  printf("CPU Cycles: %d\n", rdcycle());
  printf("Time: %d\n", rdtime());
  printf("Instructions Retired: %d\n", rdinstret());
  exit(0);
}
