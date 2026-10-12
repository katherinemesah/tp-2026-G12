#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;


//----- Fase 1: Structs -----

struct ComandaHistorica{
	char  fecha[11];        // "DD-MM-AAAA" 
	char  nombreMozo[50];   // el nombre completo, repetido en cada venta 
	int   codigoProducto;   
	int cantidad;   
	float comision;
};

struct Producto { 
    int   codigo;   
	char descripcion[50];   
	float precio;   
	int stockActual; 
}; 

struct Mozo {     
	int idMozo; 
	char nombre[50]; 
	char password[20]; 
	float totalComision; 
}; 

struct Comanda {  
	char fecha[11];
	int idMozo; 
	int codigoProducto; 
	int cantidad; 
	float comision; 
}; 


//----- Fase 2: Funciones declaradas -----

//a. Abre inventario.dat en modo "rb". Lee registro por registro y los guarda en el array inv, incrementando lenInv.
void cargarInventario(Producto inv[], int& lenInv); 

//b. Recorre el string de la clave sumando la constante K a cada car cter para cumplir con el requerimiento de seguridad.
void encriptarClave(char clave[], int k);

//c. Hace una B squeda Secuencial en el array de mozos para ver si el nombre ya existe. Retorna la posici n o -1.
int buscarMozo(Mozo mozos[], int len, char nombreBuscado[]);

//d. Hace una B squeda Binaria en el array del inventario (aprovechando que ya viene ordenado por c digo)para encontrar el producto al instante.
int buscarProducto(Producto inv[], int len, int codigoBuscado);

//e. Abre comandas_historicas.dat. Por cada venta, busca/crea al mozo, busca el producto, descuenta el stock, calcula la comisi n y guarda la venta normalizada en el array ventas.
void procesarHistorico(Producto inv[], int lenInv, Mozo mozos[], int &lenMozos, Comanda ventas[], int &lenVentas);

//f. Ordena el array de ventas en RAM por fecha y luego por ID de mozo, prepar ndolo para el corte de control.
void ordenarVentas(Comanda ventas[], int lenVentas);

//g. Aplica el patr n Corte de Control agrupando por fecha. Crea los archivos comandas_dd-mm-aaaa.dat y los graba.
void generarArchivosDiarios(Comanda ventas[], int lenVentas);

//h. Abre inventario.dat y mozos.dat en modo "wb" (que crea o vac a el archivo) y guarda los arrays actualizados.
void guardarDatosFinales(Producto inv[], int lenInv, Mozo mozos[], int lenMozos);


//----- Fase 3: Funciones desarrolladas -----

int buscarMozo(Mozo mozos[], int len, char nombreBuscado[]){
	int i=0;
	while (i<len && strcmp(mozos[i].nombre, nombreBuscado) != 0){ //strcmp (string compare) compara nombres para usarlos como clave, si devuelve 0 es porque son iguales
		i++;
	}
	if (i==len){
		return -1; //no encontrado
	} else {
		return i; //encontrado en posicion i
	}
}

void cargarInventario(Producto inv[], int& lenInv){
	FILE* inventario = fopen("inventario.dat", "rb");
	if (inventario == NULL) {
 		cout << "No se pudo abrir el archivo." << endl;
 		return;
	}

	while (fread(&inv[lenInv], sizeof(Producto), 1, inventario) == 1)
	{
		lenInv++;
	}
	fclose(inventario);
}

void encriptarClave(char clave[], int k){
	int i=0;
	while (clave[i] != '\0') // mientras no llegue al final del array. mientras la clave todavia exista
	{
		clave[i] = clave[i] + k;
		i++;
	}
}

int buscarProducto(Producto inv[], int len, int codigoBuscado){
	int izquierda = 0;
	int derecha = len - 1;

	 while (izquierda <= derecha) {
		int medio = (izquierda + derecha) / 2;
		if (inv[medio].codigo == codigoBuscado) {
 			return medio; // encontrado
 		} else if (inv[medio].codigo < codigoBuscado) {
 			izquierda = medio + 1; // buscar en la mitad derecha
 		} else {
 			derecha = medio - 1; // buscar en la mitad izquierda
 		}
 	}
 return -1; // no encontrado
}

const int K = 7; // constante k para encriptar clave

