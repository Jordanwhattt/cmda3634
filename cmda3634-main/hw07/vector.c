#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"

int countLines(FILE *fp){

  char buf[BUFSIZ];
  int numberLines = 0;

  // get a label for the current position in the file
  long int start = ftell(fp);
  
  while(fgets(buf, BUFSIZ, fp)){
    ++numberLines;
  }

  // rewind back to the original start
  fseek(fp, start, SEEK_SET);

  return numberLines;
}

vector_t vectorReader(const char *fileName){

  // "open" the file to read
  FILE *fp = fopen(fileName, "r");

  // count number of lines in file
  int numberLines = countLines(fp);

  vector_t *a = vectorConstructor(numberLines);
  
  // create a buffer on the stack
  char buf[BUFSIZ];

  int n;
  for(n=0;n<numberLines;++n){
    // read a line of the file
    fgets(buf, BUFSIZ, fp);
    float vn;
    int res = sscanf(buf, "%f", &vn);
    vectorSet(*a, n, vn);
    if(res==-1){
      break;
    }
  }

  if(n!=numberLines)
    numberLines = n;
  
  // "close" the file cos we are done
  fclose(fp);


  return *a;
  
}

vector_t *vectorConstructor(int size){
  
  vector_t* a = (vector_t*)calloc(1, sizeof(vector_t));
  a->size = size;
  a->ptr = (double*) calloc(size, sizeof(double));
  return a;
}

void vectorDestructor(vector_t a){
  
  a.size = 0;
  free(a.ptr);
  a.ptr = NULL;
  
}

double vectorGet(vector_t a, int n){

  double an = (n<a.size) ? a.ptr[n]:0;
  return an;
}

void vectorSet(vector_t a, int n, double val){

  a.ptr[n] = val;
}

#define max(a,b)  ( (a>b) ? a:b )

vector_t vectorAdd(vector_t a, vector_t b){

  int maxSize = max(a.size, b.size);
  
  vector_t c = *vectorConstructor(maxSize);

  int n;
  for(n=0;n<maxSize;++n){
    double an = vectorGet(a, n);
    double bn = vectorGet(b, n);
    vectorSet(c, n, an+bn);
  }
  return c;
}

void vectorPrint(vector_t a){
  printf("vector has length %d\n", a.size);
  for(int n=0;n<a.size;++n){
    double an = vectorGet(a,n);
    printf("%lg\n", an);
  }
}

// Count the entries that a and b have in common,
// including duplicates in each
int count_commont(vector_t a,vector_t b){
  int i,j;
  int count = 0;
  for(i=0; i < a.size; ++i){
    for(j=0; j < b.size; ++j){
      if(vectorGet(a,i) == vectorGet(b,j)){
        ++count;
      }
    }
  }
}

