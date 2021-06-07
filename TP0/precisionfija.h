#ifndef _PRECISIONFIJA_H_INCLUDED_
#define _PRECISIONFIJA_H_INCLUDED_

#include "bignum.h"
#include <regex>

struct precision_t {
  int value;
  bool isSet = false; // esta seteado por linea de argumento?
} ;

//manejo de los streams de entrada y salida, asigna los streams a los bignum
class precision_fija
{
    istream *iss_;			// stream de entrada de donde se obtendran los datos de consulta
    ostream *oss_;			// stream de salida donde se emitiran la ditancia min
    precision_fija();

public:

    precision_fija(istream &,ostream &);
    ~precision_fija();
    void captura(precision_t *);
};

#endif