
#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct{

  float imag;
  float real;
    
} c_num;

// ---------------------------------------------
// DO NOT modify this file below this point.
// Your file complex.c should have the code for
// the definitions (bodies) of the functions
// whose declarations (heads) are below.
// ---------------------------------------------


// Returns a c_num representing the complex number a+b*i
c_num c_constructor(float a,float b);

// Returns the real part of complex number x
float c_real(c_num x);

// Returns the imaginary part of complex number x
float c_imag(c_num x);

// Returns the sum of the complex numbers x and y
//         x + y
c_num c_add(c_num x,c_num y);

// Returns the difference of the complex numbers x and y
//         x - y
c_num c_sub(c_num x,c_num y);

// Returns the product of the complex numbers x and y
//         x * y
c_num c_mul(c_num x,c_num y);

// Returns the quotient of the complex numbers x and y
//         x / y
// If y is zero, your code should not crash
c_num c_div(c_num x,c_num y);

// Returns the conjugate of the complex number x
c_num c_conj(c_num x);

// Returns the modulus of the complex number x
//         |x|
c_num c_mod(c_num x);

#endif

