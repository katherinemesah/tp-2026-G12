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
// Funcion para el stock
void RestarProductoAlStock(const char* nombre,long pos, int cantidad) {
    FILE* f = fopen(nombre, "rb+");
    if (f == NULL) return;
    Producto p;
    if(fseek(f, pos * sizeof(Producto), SEEK_SET) == 0 &&
        fread(&p, sizeof(Producto), 1, f) ==1){

        p.stockActual -= cantidad;
        if(fseek(f, pos * sizeof(Producto), SEEK_SET)==0){
            if(fwrite(&p, sizeof(Producto), 1, f)!=1){
            cout << "Error al actualizar el stock." << endl;
         }
       }
    } 
    fclose(f);
}
// Funcion para la comision de Mozo
void sumarComisionMozo(const char*nombre, long pos, float comision) {
    FILE* f = fopen(nombre, "rb+");
    if (f == NULL) return;
    Mozo m;
    if(fseek(f, pos * sizeof(Mozo), SEEK_SET)!=0||
    fread(&m, sizeof(Mozo), 1, f)!=1){
        fclose(f);
        return;
    }
    m.totalComision += comision;
    if(fseek(f, pos * sizeof(Mozo), SEEK_SET)!=0 ||
    fwrite(&m, sizeof(Mozo), 1, f) !=1){
        fclose(f);
        return;
    }
    fclose(f);
}

//Funcion para ordenar comandas por Mozo
void ordenarComandasPorMozo(const char* nombre) {
    FILE* f = fopen(nombre, "rb");
    if (f == NULL) return;

    Comanda v[MAX_COMANDAS];
    int n = 0;
    while (n < MAX_COMANDAS && fread(&v[n], sizeof(Comanda), 1, f) == 1) n++;

    Comanda extra;
    if (n == MAX_COMANDAS && fread(&extra, sizeof(Comanda), 1, f) == 1) {
        cout << "Hay mas de " << MAX_COMANDAS << " ventas, no se puede ordenar." << endl;
        fclose(f);
        return;
    }
    fclose(f);

    for (int j = 1; j < n; j++) {
        Comanda aux = v[j];
        int k = j - 1;
        while (k >= 0 && v[k].idMozo > aux.idMozo) {
            v[k + 1] = v[k];
            k--;
        }
        v[k + 1] = aux;
    }

    f = fopen(nombreArchivo, "wb");
    if (f == NULL) return;
    for (int j = 0; j < n; j++) fwrite(&v[j], sizeof(Comanda), 1, f);
    fclose(f);
}

//MAIN
int main() {
    
    char fecha[50];
    cout << "Ingrese la fecha del dia de esta manera (DD-MM-AAAA): ";
    cin >> fecha;

    char ArchivoDelDia[100];
    sprintf(ArchivoDelDia, "comandas_%s.dat", fecha);

    FILE* f = fopen(ArchivoDelDia, "ab");
    if (f == NULL) {
        cout << "Error al abrir el archivo del dia." << endl;
        return 1;
    }

    int opcion = -1;
    while (opcion != 0) {
    cout << endl << "VENTAS " << fecha << ":" << endl;
    cout << "1. Cargar venta" << endl;
    cout << "0. Terminar y ordenar" << endl;
    cout << "Opcion: ";
    cin >> opcion;

        if (opcion != 1) {
            if (opcion != 0) cout << "Opcion invalida." << endl;
            continue;
    }
        int idMozo;
        cout << "Numero de mozo: ";
        cin >> idMozo;

        Mozo m;
        long posMozo = BuscarMozo("mozos.dat", idMozo, m);
        if (posMozo == -1) {
            cout << "No se encuentra Mozo, por favor vuelva a poner el numero correctamente." << endl;
            continue;
        }

        char clave[50];
        cout << "Clave: ";
        cin >> clave;

        char claveEncriptada[50];
        encriptar(clave, claveEncriptada);

        if (strcmp(claveEncriptada, m.password) != 0) {
            cout << "Clave incorrecta, por favor vuelva a poner la clave correctamente." << endl;
            continue;
        }

        int codigoProducto;
        cout << "Codigo de producto: ";
        cin >> codigoProducto;

        Producto p;
        long posProducto = BuscarProducto("inventario.dat", codigoProducto, p);
        if (posProducto == -1) {
            cout << "El producto no existe." << endl;
            continue;
        }

        int cantidad;
        cout << "Cantidad: ";
        cin >> cantidad;

         if (cantidad <= 0) {                                  
            cout << "La cantidad debe ser mayor a 0." << endl;
            continue;
        }

        if (p.stockActual < cantidad) {
            cout << "No hay stock del producto." << endl;
            continue;
        }

        float comision = p.precio * cantidad * TASA_COMISION;

        Comanda c;
        c.idMozo = idMozo;
        c.codigoProducto = codigoProducto;
        c.cantidad = cantidad;
        c.comision = comision;
        if(fwrite(&c, sizeof(Comanda), 1, f) !=1){
            cout<<"Error al guardar la venta"<<endl;
            continue;
        }

        RestarProductoAlStock("inventario.dat", posProducto, cantidad);
        sumarComisionMozo("mozos.dat", posMozo, comision);

        cout << "Venta agregada. La comision es: " << comision << endl;
    }

    fclose(f);
    ordenarComandasPorMozo(ArchivoDelDia);

    cout << " Se ordeno archivo por Mozo." << endl;
    return 0;
}
