#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Size of square matrix
#define N 10

int
main(void)
{
  int A[N][N], B[N][N], C[N][N];
  int p[2];
  int i, j, k;

  
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = i + j;        // Example values
      B[i][j] = (i == j) ? 1 : 0; // Identity-like
      C[i][j] = 0;
    }
  }

 
  if (pipe(p) < 0) {
    printf("pipe failed\n");
    exit(1);
  }

 
  for (i = 0; i < N; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    }

    if (pid == 0) {
      // CHILD PROCESS
      close(p[0]); // child won’t read

      int row[N];
      // Compute row i of result
      for (j = 0; j < N; j++) {
        row[j] = 0;
        for (k = 0; k < N; k++) {
          row[j] += A[i][k] * B[k][j];
        }
      }

      // Write row to parent
      write(p[1], row, sizeof(row));
      close(p[1]);

      exit(0); // child done
    }
    // Parent continues loop to create next child
  }

  
  close(p[1]); // parent won’t write

  for (i = 0; i < N; i++) {
    int row[N];
    read(p[0], row, sizeof(row));
    for (j = 0; j < N; j++) {
      C[i][j] = row[j];
    }
  }
  close(p[0]);


  while (wait(0) > 0);


  printf("Result Matrix C:\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }

  exit(0);
}
