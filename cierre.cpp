#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Comanda{
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

int diasDelMes(int mes, int anio){
    int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(mes == 2 && ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))){
        return 29;
    }
    return dias[mes];
}

void diaAnterior(int &dia, int &mes, int &anio){
    dia--;
    if(dia < 1){
        mes--;
        if(mes < 1){
        mes = 12;
        anio--;
        }
    dia = diasDelMes(mes, anio);
    }
}

void aparearDosArchivos(const char* nomA, const char* nomB, const char* nomC){
    FILE* a = fopen(nomA, "rb");
    FILE* b = fopen(nomB, "rb");
    FILE* c = fopen(nomC, "rb");

    if(a == NULL || b == NULL || c == NULL){
        cout<<"Error al abrir los archivos"<<endl;
        if (a) fclose(a);
        if (b) fclose(b);
        if (c) fclose(c);
        return;
    }

    Comanda ra, rb;
    int la = fread(&ra, sizeof(Comanda), 1, a);
    int lb = fread(&rb, sizeof(Comanda), 1, b);

    while (la == 1 && lb == 1){
        if (ra.idMozo <= rb.idMozo){
            fwrite(&ra, sizeof(Comanda), 1, c);
            la = fread(&ra, sizeof(Comanda), 1, a);
        }else{
            fwrite(&rb, sizeof(Comanda), 1, c);
            lb = fread(&rb, sizeof(Comanda), 1, b);
        }
    }

    while(la == 1){
        fwrite(&ra, sizeof(Comanda), 1, c);
        la = fread(&ra, sizeof(Comanda), 1, a);
    }

    while(lb == 1){
        fwrite(&rb, sizeof(Comanda), 1, c);
        lb = fread(&rb, sizeof(Comanda), 1, b);
    }

    fclose(a); fclose(b); fclose(c);
}

void procesarCierreSemanal(char archivosDiarios[7][25], const char* archivoSemanalFinal){
    const char* auxAcumulado = "aux_acumulado.dat";
    const char* auxSiguiente = "aux_siguiente.dat";

    FILE* f1 = fopen(archivosDiarios[0], "rb");
    FILE* fAcu = fopen(auxAcumulado, "wb");

    if(f1 == NULL || fAcu == NULL){
        cout<<"Error al procesar el primer dia de la semana ("<<archivosDiarios[0]<<")."<<endl;
        if(f1) fclose(f1);
        if(fAcu) fclose(fAcu);
        return;
    }

    Comanda r;

    while (fread(&r, sizeof(Comanda), 1, f1) == 1){
        fwrite(&r, sizeof(Comanda), 1, fAcu);
    }

    fclose(f1); fclose(fAcu);

    for(int i = 1; i < 7; i++){
        aparearDosArchivos(auxAcumulado, archivosDiarios[i], auxSiguiente);

        FILE* fOrig = fopen(auxSiguiente, "rb");
        FILE* fDest = fopen(auxAcumulado, "wb");

        if(fOrig == NULL || fDest == NULL){
            cout<<"Error al procesar el dia "<<i + 1<<" ("<< archivosDiarios[i]<<"). "<< endl;
            if(fOrig) fclose(fOrig);
            if(fDest) fclose(fDest);
            return;
        }

        while(fread(&r, sizeof(Comanda), 1, fOrig) == 1){
            fwrite(&r, sizeof(Comanda), 1, fDest);
        }

        fclose(fOrig); fclose(fDest);
    }

    FILE* fFinalOrig = fopen(auxAcumulado, "rb");
    FILE* fFinalDest = fopen(archivoSemanalFinal, "wb");

    if(fFinalOrig == NULL || fFinalDest == NULL){
        cout<<"Error al generar el archivo semanal final."<<endl;
        if(fFinalOrig) fclose(fFinalOrig);
        if(fFinalDest) fclose(fFinalDest);
        return;
    }

    while(fread(&r, sizeof(Comanda), 1, fFinalOrig) == 1){
        fwrite(&r, sizeof(Comanda), 1, fFinalDest);
    }

    fclose(fFinalOrig); fclose(fFinalDest);

    cout<<endl<<"Cierre semanal completado con exito!"<<endl;
    cout<<"Archivo semanal generado: "<<archivoSemanalFinal<<endl;
}

int main(){
    int d, m, a;
    int numSemana;

    cout<<"PROGRAMA DE CIERRE"<<endl;
    cout<<"Ingrese la semana del mes que desea cerrar"<<endl;
    cin>>numSemana;

    cout<<"Ingrese la fecha del dia de cierre (DD MM AAAA)"<<endl;
    cin>>d>>m>>a;

    char nombresDias[7][25];
    char archivoSemanal[25];

    int dAux = d, mAux = m, aAux = a;

    for(int i = 0; i<6; i++){
        diaAnterior(dAux, mAux, aAux);
    }

    int dInicio = dAux, mInicio = mAux, aInicio = aAux;

    for(int i = 0; i<7; i++){
        sprintf(nombresDias[i], "comandas_%02d-%02d-%d.dat", dInicio, mInicio, aInicio);
        dInicio++;
        if(dInicio>diasDelMes(mInicio, aInicio)){
            dInicio = 1;
            mInicio++;
            if(mInicio>12){
                mInicio = 1;
                mInicio++;
            }
        }
    }
    sprintf(archivoSemanal, "comandas_semana_s%d-%02d.dat", numSemana, m);

    procesarCierreSemanal(nombresDias, archivoSemanal);

    return 0;
}
