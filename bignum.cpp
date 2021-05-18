#include <iostream>
#include "bignum.h"
#include <string>

using namespace std;

bignum::bignum()
{
    digits = NULL;
    dim = 0;
    sign = false;
}

bignum::bignum(bignum& a)
{
    digits = new unsigned short[a.dim];
    dim = a.dim;
    sign = a.sign;
}

bignum::bignum(std::string& str, int precision)
{   
    dim = str.length();
    sign = false;
    int j = 0; //Contador del string
    if(str.at(0) == '-') 
    {   
        sign = true;
        precision++; //Contemplo el '-' en la precision
        dim--;
        j++;
    }
    digits = new unsigned short[dim];    
    for(int i = dim - 1; i >= 0; i--) 
    {
        if(j < precision)
        { 
            char c = str.at(j++);      
            digits[i] = c - '0'; 
        }
        else
            digits[i] = 0;
    }
}

bignum::bignum(size_t n)
{
    digits = new unsigned short[n];
    dim = n;
    sign = false;
}

bignum::~bignum()
{
    if(digits)
        delete []digits; 
}

void bignum::emitir_bignum()
{
for(int i = 0; i < dim; i++)
    cout << digits[i]; 

cout << ", "  << (sign ? "NEGATIVO" : "POSITIVO") << endl;
}

int main(void)
{
    string str;
    int precision;
    cin >> str;
    cin >> precision;
    bignum a(str, precision);
    a.emitir_bignum();
}
