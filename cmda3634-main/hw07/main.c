#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"

// added a comment
int main(int argc, char **argv){

  vector_t a, b, c;

  a = vectorReader("a.dat");
  b = vectorReader("b.dat");
  c = vectorAdd(a,b);

  vectorPrint(c);
  int common = count_commont(a,b);
  printf("a and b have %d entries in common.\n",common);

  vectorDestructor(a);
  vectorDestructor(b);
}

