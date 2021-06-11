#ifndef _PRECISIONFIJA_H_INCLUDED_
#define _PRECISIONFIJA_H_INCLUDED_

#include "bignum.h"

#include <queue>
#include <set>
#include <cstring>
#include <stack>
#include <cctype>
//manejo de los streams de entrada y salida, asigna los streams a los bignum
class fixed_precision
{
    istream *iss_;			// stream de entrada de donde se obtendran los datos de consulta
    ostream *oss_;			// stream de salida donde se emitiran la ditancia min
    fixed_precision();

public:

    fixed_precision(istream &,ostream &);
    ~fixed_precision();
    void capture();
    bool shunting();
};

#endif