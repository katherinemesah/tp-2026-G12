#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

struct ComandaHistorica{
  char fecha[11]; //DD-MM-AAAA
  char nombreMozo[50];
  int codigoProducto;
  int cantidad;
  float comision;
};

struct Mozo {
    int IdMozo;
    char nombre[50];
    char password[20];
    float totalComision;
};

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

    ComandaHistorica comandas;
    while(fread(&comandas, sizeof(ComandaHistorica), 1, f)==1){

    }
}

void crearHoja(const char* nombre, const char* comanda[]){
    FILE* f=fopen(nombre, "wb");
    if(f==NULL){
        cout<<"No se pudo crear archivo";
        return;
    }
    ComandaHistorica comanda_semanal;
    int cantidad_archivos = 7;
    while(cantidad_archivos > 0){
        copiarHoja();
        cantidad_archivos--;
    }
}

int main(){
  int semana = 1;
  char nombre_semana = "comandas_semana_s" << semana << "_01.dat";
  FILE* comanda_semana = crearHoja(nombre_semana);

   return 0;
}
