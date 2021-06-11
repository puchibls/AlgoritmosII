#ifndef _PRODUCT_H_INCLUDED_
#define _PRODUCT_H_INCLUDED_

#include <iostream>
#include "bignum.h"

using namespace std;

class product   // Clase Abstracta
{ 
public:
    virtual bignum multi(const bignum& a, const bignum& b)=0;
	virtual ~product(){}; 
};

class karatof_mul: public product	// Clase Heredada
{
public:
	virtual bignum multi(const bignum& a, const bignum& b);
};

class classic_mul: public product	// Clase Heredada
{
public:
	virtual bignum multi(const bignum& a, const bignum& b);
};

#endif
