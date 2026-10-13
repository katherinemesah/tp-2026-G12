#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

//Actualizar stock, se toman los dos primeros structs
//comandas_historicas.cpp
struct ComandaHistoric{
  char fecha[11]; //DD-MM-AAAA
  char nombreMozo[50]; //nombre completo, repetido en cada venta
  char codigoProducto;
  int cantidad;
  float comision;
};

struct Producto{
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;
};

struct Mozo{
  int idMozo;
  char nombre[50];
  char password[20];
  float total Comision;
};

struct Comanda{
  int idMozo;
  int codigoProducto;
  int cantidad;
  float comision;
};
//inventarios.cpp
// const floar TASA_COMISION=0.10f; Comision de cada venta es el 10% de lo vendido

void cifrarClave(char clave[], int k);

int main(){

    return 0;
}

void cifraarClave(char clave[], int k){

    for(int i=0; clave[i]!=0; i++){
        clave[i]=clave[i]+k;
    }
}