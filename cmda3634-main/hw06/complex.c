#include <stdio.h>
#include <math.h>
#include "complex.h"

// Returns a c_num representing the complex number a+b*i
c_num c_constructor(float a, float b) {
  
  c_num x;
  x.real = a;
  x.imag = b;
  return x;
}

// Returns the real part of complex number x
float c_real(c_num x) {
  return x.real;
}

// Returns the imaginary part of complex number x
float c_imag(c_num x) {
  return x.imag;
}

// Returns the sum of the complex numbers x and y
//         x + y
c_num c_add(c_num x, c_num y) {

  float a = c_real(x);
  float b = c_imag(x);
  float c = c_real(y);
  float d = c_imag(y);

  c_num z = c_constructor(a + c, b + d);
  return z;
}

// Returns the difference of the complex numbers x and y
//         x - y
c_num c_sub(c_num x, c_num y) {

  float a = c_real(x);
  float b = c_imag(x);
  float c = c_real(y);
  float d = c_imag(y);

  c_num z = c_constructor(a - c, b - d);
  return z;
}

// Returns the product of the complex numbers x and y
//         x * y
c_num c_mul(c_num x, c_num y) {

  float a = c_real(x);
  float b = c_imag(x);
  float c = c_real(y);
  float d = c_imag(y);

  c_num z = c_constructor( (a*c - b*d), (b*c + a*d) );
  return z;
}


// Returns the quotient of the complex numbers x and y
//         x / y
// If y is zero, your code should not crash
c_num c_div(c_num x, c_num y) {

  float a = c_real(x);
  float b = c_imag(x);
  float c = c_real(y);
  float d = c_imag(y);
  
  c_num z = c_constructor( ((a*c + b*d)/(c*c + d*d)) , ((b*c - a*d)/(c*c + d*d)) ) ;
  
  return z;
}

// Returns the conjugate of the complex number x
//The conjugate in the the Real part of a complex number multiplied by -1
c_num c_conj(c_num x) {

  float a = c_real(x);
  float b = c_imag(x);
 

  c_num z = c_constructor( a,-1 * b); 
  return z;
}

// Returns the modulus of the complex number x
//         |x|
// The modulus of a complex number is the square root of the sum of the 2 parts squared
// sqrt ( real^2 + imaginary^2 )
c_num c_mod(c_num x) {

  float a = c_real(x);
  float b = c_imag(x);
  

  c_num z = c_constructor( sqrt( a*a + b*b ), 0 );
  return z;
}
