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
    string Mes ;
    bool MesValido = false ;
    while (!MesValido) {
        cout << "Ingresa el mes que quiere;"<<endl;
        if (!(cin >> Mes ))
            return 1;
        MesValido = (Mes.length() == 2);
        if ( MesValido) {
                if (Mes[0] < '0' || Mes [0] > '9' || Mes [1] < '0' || Mes [1] > '9') {
                    MesValido = false;
                } else {
                int NumerodeMes = (Mes[0] - '0') * 10 + (Mes [1] - '0');
                if (NumerodeMes < 1 || NumerodeMes > 12) MesValido= false ;
                }
        }
        if (!MesValido) cout << "Mes no valido,ingrese otro." << endl;
    }

    return 0;
}
