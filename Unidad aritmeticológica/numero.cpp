#include "numero.h"
#include "bitset"

numero::numero()
{

}

numero::numero(string numero){
    setSigno(numero.substr(0,1));
    setExp(getExponenteNum(numero.substr(1,8)));
    string man_mod="1";
    setMantisa(man_mod.append(numero.substr(9,24)));
}

//GUETTERS AND SETTERS

void numero::setSigno(string sig_1){
    signo=sig_1;
}

string numero::getSigno()
{
    return signo;
}

void numero::setExp(int exp_1){
    exponente=exp_1;
}

int numero::getExp()
{
    return exponente;
}

void numero::setMantisa(string man_1){

    mantisa=man_1;
}

string numero::getMan()
{
    return mantisa;
}


//EXPONENTE

int numero::getExponenteNum(string exp){
    int cont_Exp=0;
    for(int i=0;i<exp.size();i++){
        if(exp[i]=='1'){
            cont_Exp=cont_Exp+getNumero(i);
        }
    }
    return cont_Exp-127;
}

int numero::getNumero(int pos){

    int vector[8]={128,64,32,16,8,4,2,1};
    return vector[pos];
}

string numero::complemento_a_dos(string man_normalizar){

    string vuelta;
    bool cambiar =false;

    for(int i=man_normalizar.length();i>0;i--){
        if(cambiar==false){
            if((man_normalizar.at(i-1)-48)==1){
                cambiar=true;
                vuelta="1"+vuelta;
            }
            else{
                vuelta="0"+vuelta;
            }
        }
        else{
            if((man_normalizar.at(i-1)-48)==0){
                vuelta="1"+vuelta;
            }
            else{
                vuelta="0"+vuelta;
            }
        }
    }

    return vuelta;

}

string numero::desplazarIzq_mult(string man, int numPos, int value){

    std::bitset<48> man_mod{man};
    for(int i=0;i<numPos;i++){
        for(int j=0;j<man_mod.size();j++){
            if(j==man_mod.size()-1){
                man_mod[j]=value;
            }
            else{
                man_mod[j]=man_mod[j+1];
            }
        }
    }

    std::string mystring = man_mod.to_string<char, std::char_traits<char>, std::allocator<char> >();

    return mystring;
}

string numero::desplazarDer_mult(string man, int numPos, int value){

    std::bitset<48> man_mod{man};

    for(int i=0;i<numPos;i++){
        for(int j=man_mod.size()-1;j>=0;j--){
            if(j==0){
                man_mod[j]=value;
            }
            else{
                man_mod[j]=man_mod[j-1];
            }

        }
    }
    std::string mystring = man_mod.to_string<char, std::char_traits<char>, std::allocator<char> >();

    return mystring;
}

string numero::desplazar(string man, int numPos, int value){

    std::bitset<24> man_mod{man};
    for(int i=0;i<numPos;i++){
        for(int j=0;j<man_mod.size();j++){
            if(j==man_mod.size()-1){
                man_mod[j]=value;
            }
            else{
                man_mod[j]=man_mod[j+1];
            }
        }
    }

    std::string mystring = man_mod.to_string<char, std::char_traits<char>, std::allocator<char> >();

    return mystring;
}

string numero::desplazar_derecha(string man, int veces, int value){
    std::bitset<24> man_mod{man};
    for(int i=0;i<veces;i++){
        for(int j=man_mod.size()-1;j>=0;j--){
            if(j==0){
                man_mod[j]=value;
            }
            else{
                man_mod[j]=man_mod[j-1];
            }

        }
    }

    std::string mystring = man_mod.to_string<char, std::char_traits<char>, std::allocator<char> >();

    return mystring;
}

int numero::normalizar(string p){

    int cont=0;
    for(int i=0;i<p.length();i++){
        if(p.at(i)=='1'){
            cont=i;
            break;
        }
    }

    return cont;
}

int numero::OR(string cadena){
    if(cadena.length()==1){
        return atoi(cadena.c_str());
    }else{
        int cont1 = 0;
        int cont0 = 0;
        for(int i=0;i<cadena.size();i++){
            if(cadena[i] == '0'){
                cont0 ++;
            }
            else{
                cont1 ++;
            }
        }

        if(cont0 == cadena.size()){
            return 0;
        }
        else{
            return 1;
        }
    }

}

string numero::XOR(string num1, string num2){

    if((num1=="0"&&num2=="0")||(num1=="1"&&num2=="1")){
        return "0";
    }
    else{
        return "1";
    }

}


