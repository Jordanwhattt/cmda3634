
#include "complex.h"
#include <stdio.h>
#include <stdlib.h>

int main(int carg, char **varg){
    if(carg != 5){
        printf("Please provide four floats\n");
        exit(-1);
    }
    float a = atof(varg[1]);
    float b = atof(varg[2]);
    float c = atof(varg[3]);
    float d = atof(varg[4]);

    // Represent the numbers a+bi and c+di
    c_num x = c_constructor(a,b);
    c_num y = c_constructor(c,d);

    char* template = "(%.4g + %.4g i)";
    char xstr[50];
    char ystr[50];
    sprintf(xstr,template,a,b);
    sprintf(ystr,template,c,d);

    c_num z;
    char zstr[50];

    printf("Inputs %s and %s\n",xstr,ystr);
    
    z = c_add(x,y);
    sprintf(zstr,template,c_real(z),c_imag(z)); 
    printf("%s + %s = %s\n",xstr,ystr,zstr);

    z = c_sub(x,y);
    sprintf(zstr,template,c_real(z),c_imag(z)); 
    printf("%s - %s = %s\n",xstr,ystr,zstr);

    z = c_mul(x,y);
    sprintf(zstr,template,c_real(z),c_imag(z)); 
    printf("%s * %s = %s\n",xstr,ystr,zstr);

    z = c_div(x,y);
    sprintf(zstr,template,c_real(z),c_imag(z)); 
    printf("%s / %s = %s\n",xstr,ystr,zstr);

    z = c_conj(x);
    sprintf(zstr,template,c_real(z),c_imag(z)); 
    printf("conj%s = %s\n",xstr,zstr);

    z = c_mod(x);
    sprintf(zstr,template,c_real(z),c_imag(z)); 
    printf("|%s| = %s\n",xstr,zstr);

}

