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

//1.Por pedido, la clave de mozo se cifra k=3 SI
void cifrarClave(char clave[], int k);
//2.Al buscar los mozos se busca que no se repita SI
int buscarMozo(Mozo mozos[], int& len, char nombreBuscado[]);
//3. Pasar inventario SI
void inventarioProductos(Producto prod[], int& Ilen);
//4. busca productos para restarle SI
int BuscarActualizarInv(Producto prod[], int Ilen, int codBuscado);
//5.Asigna Id, comision total y ventas
void leerComandas(Producto prod[], int Ilen, Mozo mozos[], int& mlen, Comanda ventas[], int vlen);
//6.Ordena las ventas por id
void ordenarVentas(Comanda ventas[], int vlen);
//7.Asigna nombre a las plantillas de ventas
void asignaNombreDiario(Comanda ventas[], int vlen);
//8.Actualizar stock
void guardaStockActual(Productos prod[], int pLen);
//9. mozos crea archivo
void generarArchivoMozo(Mozo mozos[], int mlen);

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

void inventarioProductos(Producto prod[], int& plen){
    FILE* fprod=fopen("inventario.dat", "rb");
    if(fprod==NULL){
        cout<<"No se pudo abrir el archivo";
        return;
    }
    while(fread(&prod[plen), sizeof(Producto), 1, fprod)==1){
        plen++;
    }
    fclose(fprod);
    cout<<"Inventario cargado con el total de los productos"<<endl;
}

int BuscarActualizarInv(Producto prod[], int plen, int codBuscado){
    int izquierda=0;
    int derecha=plen-1;

    while(izquierda<=derecha){
        int medio=(izquierda+derecha)/2;

        if(prod[medio].codigo==codBuscado){
            return medio;
        }

        if(prod[medio].codigo<codBuscado){
            izquierda=medio+1;
        }
        else{
            derecha=medio-1;
        }
    }
    return -1;
}

void guardaStockActual(Productos prods[], int pLen){
    FILE* fstock=fopen("inventario.dat", "wb");
    if(ftock==NULL){
        cout<<"No se pudo abrir el archivo";
        return;
    }
    for(int i=0; i<plen; i++){
        fwrite(&prods[i], sizeof(Producto), 1, fstock);
    }
    fclose(fstock);
    cout<<"El inventario se actualizo con exito"<<endl;
}

void generarArchivoMozo(Mozo mozos[], int mlen){
    FILE* fmozo=fopen("mozos.dat", "wb");
    if(fmozo==NULL){
        cout<<"No se pudo crear/abrir mozos.dat";
        return;
    }
    for(int i=0; i<mlen; i++){
        fwrite(&mozos[i], sizeof(Mozo), 1, fmozo;
    }
    fclose(fmozo);
    cout<<"El archivo de mozo se cargo correctamente"<<endl;
}
