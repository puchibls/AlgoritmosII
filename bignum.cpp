#include "bignum.h"
#include "product.h"

bignum::bignum()
{
    digits = NULL;
    dim = 0;
    sign = POS;
}
bignum::bignum(int n)
{
    digits = new unsigned short[n]();
    dim = n;
    sign = POS;
}
bignum::bignum(const bignum &a)
{
    digits = new unsigned short[a.dim];
    for(int i = 0; i < a.dim; i++)
        digits[i] = a.digits[i];
    dim = a.dim;
    sign = a.sign;
}
bignum::bignum(std::string& str, int precision)
{   
    dim = str.length();
    sign = POS;
    int j = 0; //Contador del string
    if(str.at(0) == '-') 
    {   
        sign = NEG;
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
bignum::~bignum()
{
    if(digits)
        delete []digits; 
}
void copy_array(unsigned short *dest, unsigned short *orig, int n)
{
    for(int i = 0; i < n; i++)
        dest[i] = orig[i];
}
bignum::bignum(const unsigned short *v, int n, sign_t signo) 
{
    digits = new unsigned short[n];
    for(int i = 0; i < n; i++)
        digits[i] = v[i];
    dim = n;
    sign = signo;
}
int resize(unsigned short *&a, int n) // Quita los ceros sobrantes y devuelve la nueva dim
{    
    int zeros = 0;
    while((a[n - zeros - 1] == 0) && (n - zeros - 1) > 0) zeros++;     
    unsigned short *aux = new unsigned short[n - zeros]; 
    copy_array(aux, a, n - zeros);
    delete[] a;
    a = aux; 
    return n - zeros;
}
bool bignum::is_zero() const
{
    size_t add = 0;
    for(int i = 0; i < dim; i++)
        add += digits[i];
    return add == 0;       //Suma de todos los digitos == cero == true
}
bignum bignum::add_zeros(int zeros, bool start) //inicio == false, agrega ceros al final
{
    if(zeros == 0) return *this;
    unsigned short *aux = new unsigned short[dim + zeros]();  
    start ? copy_array(aux + zeros, digits, dim) : copy_array(aux, digits, dim);
    delete []digits;
    digits = aux;
    dim += zeros;
    return *this;
}
bignum& bignum::operator=(const bignum& b)
{
    if(&b != this) 
    {
        if(dim != b.dim) 
        {
            unsigned short *aux = new unsigned short[b.dim];
            delete[] digits;
            dim = b.dim;
            sign = b.sign;
            digits = aux;
            copy_array(digits, b.digits, dim);
            return *this;
        }
        else 
        {
            sign = b.sign;
            copy_array(digits, b.digits, dim);
            return *this; 
        }
    }    
    return *this;
}
bignum classic(const bignum& a, const bignum& b) 
{
    int large = a.dim + b.dim;

    bignum r(large);
    for (int k = 0; k < b.dim; k++)
    {
        bignum multi(a.dim + 2 + k);
        multi = a * b.digits[k];
        r = r + multi.add_zeros(k, true);
    }
    b.sign == a.sign ? r.sign = POS : r.sign = NEG; //cout << "Multiplicacion Classic" << endl;
    return r;
}
bignum karatof(const bignum&a, const bignum& b)
{
    bignum aa(a);
    bignum bb(b);
    bignum result;
    sign_t sign;
    b.sign == a.sign ? sign = POS : sign = NEG;
    
    if(aa.dim == 1)
    {
        result = bb * aa.digits[0];   //Para mejorar eficiencia: bignum * digito
        result.sign = sign;
        return result;
    }
    if(bb.dim == 1)
    {
        result = aa * bb.digits[0];
        result.sign = sign;
        return result;
    }
    aa.sign = POS;                 //Operacion con ambos numeros positivos  
    bb.sign = POS;
    result = _karatof(aa, bb);
    result.sign = sign;            //cout << "Multiplicacion Karatsuba" << endl;
    return result;
}
bignum _karatof(bignum& a, bignum& b) 
{
    if(a.is_zero() || b.is_zero())     //Para mayor eficiencia, bignum de dim > 1 con todos ceros
    {    
        bignum zero(1);                  //Retorna un bignum 0 de dim 1
        return zero;
    }
    if(a.dim == 1 && b.dim > 1)             //Caso base
        return b * a.digits[0];
    if(b.dim == 1 && a.dim > 1)             //Caso base
        return a * b.digits[0];

    int n = a.dim;
    if(a.dim > b.dim)          
    {
        n = a.dim;
        if(n & 1)               // si es impar hace n+1 y cambia las dos dim
        {
            n++;
            a.add_zeros(n - a.dim, false);
            b.add_zeros(n - b.dim, false);
        }
        else
            b.add_zeros(n - b.dim, false);
    }
    if(b.dim > a.dim)
    {
        n = b.dim;
        if(n & 1)
        {
            n++;
            a.add_zeros(n - a.dim, false);
            b.add_zeros(n - b.dim, false);
        }
        else
            a.add_zeros(n - a.dim, false);
    } 
    if((n & 1) && (n > 1))      // caso en que dim a = dim b y son impares
    { 
        n++;             
        a.add_zeros(n - a.dim, false);
        b.add_zeros(n - b.dim, false);     
    }
    int k = n / 2;
    if(n == 1)                           //CONDICION BASE: dim == 1, multiplicacion entre 2 digitos
    {
        unsigned short mul = a.digits[0] * b.digits[0];
        if(mul > 9)
        {
            bignum m(2);
            m.digits[0] = mul % 10;
            m.digits[1] = mul / 10;
            return m;
        }
        bignum m(1);
        m.digits[0] = mul;
        return m;
    }
    bignum a0(a.digits + k, n - k, POS);     // a = |---a0---||---a1---|
    bignum a1(a.digits, n - k, POS);     
    bignum b0(b.digits + k, n - k, POS);     // b = |---b0---||---b1---|
    bignum b1(b.digits, n - k, POS);
    bignum c1 = a0 + a1;
    bignum c2 = b0 + b1;
    bignum c = _karatof(c1, c2);
    bignum d = _karatof(a0, b0);
    bignum e = _karatof(a1, b1);
    bignum dd(d);
    dd.add_zeros(n, true);       // dd = d * 10^2k = d * 10^n 
    bignum subs = c - d - e;        
    subs.add_zeros(k, true);     // subs = (c - d - e) * 10^k 
    return dd + subs + e; 
}
bignum operator*(const bignum& a, const bignum& b) 
{
    bignum result;
    product *p;

    if(FLAG_CLASSIC == true)
    {
	p = new classic_mul;
        result = p->multi(a, b);
        delete p;
	return result; 
    }
    else
    {
	p = new karatof_mul;
	result = p->multi(a, b);
        delete p;
	return result;
    }	
}
bignum operator*(const bignum& a, const unsigned short b) 
{
    bignum result(a.dim + 1);
    int i = 0;
    unsigned short carry = 0;
    for (; i < a.dim; )
    {
        unsigned short multi = 0;
        multi = a.digits[i] * b;
        if(multi + carry > 9)     
            result.digits[i] = (multi + carry) % 10;
        else
            result.digits[i] = multi + carry;
        result.digits[i + 1] = (multi + carry) / 10;
        carry = 0;
        carry = result.digits[i + 1];  
        i++;
    }
    result.dim = resize(result.digits, result.dim); //ojo
    return result;
}
bignum operator+(const bignum& a, const bignum& b)
{
    int new_dim;
    a.dim > b.dim ? new_dim = a.dim + 1 : new_dim = b.dim + 1;
    bignum c(new_dim);
    if(a.sign && !b.sign) // a < 0 y b > 0 --> c = b - a
    {   
        bignum aa(a);
        aa.sign = POS;
        c = b - aa;
        return c;
    }
    if(!a.sign && b.sign) // a > 0 y b < 0 --> c = a - b
    {   
        bignum bb(b);
        bb.sign = POS;
        c = a - bb;
        return c;
    }
    c.sign = a.sign;
    int na = 0; int nb = 0;
    for(int i = 0; i < new_dim; i++)
    {
        unsigned short carry = 0;
        unsigned short add = 0;
        add = ((na < a.dim) ? a.digits[na++] : 0)  
                            + ((nb < b.dim) ? b.digits[nb++] : 0) 
                            + c.digits[i];
        carry = add / 10; 
        c.digits[i] = add % 10;
        if(i < new_dim - 1)
            c.digits[i + 1] = carry; 
    }              
    c.dim = resize(c.digits, new_dim);
    return c;
}

bool bigger(unsigned short *v1, size_t n1, unsigned short *v2, size_t n2)
{
    if(n1 > n2)
        return true;
    if(n1 < n2)
        return false;    
    else {
        size_t i = n1 - 1;    
        while(v1[i] == v2[i]) i--;
        if(v1[i] > v2[i]) return true;
        return false;    
    }    
}
bool equal_module(unsigned short *v1, int n1, unsigned short *v2, int n2)
{
    if(n1 != n2) return false;

    for(int i = 0; i < n1; i++)
        if(v1[i] != v2[i]) return false;
    return true;
}
unsigned short *substract(unsigned short *a, int na, unsigned short *b, int nb, int &nc)
{
    unsigned short *c = new unsigned short[na]();
    nc = na;

    for(int i = 0; i < nb; i++)
    {
        if(a[i] < b[i])             //Pide carry   
        {
            a[i] += 10; 
            c[i] = a[i] - b[i];
            if(a[i + 1] != 0)       //Si el que sigue no es cero le resta 1
                a[i + 1]--;
            else                    //Si es cero, sigue hasta encontrar un num > 0
            {
                int j = i + 1;
                while(a[j] == 0)
                {    
                    a[j] = 9;
                    j++;
                }
                a[j]--;
            }    
        }
        else if(a[i] > b[i])
            c[i] = a[i] - b[i];
        else c[i] = 0;        
    }
    for(int i = nb; i < na; i++)    //Completa los restantes
        c[i] = a[i];
    
    if(c[na - 1] == 0)              //Si cambia la dimension de la resta, la ajusta   
        nc = resize(c, na);
    return c; 
}
bignum operator-(const bignum& a, const bignum& b)
{  
    bignum c; // c.digits = {0};
    int dim_c;

    unsigned short *aux;
    if(equal_module(b.digits, b.dim, a.digits, a.dim))
    {    
        if(!(b.sign ^ a.sign)) return c; // XNOR: a = b = true o a = b = false --> c = 0
        c = a + a;
        if(b.sign)
            return c;     // b < 0 y a = b --> c = a + a
        c.sign = NEG;           // a < 0 y a = b --> c = -(a + a)
        return c; 
    }
    if(a.sign && !b.sign)        // a < 0 y b > 0 --> c = -(a + b) 
    {
        bignum aa(a);
        aa.sign = POS;
        c = aa + b;
        c.sign = NEG;
        return c;
    }
    if(!a.sign && b.sign)        // a > 0 y b < 0 --> c = a + b 
    {
        bignum bb(b);
        bb.sign = POS;
        c = a + bb;
        return c;      
    }
    if(bigger(b.digits, b.dim, a.digits, a.dim)) //  b > a --> c = -(b - a) 
    {
        aux = substract(b.digits, b.dim, a.digits, a.dim, dim_c);
        c.digits = new unsigned short[dim_c];
        c.dim = dim_c;
        if(!a.sign)                           // b > a, a > 0 y b > 0 --> c < 0          
            c.sign = NEG;
        copy_array(c.digits, aux, dim_c);
        delete []aux;
        return c;
    }                                                       // a > b --> c = a - b                        
    aux = substract(a.digits, a.dim, b.digits, b.dim, dim_c);
    c.digits = new unsigned short[dim_c];
    c.dim = dim_c;
    if(a.sign)                  // a > b, a < 0 y b < 0 --> c < 0
        c.sign = NEG;
    copy_array(c.digits, aux, dim_c);
    delete []aux;
    return c;
}
std::ostream& operator<<(std::ostream& oss_, const bignum& out){
	if(out.dim == 0 || ( out.dim == 1 && out.digits[0]==0)){
        //std::cout<<"La dimension es cero!"<<std::endl;
        oss_<<'0';
    }
    else{
        oss_<< (out.sign ? "-" : "");
        for(int i=out.dim; i!=0; i--){
            //std::cout<<"Imprimo como un campeon "<<std::endl;
            //std::cout<<"La dimension es: "<<out.dim<<std::endl;
        
		    oss_<< out.digits[i-1];
	    }
    }
    oss_<<"\n";
    return oss_;
}
/**
    * Sobrecarga del operador de ingreso.
    *
    * @param [out] iss_ Se trabaja sobre el istream, el cual llega por referencia
    * @param [out] in Se carga el bignum cargado por usuario, con la precisión especificada por en el inicio del programa
    * @return El istream iss_
*/
std::istream& operator>>(std::istream& iss_, bignum& in){

    string s;
    iss_>> s;
    regex e ("^(\\d+|\\-\\d+)"); //ej: 54848181 ó -54545454 ---> nro positivos o negativos 
    smatch m;                    //ej: -546de$w será -546 || Cualquier otra combinacion de caracteres se asigna 0  
    if (std::regex_search (s,m,e) && (m.str(1).length()< MAX_PRECISION)) { //Tiene que pasar el regex y el strin resultante
        string s_parse=m.str(1);                                           //tener una longitud menor que la precision maxima por diseño
        int precision_parse = preciseness.isSet ? preciseness.value : s_parse.length();
        bignum parse(s_parse, precision_parse);
        //le asigno al bignum 
        in = parse;
    }else{ 
        //sino pasa el regex, se le asigna cero.
        string s_parse="0";
        bignum parse(s_parse, s_parse.length());
        in = parse;
    }
    return iss_;
    
}
