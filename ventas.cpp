#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
//Struct
struct Mozo {
    int idMozo;
    char nombre[50];
    char password[20];
    float totalComision;
};

struct Producto {
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;
};

struct Comanda {
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};
//varibles constantes
const float TASA_COMISION = 0.10f;
const int MAX_COMANDAS = 1000;
const int K = 3; 

// funcion de encriptacion
void encriptar(const char* original, char* encriptada) {
    int i = 0;
    while (original[i] != '\0') {
        encriptada[i] = original[i] + K;
        i++;
    }
    encriptada[i] = '\0';
}
// funciones buscar
long BuscarMozo(const char* nombre, int idMozo, Mozo&m){
    FILE*f =fopen(nombre , "rb");
    if(f==NULL)return -1;
    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Mozo);
    long pri = 0, ult = n - 1, pos = -1;
    while (pri <= ult && pos == -1) {
        long med = (pri + ult) / 2;
        fseek(f, med * sizeof(Mozo), SEEK_SET);
        if (fread(&m, sizeof(Mozo), 1, f)!=1){
            fclose(f);
            return-1;
        }
        if (m.idMozo == idMozo) pos = med;
        else if (idMozo > m.idMozo) pri = med + 1;
        else ult = med - 1;
 }
 fclose(f);
 return pos;
}     

long BuscarProducto(const char* nombre, int codigo, Producto&p){
    FILE*f =fopen(nombre ,"rb");
    if(f==NULL)return -1;
     fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Producto);
    long pri = 0, ult = n - 1, pos = -1;
    while (pri <= ult && pos == -1) {
        long med = (pri + ult) / 2;
        fseek(f, med * sizeof(Producto), SEEK_SET);
        if(fread(&p, sizeof(Producto), 1, f)!=1){
            fclose(f);
            return -1;
        }
        if (p.codigo == codigo) pos = med;
        else if (codigo > p.codigo) pri = med + 1;
        else ult = med - 1;
 }
 fclose(f);
 return pos;
}
