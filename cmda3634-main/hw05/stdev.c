#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Count the number of lines
int countLines(FILE *fp) {

  char buf[BUFSIZ];
  int numberLines = 0;

  //get a label for the current position in the file
  long int start = 0;

  while(fgets(buf, BUFSIZ, fp)) {
    ++numberLines;
  }
  fseek(fp,start,SEEK_SET);
  return numberLines;
}

//Calculate the Sum
float sum(float *col, int numberLines) {
  float summ = 0;
  for(int i = 0; i < numberLines; i++) {
    summ += col[i];
  }

  return summ;
}

//Calculate the mean
float meanCol(float *col,int numberLines) {
  return sum(col,numberLines) / numberLines;
}
 
//Calculate the Standard Deviation
float stanDev(float *col, float mean, int numberLines) {

  //Create a new array to store the difference between
  //the column and the mean of that column
  float *diff = (float*) malloc(numberLines*sizeof(float));
  float variance;
  float standard_deviation;
  for(int i = 0; i < numberLines; i++) {
    //calculate the difference and square the result in each
    //entry
    diff[i] = col[i] - mean;
    diff[i] = pow(diff[i],2);
  }

  //Calcuate the Variance
  variance = sum(diff, numberLines)/(numberLines - 1);

  //Calculate and return the Standard Deviation
  return sqrt(variance);
}


int main(int argc, char **argv) {

  //open the file
  FILE *fp = fopen(argv[1],"r");

  //get the number of Lines in the File fp
  int numberLines = countLines(fp);

  //create a data array by dynamically
  float *col1 = (float*) malloc(numberLines*sizeof(float));
  float *col2 = (float*) malloc(numberLines*sizeof(float));
  
  char buf[BUFSIZ];
  int n;
  
  for(n=0; n<numberLines;++n) {
    //read a line of the File
    fgets(buf, BUFSIZ, fp);
    int res = sscanf(buf, "%f %f", col1+n, col2+n);
    if(res == -1) {
      break;
    }   
  }

  
  //close the file
  fclose(fp);

  
  //calculate the means
  float mean_1 = meanCol(col1, numberLines);
  float mean_2 = meanCol(col2, numberLines);
  //calculate the standard deviation
  float st_dev_1 = stanDev(col1, mean_1, numberLines);
  float st_dev_2 = stanDev(col2, mean_2, numberLines);
  printf("%f %f\n", st_dev_1, st_dev_2);
  
}
