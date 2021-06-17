#include <stack>
#include <iostream>
#include <set>
#include <cstring>
#include <queue>
#include "bignum.h"
using namespace std;
#include <stack>

class numero_grande{
	public:
	int num;

	numero_grande(){}
	numero_grande(int numero){
		this->num = numero;
	}
	~numero_grande(){}
	int getNum(){
		return num;
	}

	virtual numero_grande& operator*(numero_grande& )=0; 
};

class mult1: public numero_grande{ //herencia de clases en privada por defecto
	public:
	mult1(){
		numero_grande::num =0;
	}
	mult1(int num_in){
		numero_grande::num = num_in;
	}
	numero_grande& operator*(numero_grande& num_grande){
			static mult1 result(this->num  * num_grande.num + 1);
			return result;
	}
};
class mult2:public numero_grande{
	public:
	mult2(int num){
		numero_grande::num = num;
	}
	numero_grande& operator*(numero_grande& num_grande){
			static mult2 result(this->num  * num_grande.num);
			return result;
	}
	//numero_grande& operator*(numero_grande& num_grande){
	//		int result;
	//		result = numero_grande::num  * num_grande::
	//}
};

//Base class
class cola_bignum
{
	public:
	cola_bignum(){
	}
	
	virtual void Print(ostream& os)=0;

	~cola_bignum(){
	}
	virtual bool isBignum()=0;
};
std::ostream& operator<<(ostream& os, cola_bignum& loc) 
{ 
    loc.Print(os); 
    return os; 
}
// Sub class inheriting from Base Class(Parent)
class bignum_child : public cola_bignum
{
	int bignum;
    public:
      bignum_child(int a){
        bignum=a;
      }
	void Print(ostream& os){
		os << this->bignum;
	}
	bool isBignum(){
		return true;
	}
};

class bignum_operator : public cola_bignum
{
	char op;
  public:
  bignum_operator(char c){
    op = c;
  }
  void Print(ostream& os){
		os << this->op;
  }
  bool isBignum(){
	  return false;
  }
};


//main function
int main()
   {
	bignum_child a(10);
	bignum_operator b('+');

	mult1 num1(32);
	mult1 num3(10);
	mult2 num2(32);

	std::cout <<(num1*num3).getNum()<<endl;
	std::cout <<(num2*num3).getNum()<<endl;

	

	//mult1 result= num1*num2 ;


	/*

	std::cout<< a << endl;
	std::cout<< b << endl;

	if (a.isBignum())
		std::cout<< "soy un bignum"<<endl;
	else
		std::cout<< "No soy un bignum"<<endl;

		*/
    return 0;
   }