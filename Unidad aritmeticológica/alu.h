#ifndef ALU_H
#define ALU_H
#include "numero.h"

class alu
{
public:
    alu();
    alu(numero *num1, numero *num2, string operacion_1);
    ~alu();

    //OPERACIONES

    void operar();

    //ALU

    float suma();
    float multiplicacion();
    float division();
    
    //OTROS
    
    string suma_bin(string cad1,string cad2);
    string multiplicacion_bin_sinSig(string man1,string man2);


private:

    numero *numero1;
    numero *numero2;
    string operacion;

    //VARIABLES SUMA

    string p;
    int g;
    int r;
    int st;
    int n;
    int d;
    int c;
    int k;
    bool operandos_intercambiados;
    bool complemento_p;

    numero *solucion=new numero();
    numero *control=new numero();


};

#endif // ALU_H
