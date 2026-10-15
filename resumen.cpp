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
        if (!(cin>> Semana))
            return 1;
    SemanaValida = ( Semana >= '1' && Semana <= '6');
    if (!SemanaValida)
        cout <<"Semana Invalida,ingrese otro numero."<<endl;
    }
    char MesIngresado [50] ;
    char MesArchvo [3];
    int Longitud;
    int Mes;
    bool MesValido = false ;
    while (!MesValido) {
        cout << "Ingresa el mes que quiere:"<<"(En 2 digitos)"<<endl;
        if (!(cin >> MesIngresado )) {
                cout <<"Error en el me ingresado,intente de nuevo"<<endl;
            return 1;
            }
        Longitud = 0;
        while (MesIngresado[Longitud] != '\0') {
            Longitud ++;
        }            if (Longitud == 2 && MesIngresado [0] >= '0' && MesIngresado [0] <= '9' && MesIngresado [1] >= '0' && MesIngresado [1] <= '9')
            {
                    Mes = (MesIngresado[0] - '0') * 10 + (MesIngresado [1] - '0');
            if (Mes >= 1 && Mes <= 12) {
                    MesArchvo [0] = MesIngresado [0] ;
                    MesArchvo [1] = MesIngresado [1] ;
                    MesArchvo [2] = '\0' ;
                    MesValido = true ;
                    } else {
                        cout << "Error en el mes ingresado,intente de nuevo"<<endl;
                        }
            } else {
            cout << "Ingrese 2 digitos"<<endl;
            }
    }
char NombreArchivo [50] ;
int i=0;
char Inicio[] = "comandas_semana_s";
for (int j=0; Inicio[j] != '\0' ; j++) {
    NombreArchivo[i] = Inicio [j];
    i++;
}
NombreArchivo [i] = Semana;
i++;
NombreArchivo [i] = '-';
i++;
for (int j= 0; MesArchvo [j] != '\0'; j++) {
    NombreArchivo [i] = MesArchvo[j];
    i++;
}
char Extension[] = ".dat";
for (int j=0; Extension [j] != '\0' ; j++) {
    NombreArchivo [i] = Extension [j];
    i++;
}
NombreArchivo [i] = '\0' ;
cout << "Archivo a procesar" << NombreArchivo <<endl;

FILE* fsemana = fopen(NombreArchivo, "rb");
if (fsemana == NULL) {
    cout <<"Error,no se pudo abrir el archivo"<<" "<<NombreArchivo<<endl;
        return 1;
    }

    cout << "Resumen del cierre:" << NombreArchivo << "=" <<endl;

    Comanda C;
    bool MozoSi = false;
    int MozoActual = 0 ;
    long ProductosMozo = 0 ;
    float ComisionMozo = 0 ;
    long TotalProductos = 0;
    return 0;
}
