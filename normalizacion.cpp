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
  char fecha[11];
  int idMozo;
  int codigoProducto;
  int cantidad;
  float comision;
};

//1.Por pedido, la clave de mozo se cifra k=3 SI
void cifrarClave(char clave[], int k);
//2.Al buscar los mozos se busca que no se repita SI
int buscarMozo(Mozo mozos[], int& mlen, char nombreBuscado[]);
//3. Pasar inventario SI
void inventarioProductos(Producto prod[], int& plen);
//4. busca productos para restarle SI
int BuscarActualizarInv(Producto prod[], int plen, int codBuscado);
//5.Asigna Id, comision total y ventas
void leerComandasHistoricas(Producto prod[], int plen, Comanda ventas[], int vlen, Mozo mozos[], int& mlen, int k);
//6.Ordena las ventas por id
void ordenarVentas(Comanda ventas[], int vlen);
//7.Asigna nombre a las plantillas de ventas
void asignaNombreDia(Comanda ventas[], int vlen);
//8.Actualizar stock
void guardaStockActual(Producto prod[], int plen);
//9. mozos crea archivo
void generarArchivoMozo(Mozo mozos[], int mlen);

int main(){
    const int cantMozos[50];
    int mlen=0;
    const int cantProductos[100];
    int plen=0;
    const int cantVentas[100];
    int vlen=0;
    const int k=3;

    Mozo mozos[cantMozos];
    Producto productos[cantProductos];
    Comanda ventas[cantVentas];

    inventarioProductos(productos, plen);
    leerComandasHistoricas(productos, plen, ventas, vlen, mozos, mlen, k);
    ordenarVentas(ventas,  vlen);
    asignaNombreDia(ventas, vlen);
    guardaStockActual(productos,  plen);
    generarArchivoMozo(mozos,  mlen);


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

void leerComandasHistoricas(Producto prod[], int plen, Comanda ventas[], int& vlen, Mozo mozos[], int& mlen, int k){
    FILE* fcomandas=fopen("comandas_historicas.dat","rb");
    if(fcomandas==NULL){
        cout<<"No se pudo abrir el archivo";
        return;
    }

    ComandaHistoricas comandas;
    vlen=0;
    plen=0;

    char contraxdefecto[20]="1234";
    cifrarClave(contraxdefecto, k);

    while(fread(&comandas, sizeof(ComandaHistoricas), 1, fcomandas)==1){
        int idAsignado=buscarMozo(mozos, mlen, comandas.nombreMozo, comandas.comision, contraxdefecto);

        int posProd=BuscarActualizarInv(prod,  plen, comandas.codigoProducto);
        if(posProd!=-1){
            prod[posProd].stockActual-=comandas.cantidad;
        }
        if(prod[posProd].stockActual<0){
            cout<<"El stock esta en negativo";//<<comandas.codigoProducto<<"("<<prod[posProd].stockActual<<"unidades)"<<endl;
        }
        else{
            cout<<"El producto con codigo"<<comandas.codigoProducto<<" no existe"<<endl;
        }

        if(vlen<cantProductos){
            strcpy(ventas[vlen].fecha, comandas.fecha);
            ventas[vlen].idMozo=idAsignado;
            ventas[vlen].codigoProducto=comandas.codigoProducto;
            ventas[vlen].cantidad=comandas.cantidad;
            ventas[vlen].comision=comandas.comision;
            vlen++;
        }
        else{
            cout<<"Se alcanzo la memoria fisica de ventas"<<endl;
        }

    }
    fclose(fcomandas);
    cout<<"\nComandas Historicas leida"<<endl;
    cout<<"\nCantidad mozos:"<<mlen<<endl;
    cout<<"\nCantidad ventas: "<<vlen<<endl;

}

void ordenarVentas(Comanda ventas[], int vlen){
    for(int i=0; i<vlen, i++){

    Comanda clave=venta[i];
    int j=i-1;

        while(j>=0 && (strcmp(ventas[j].fecha,clave.fecha)>0 || (strcmp(ventas[j].fecha, clave.fecha)==0 && ventas[i].idMozo>clave.idMozo))){
            ventas[j+1]=ventas[j];
            j--;
        }
            ventas[j+1]=clave;
        }
        cout<<"Se ordeno las ventas por fecha y Id"<<endl;
}

void asignarNombreDia(Comanda ventas[], int vlen){
    int i=0;
    while(i<vlen){
        char fechaActual[11];
        strcpy(fechaActual, ventas[i].fecha);

        char nombreArchivo[40];
        sprintf(nombreArchivo, "comandas_%s.dat", fechaActual);

        FILE* fdia=fopen(nombreArchivo, "wb");
        if(fdia==NULL){
            cout<<"No se pudo crear el archivo";
            return;
        }

        while(i<vlen && strcmp(ventas[i].fecha, fechaActual)==0){
            Comanda comanda;
            comanda.idMozo=ventas[i].idMozo;
            comanda.codigoProducto=ventas[i].codigoProducto;
            comanda.cantidad=ventas[i].cantidad;
            comanda.comision=ventas[i].comision;

            fwrite(&comanda, sizeof(Comanda), 1, fdia);
            i++;
        }
        fclose(fdia);
        cout<<"Planilla generada: "<<nombreArchivo<<endl;

    }
}

void guardaStockActual(Productos prod[], int pLen){
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
