#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

struct Comanda {
    int idmozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

void VerMozo (int idmozo,long productos,float comision) {
cout << "Mozo" << idmozo <<endl;
cout << "Productos Vendidos" << productos <<endl;
cout << "Comision Correspondiente:$" << comision << endl;
}
int main()
{
    char Semana = '0' ;
    bool SemanaValida = false ;
    while (!SemanaValida) {
        cout <<" Ingrese la semana que quiere:"<<endl;
        if (!(cin>> Semana)) return 1;
    SemanaValida = ( Semana >= '1' && Semana <= '6');
    if (!SemanaValida)
        cout <<"Semana Invalida,ingrese otro numero."<<endl;
    }

    return 0;
}
