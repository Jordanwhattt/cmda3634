#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    printf("usage: %s n\n", argv[0]);
    exit(-1);
  }
  int n = atoi(argv[1]);
  int i = 0; 
  //printf("n=%d a_0=%d\n ", n, i);
  printf("%d",n);
  while(n != 1){
    
    if (n % 2 == 0) {
      n = n/2;
    }
    else {
      n = 3 * n + 1;
    }
    printf(",%d",n);
  }
  printf("\n");
  
}
