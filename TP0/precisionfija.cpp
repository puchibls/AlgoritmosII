#include "precisionfija.h"

using namespace std;
precision_fija::precision_fija()
{
}
precision_fija::precision_fija(istream &iss, ostream &oss){
    iss_ = &iss;
    oss_ = &oss;
}
precision_fija::~precision_fija(){
    
}
void precision_fija::captura(precision_t *precision){
    
    string s; //se almacenará la lína 
    smatch m; // ver regex c++, se almacenará las "captura" realizadas por el regex
    static bool entry_error=false;

    //validacion regex---> https://regex101.com/  consultar: ^(\d+|\-\d+|\+\d+)\s*(\+|\*|\-)\s*(\d+|\-\d+|\+\d+)$
    //\s --> matches any whitespace character (equivalent to [\r\n\t\f\v ])
    regex e ("^(\\d+|\\-\\d+|\\+\\d+)\\s*(\\+|\\*|\\-)\\s*(\\d+|\\-\\d+|\\+\\d+)$"); 

    // Recibo el flujo isstream y lo guarda en un string
    while (getline(*iss_, s)){
        if (s.empty() == true){ // si la linea está vacía,
                *oss_<<"Finished program"<<endl;       
                break;
        }
        if (std::regex_search (s,m,e)) { //true: A match was found within the string.
            //for (auto x:m) std::cout << x << ".."; realiza lo mismo que el for de abajo
            //for (unsigned i=0; i<m.size(); ++i) {
            //    cout << "[" << m[i] << "] ";
            //}
            /////////////////////////////////////////////////////////////////////////////////    
            // m.str(i)
            // En i=0 se encuentra toda el string, i=1 1er bignum, i=2 la operacion, i=3 2do bignum
            string a=m.str(1); 
            string b=m.str(3);

            int precision_a = precision->isSet ? precision->value : a.length();
            int precision_b = precision->isSet ? precision->value : b.length();
            //cout<<precision_a<<" "<<precision_b<<endl;
            bignum aa(a, precision_a);
            bignum bb(b, precision_b);
            switch (m.str(2)[0])
            {
            case '+':
                *oss_ << aa + bb; 
                break;
            case '-':
                *oss_ << aa - bb;
                break;
            case '*':
                *oss_ << aa * bb;
                break;
            default:
                // validado desde el regex, no es posible que llegue acá;
                break;
            }
            s = m.suffix().str(); // captura el "\n" (o cualquier otro caracter que no haya sido procesado por regex) de la 
                                  // línea dejando al objeto match "ready" para la siguiente captura
         }
         else{ 
            *oss_<<"Entry not processed"<<endl;
            entry_error=true;
         }
    } 
    if (iss_->bad()) {
        cerr << "cannot read from input stream."
        << endl;
        exit(1);
    }
    if(entry_error) {
        exit(1); //el programa terminará con valor no nulo ya que hubo al menos un error en el procesamiento de operaciones.
    }
}