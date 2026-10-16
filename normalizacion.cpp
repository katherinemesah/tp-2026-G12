#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const float TASA_COMISION=0.10f;
//Actualizar stock, se toman los dos primeros structs
//comandas_historicas.cpp
struct ComandaHistoricas{
  char fecha[11]; //DD-MM-AAAA
  char nombreMozo[50]; //nombre completo, repetido en cada venta
  int codigoProducto;
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
  float totalComision;
};

struct Comanda{
  int idMozo;
  int codigoProducto;
  int cantidad;
  float comision;
};
//inventarios.cpp
// const floar TASA_COMISION=0.10f; Comision de cada venta es el 10% de lo vendido
/*===== comandas_historicas.dat  (30 registros, DESORDENADO) =====
fecha        nombreMozo        codProd   cant   comision
02-06-2025   Sofia Ramirez         101      2     300.00
02-06-2025   Bruno Diaz            105      3     240.00
03-06-2025   Carla Lopez           110      1     320.00
===== inventario.dat  (ordenado por codigo, CON HUECOS) =====
codigo   descripcion        precio    stock
101      Cafe              1500.00       60
105      Medialuna          800.00       80
110      Tostado           3200.00       30s */

//1.Por pedido, la clave de mozo se cifra k=3
void cifrarClave(char clave[], int k);
//2.Al buscar los mozos se busca que no se repita
int buscarMozo(Mozo mozos[], int& len, char nombreBuscado[]);
//3.Se abre comandas_historicas.cpp para poder asignar el id y sumar la comision
void mozosArchivo(Mozo mozos[], int& len);

//crear archivos de ventas por dia
void ventasDiarias(Producto prod[], Comanda ventas[]);

//5.Toma las ventas en historica y se actualiza el stock
void actualizarStock(Comanda ventas[], int vlen, Productos prods[], int pLen, Mozo mozos[], int mlen);

int main(){
    const int cantMozos[50];
    const int cantProductos[100];
    const int cantVentas[100];
    const int k=3;

    Mozo mozos[cantMozos];
    Producto productos[cantProductos];
    Comanda ventas[cantVentas];

    cifrarClave(mozos, k);


    return 0;
}

//k=3
void cifrarClave(char clave[], int k){

    for(int i=0; clave[i]!='\0'; i++){
        clave[i]=clave[i]+k;
    }
}

///Aca al devolver la pos cuando es la primera vez que lo encuentra entonces retorna
///la primera pos en la que es encontrado cada nombre y no reasigna
int buscarMozo(Mozo mozos[], int len, char nombreBuscado[]){

    for(int i=0; i<len; i++){
        if(strcmp(mozos[i].nombre, nombreBuscado)==0){
            return i;
        }
    }
        return -1;
}

void mozosArchivo(Mozo mozos[], int &len){

    FILE* fComandas= fopen("comandas_historicas.dat", "rb");
    if(fComandas==NULL){
        cout<<"No se pudo abrir el archivo";
        return;
    }
    ComandaHistoricas comandas;
    while(fread(&comandas, sizeof(ComandaHistoricas), 1, fComandas)==1){

    }
}


void actualizarStock(Comanda ventas[], int vlen, Productos prods[], int pLen, Mozo mozos[], int mlen){

}
