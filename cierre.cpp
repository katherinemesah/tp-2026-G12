#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

//comandas_dd-mm-aaaa.dat

struct Comanda {
    char fecha[11]; //DD-MM-AAAA
    int idMozo;
	int codigoProducto;
	int cantidad;
	float comision;
};

//comadas_semana_sX-mm.dat
//
// struct Comanda {
//     char fecha[11]; //DD-MM-AAAA
//     int idMozo;
// 	int codigoProducto;
// 	int cantidad;
// 	float comision;
// };

int buscarMozo(Mozo mozos[], int len, char nombreBuscado[]){
    int i = 0;
    while(i<len && strcmp(mozos[i].nombre, nombreBuscado) != 0){
        i++;
    }
    if(i==len){
        return -1;
    }else{
        return i;
    }
}

void copiarHoja(const char* nombre){
    FILE* f=fopen(nombre, "rb");
    if(f==NULL){
        cout<<"No se pudo abrir el archivo";
        return;
    }

    Comanda comandas;
    while(fread(&comandas, sizeof(Comanda), 1, f)==1){

    }
}

void crearHoja(const char* nombre, const char* comanda[]){
    FILE* f=fopen(nombre, "wb");
    if(f==NULL){
        cout<<"No se pudo crear archivo";
        return;
    }
    Comanda comanda_semanal;
    int cantidad_archivos = 7;
    while(cantidad_archivos > 0){
        copiarHoja();
        cantidad_archivos--;
    }
}

void nombrarArchivos(){
    char nombre=""
}

int main(){
  //pedir fecha y semana para armar el nombre del archivo comandas_semana

  int primer_dia_semana;
  cout<<"Primer dia de la semana:"
  cin>>primer_dia_semana;

  cout<<"Numero Semana:"
  char semana;
  cin>>semana;

  cout<<"Numero Mes:"
  char Mes;
  cin>>Mes;

  //conseguir las 7 comandas de la semana, si no existen comandas ese dia no se cargan 7:
  //
  //comandas_dd-mm-aaaa.dat
  //comandas_dd-mm-aaaa.dat
  //comandas_dd-mm-aaaa.dat
  //comandas_dd-mm-aaaa.dat
  //comandas_dd-mm-aaaa.dat
  //comandas_dd-mm-aaaa.dat
  //comandas_dd-mm-aaaa.dat

  char nombre_semana = "comandas_semana_sX-mm.dat";
  FILE* comanda_semana = crearHoja(nombre_semana);
  cout<<
   return 0;
}
