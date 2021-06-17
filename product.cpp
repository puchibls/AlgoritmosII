#include <iostream>
#include "product.h"
#include "bignum.h"

using namespace std;

/*Implementacion de las sub-clases derivadas de la clase product*/

bignum karatof_mul::multi(const bignum& a, const bignum& b)
{ return karatof(a, b); } //Definida en bignum.cpp

bignum classic_mul::multi(const bignum& a, const bignum& b)  
{ return classic(a, b); } //Definida en bignum.cpp
