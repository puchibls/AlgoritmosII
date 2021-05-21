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
    cout << digits[dim - i - 1]; 

cout << ", "  << (sign ? "NEGATIVO" : "POSITIVO") << endl;
}

bignum bignum::operator+(const bignum&a)
{
    size_t new_dim;
    a.dim > dim ? new_dim = a.dim + 1 : new_dim = dim + 1;
    bignum b(new_dim);
    if(a.sign == sign)
        b.sign = a.sign;
    int carry = 0;
    int i = 0;
    while(i < b.dim)
    {
        if(i < dim && i < a.dim)
        {
            b.digits[i] = (a.digits[i] + digits[i] + carry) % 10;
            carry = (a.digits[i] + digits[i] + carry) / 10;
            i++;
        }    
        else if(i >= dim && i < a.dim)
        {
            b.digits[i] = (a.digits[i] + carry) % 10;
            carry = (a.digits[i] + carry) / 10;
            i++;
        }
        else if(i >= a.dim && i < dim)
        {
            b.digits[i] = (digits[i] + carry) % 10;
            carry = (digits[i] + carry) / 10;
            i++;
        }
    }
    b.digits[i] = carry;
    return b;
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
