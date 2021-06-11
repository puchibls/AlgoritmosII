#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <regex>
#define MAX_PRECISION 10000
using namespace std;

struct precision_t {
	int value;
	bool isSet; // esta seteado por linea de argumento?
	precision_t(bool set){
	  this->isSet = set;
  	}
};
extern precision_t preciseness;
extern bool FLAG_CLASSIC; // Hay que definirla false por defecto 

typedef enum {POS, NEG} sign_t;

class bignum
{
private:
	unsigned short *digits;
	int dim;
	sign_t sign;

	friend void copy_array(unsigned short *dest, unsigned short *orig, int n);
	friend bignum karatof(const bignum& a, const bignum& b);
	friend bignum _karatof(const bignum& a, const bignum& b);
	friend bignum classic(const bignum& a, const bignum& b);

	int resize(unsigned short *&a, int n);
	bool mayor(unsigned short *v1, size_t n1, unsigned short *v2, size_t n2);
	bool modulo_igual(unsigned short *v1, int n1, unsigned short *v2, int n2);
	unsigned short *resta(unsigned short *a, int na, unsigned short *b, int nb, int &nc);
	bignum add_zeros(int ceros, bool inicio);
	bool es_cero() const;

public:

	bignum();
	bignum(int);
	bignum(const bignum&);
	bignum(std::string&, int); 
	bignum(const unsigned short*, int n, sign_t signo); 
	~bignum();

	
	bignum& operator=(const bignum&);
	friend bignum operator*(const bignum& a, const bignum& b); 
	friend bignum operator*(const bignum& a, const unsigned short b); 
	friend bignum operator+(const bignum& a, const bignum& b);
	friend bignum operator-(const bignum& a, const bignum& b);
	friend std::ostream& operator<<(std::ostream&, const bignum&);
	friend std::istream& operator>>(std::istream&, bignum&);
};

#endif