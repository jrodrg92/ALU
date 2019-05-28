#ifndef NUMERO_H
#define NUMERO_H
#include "string.h"
#include <iostream>
#include <vector>

using namespace std;

class numero
{
public:
    numero();
    numero(string numero);


    //GETTERS AND SETTERS
    void setSigno(string sig_1);
    string getSigno();
    void setExp(int exp_1);
    int getExp();
    void setMantisa(string man_1);
    string getMan();

    //EXPONENTE

    int getExponenteNum(string exp);
    int getNumero(int pos);

    //NORMALIZAR MANTISA

    string complemento_a_dos(string man_normalizar);

    string desplazar(string man, int numPos, int value);

    string desplazar_derecha(string man, int veces, int value);

    string desplazarDer_mult(string man, int numPos, int value);

    string desplazarIzq_mult(string man, int numPos, int value);


    int normalizar(string p);

    int OR(string cadena);

    string XOR(string num1, string num2);


private:
    string signo;
    int exponente;
    string mantisa;
};

#endif // NUMERO_H
