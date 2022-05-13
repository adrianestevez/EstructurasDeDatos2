#ifndef BUSQUEDAS_EFICIENTES_H
#define BUSQUEDAS_EFICIENTES_H
#include <iostream>
#include "correo.h"
#include <string>
#include <stdlib.h>
#define MAX 1000

using namespace std;

class Busquedas_eficientes
{
    Correo* emails=new Correo[MAX];
    Correo cor;
public:
    Busquedas_eficientes();
    ~Busquedas_eficientes();
    void LlenarArreglo();
    void imprimirCorreo(Correo a[], int pos);

    //Ordenamientos
    void shellsort();

    //Busquedas
    void BinarySearch(const string &rem);
};

#endif // BUSQUEDAS_EFICIENTES_H