void procesarHistorico(Producto inv[], int lenInv, Mozo mozos[], int &lenMozos, Comanda ventas[], int &lenVentas) {
    FILE* fHist = fopen("comandas_historicas.dat", "rb");
    if (fHist == NULL) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    ComandaHistorica vieja;
    while (fread(&vieja, sizeof(ComandaHistorica), 1, fHist) == 1) {

        int posMozo = buscarMozo(mozos, lenMozos, vieja.nombreMozo);

        if (posMozo == -1) { // esto lo que hace con el if -1 es que si no lo encuentra crea el primer id y asi para todos los demas que entren
            // Mozo nuevo — acá van, en orden:
            posMozo = lenMozos;
                       
            mozos[lenMozos].idMozo=lenMozos+1; 
            strcpy(mozos[lenMozos].nombre, vieja.nombreMozo); // copiar nombre
            mozos[lenMozos].totalComision=0; // totalComision = 0
            sprintf(mozos[posMozo].password, "%d", mozos[posMozo].idMozo); // generar password. sprintf escribe el resultado dentro de un char[], es como un cout pero en vez de por pantalla en un char
            encriptarClave(mozos[posMozo].password, K); // generar password encriptada
            
            lenMozos++;
        }
        // Corre siempre, mozo nuevo o existente:
        mozos[posMozo].totalComision += vieja.comision; // sumar comisión, 
        
		//-----						buscar producto y descontar stock, armar ventas[]						-----
		int posProd = buscarProducto(inv, lenInv, vieja.codigoProducto); // es vieja.codigoProducto porque al abrir el archivo "comandas_historicas.dat" abrimos el struct Comandas
		
		if (posProd != -1){
			
			if (inv[posProd].stockActual >= vieja.cantidad){
				// hay stock suficiente: se descuenta normal
				inv[posProd].stockActual = inv[posProd].stockActual - vieja.cantidad; // descuenta la mercaderia por venta
			} else {
            // no alcanza el stock: se avisa y se deja en 0 (no se permite que quede negativo)
            cout << "Aviso: stock insuficiente para el producto " << vieja.codigoProducto
            << " (" << vieja.fecha << ", mozo " << vieja.nombreMozo << "). "
            << "Stock disponible: " << inv[posProd].stockActual
            << ", se pidieron: " << vieja.cantidad << endl;
            inv[posProd].stockActual = 0;
            }


			strcpy(ventas[lenVentas].fecha, vieja.fecha);
			ventas[lenVentas].idMozo = mozos[posMozo].idMozo; 
			ventas[lenVentas].codigoProducto = vieja.codigoProducto;
			ventas[lenVentas].cantidad = vieja.cantidad;
			ventas[lenVentas].comision  = vieja.comision;
	
			lenVentas++;
		}
		else {
			cout << "No se encontro el Producto" << endl;
		}
    }

    fclose(fHist);
}


//salvar problema de la fecha (que compare cronologicamente)
// consultar que pasa si son diferentes los meses/anios


//ordenar el array de ventas por fecha e id
void ordenarVentas(Comanda ventas[], int lenVentas){
	//selección, comparando fecha como string
    for (int i = 0; i < lenVentas - 1; i++){
        int posMenor = i;
        for (int j = i + 1; j < lenVentas; j++){
            if (strcmp(ventas[j].fecha, ventas[posMenor].fecha) < 0 ||
               (strcmp(ventas[j].fecha, ventas[posMenor].fecha) == 0 && ventas[j].idMozo < ventas[posMenor].idMozo)) { //desempate por idMozo si las fechas son iguales
                posMenor = j;
            }
        }
        if (posMenor != i) {
            Comanda aux = ventas[i];
            ventas[i] = ventas[posMenor];
            ventas[posMenor] = aux;
        }
    }
}

//generar archivos diarios con corte de control creando el archivo comandas_dd-mm-aaaa.dat
void generarArchivosDiarios(Comanda ventas[], int lenVentas){
	//depende de que ventas[] ya venga ordenado
    int i = 0;
    while (i < lenVentas) {
        char fechaActual[11];
        strcpy(fechaActual, ventas[i].fecha);

        char nombreArchivo[30];
        sprintf(nombreArchivo, "comandas_%s.dat", fechaActual);

        FILE* fDia = fopen(nombreArchivo, "wb");
        if (fDia == NULL) {
            cout << "No se pudo crear " << nombreArchivo << endl;
            return;
        }

        while (i < lenVentas && strcmp(ventas[i].fecha, fechaActual) == 0) {
            fwrite(&ventas[i], sizeof(Comanda), 1, fDia);
            i++;
        }
        fclose(fDia);
    }
}

//guardar datos finales abriendo inventario.dat y mozos.dat en modo "wb" (que crea o vac a el archivo) y guarda los arrays actualizados
void guardarDatosFinales(Producto inv[], int lenInv, Mozo mozos[], int lenMozos){
    FILE* fInv = fopen("inventario.dat", "wb");
    if (fInv == NULL) {
        cout << "No se pudo guardar inventario.dat" << endl;
        return;
    }
    fwrite(inv, sizeof(Producto), lenInv, fInv);
    fclose(fInv);

    FILE* fMoz = fopen("mozos.dat", "wb");
    if (fMoz == NULL) {
        cout << "No se pudo guardar mozos.dat" << endl;
        return;
    }
    fwrite(mozos, sizeof(Mozo), lenMozos, fMoz);
    fclose(fMoz);
}


int main(){
    const int MAX_PROD = 100;
    const int MAX_MOZOS = 100;
    const int MAX_VENTAS = 1000;

    Producto inv[MAX_PROD];
    int lenInv = 0;

    Mozo mozos[MAX_MOZOS];
    int lenMozos = 0;

    Comanda ventas[MAX_VENTAS];
    int lenVentas = 0;

    cargarInventario(inv, lenInv);
    procesarHistorico(inv, lenInv, mozos, lenMozos, ventas, lenVentas);
    ordenarVentas(ventas, lenVentas);
    generarArchivosDiarios(ventas, lenVentas);
    guardarDatosFinales(inv, lenInv, mozos, lenMozos);

    cout << "Normalizacion completada. Mozos: " << lenMozos
         << " | Ventas: " << lenVentas << endl;

    return 0;
}