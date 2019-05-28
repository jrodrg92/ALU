#include "alu.h"
#include "bitset"

using namespace std;
alu::alu()
{

}

alu::alu(numero *num1, numero *num2, string operacion_1){

    numero1=num1;
    numero2=num2;
    operacion=operacion_1;
}

//OPERACIONES

void alu::operar(){
    if(operacion=="Suma"){
        suma();
    }
    if(operacion=="Multiplicacion"){
        multiplicacion();
    }
    if(operacion=="Division"){
        division();
    }
}

//ALU


//SUMA

float alu::suma(){

    n=numero1->getMan().size();
    complemento_p=false;
    operandos_intercambiados=false;

    if(numero1->getExp()<numero2->getExp()){


        numero *aux=numero2;
        numero2=numero1;
        numero1=aux;

        operandos_intercambiados=true;

    }
    solucion->setExp(numero1->getExp());
    d=numero1->getExp()-numero2->getExp();

    if(numero1->getSigno()!=numero2->getSigno()){

        numero2->setMantisa(control->complemento_a_dos(numero2->getMan()));

    }
    p=numero2->getMan();

    g=(p.at(0)-48);
    r=(p.at(1)-48);
    st=control->OR(p.substr(2,22));

    if(d>=0){
        if(numero1->getSigno()!=numero2->getSigno()){
            p=control->desplazar(p,d,1);
        }
        else{
            p=control->desplazar(p,d,0);
        }

    }
    //Sumar Mantisas

    string ac_p=suma_bin(p, numero1->getMan());
    c=atoi(ac_p.substr(0,1).c_str());
    p=ac_p.substr(1,24);
    if(d>=0){
        if(numero1->getSigno()!=numero2->getSigno()&&(p.at(p.length()-1)-48)==1&&c==0){
            p=control->complemento_a_dos(p);
            complemento_p=true;
        }
        else if(numero1->getSigno()==numero2->getSigno()&&c==1){
            st=r||g||st;
            r=p.at(p.length()-1)-48;
            p =control->desplazar(p,1,c);
            solucion->setExp(solucion->getExp() + 1);
        }
        else{
            k=control->normalizar(p);
            if(k == 0){
                st = r||st;
                r=g;
            }
            else if(k>1){
                r = 0;
                st= 0;
            }

            p=control->desplazar_derecha(p,k,g);

            solucion->setExp(solucion->getExp()-k);
        }
    }

    //REDONDEO
    if((r==1&&st==1)||(r==1&&st==0&&p.at(p.length()-1))){
        string ac_p_1=suma_bin(p, "1");

        int c_1=atoi(ac_p_1.substr(0,1).c_str());
        p=ac_p_1.substr(1,24);

        if(c_1==1){
            p=control->desplazar_derecha(p,1,c_1);
            solucion->setExp(solucion->getExp()+1);
        }

    }

    solucion->setMantisa(p);
    if(operandos_intercambiados==false&&complemento_p==true){
        solucion->setSigno(numero2->getSigno());
    }

    else{
        solucion->setSigno(numero1->getSigno());
    }

    cout<<"Sig sol "+solucion->getSigno()<<endl;
    cout<<solucion->getExp()<<endl;
    cout<<"Sig man "+solucion->getMan()<<endl;
}

//MULTIPLICACION

float alu::multiplicacion(){

    //calcular signo de la multiplicacion

    solucion->setSigno(control->XOR(numero1->getSigno(),numero2->getSigno()));

    //Calcular el exponente del producto

    solucion->setExp(numero1->getExp()+numero2->getExp());

    //Calculo de mantisa

    string mult=multiplicacion_bin_sinSig(numero1->getMan(),numero2->getMan());
    p=mult.substr(0,24);
    string a=mult.substr(24,24);

    if(p.at(0)=='0'){
       string desplazamiento=control->desplazarDer_mult(p+a,1,0);
       p=desplazamiento.substr(0,24);
       a=desplazamiento.substr(24,24);
    }
    else{
        solucion->setExp(solucion->getExp()+1);
    }

    r=a.at(0)-48;
    st=control->OR(a.substr(1,24));


    cout<<r<<endl;
    cout<<st<<endl;
    cout<<p.at(p.length()-1)<<endl;

    if((r==1&&st==1)||(r==1&&st==0&&p.at(p.length()-1)=='0')){
        p=suma_bin(p,"1").substr(1,24);
    }
    solucion->setMantisa(p);


    cout<<"Sig sol "+solucion->getSigno()<<endl;
    cout<<solucion->getExp()<<endl;
    cout<<"Sig man "+solucion->getMan()<<endl;

}

float alu::division(){

}

//OTRAS OPERACIONES

string alu::multiplicacion_bin_sinSig(string man1, string man2){

    //multiplicacion binaria sin signo

    string c_1;
    string p_p="0";
    //Repetir bucle numero de bits de la mantisa

    for(int i=0;i<man1.length();i++){

        //Si man1(man1.length()-1)==1 se suma p_p con man2

        if(man1.at(man1.length()-1)=='1'){
            cout<<man2<<endl;
            string suma=suma_bin(p_p, man2);
            c_1=suma.substr(0,1);
            p_p=suma.substr(1,24);
        }
        else{
            string suma=suma_bin(p_p, "0");
            c_1=suma.substr(0,1);
            p_p=suma.substr(1,24);
        }
        cout<<p_p+man1<<endl;
        string concatenado=control->desplazarIzq_mult(p_p+man1,1,atoi(c_1.c_str()));
        p_p=concatenado.substr(0,24);
        man1=concatenado.substr(24,24);
    }

    return p_p.append(man1);


}

string alu::suma_bin(string cad1, string cad2){
    if(cad1.length()>cad2.length()){
        int dif=cad1.length()-cad2.length();
        for(int i=0;i<dif;i++){
            cad2="0"+cad2;
        }
    }
    if(cad1.length()<cad2.length()){
        int dif=cad2.length()-cad1.length();
        for(int i=0;i<dif;i++){
            cad1="0"+cad1;
        }
    }
    string resul="";
    int acarreo=0;

    for(int i=cad1.length()-1;i>=0;i--){
        int aux=(cad1.at(i)-48)+(cad2.at(i)-48);
        if(aux+acarreo==0){
            resul="0"+ resul;
            acarreo=0;
        }
        else if(aux+acarreo==1){
            resul="1"+resul;
            acarreo=0;
        }
        else if(aux+acarreo==2){
            resul="0"+resul;
            acarreo=1;
        }
        else{
            resul="1"+resul;
            acarreo=1;
        }
    }

    resul=std::to_string(acarreo)+""+resul;
    return resul;
}
