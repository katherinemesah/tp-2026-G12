#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

struct comandasHistoricas{
  char fecha[11]; //DD/MM/AAAA
  char nombreMozo[50];
  int codProducto;
  int cantidad;
  float comision;
};

struct Producto{
 int codigo;
 char descripcion[50];
 float precio;
 int stock;
};

struct Mozo{
  int idMozo;
  char nombre[50];
  char password[20];
  float tComision;
};

struct Comanda{
  char fecha[11];
  int idMozo;
  int cProducto;
  int cantidad;
  float comision;
};

int main(){

   return 0;
}
