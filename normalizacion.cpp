#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

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

//inventarios.cpp
