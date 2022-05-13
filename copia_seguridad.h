#ifndef COPIA_SEGURIDAD_H
#define COPIA_SEGURIDAD_H
#include <correg.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include "correo.h"

class Copia_Seguridad
{
public:
    Copia_Seguridad();
    void exportar(Correo&);
    string convertir(string aux);
    string unirRegistro(Correo&);
    string convertirRegistro(Correo c);

    void importar();
    Correo cRetorno;
   // Correo guardarCampo(string conca,int cont, Correo &cor);
    void agregarAlArchivo(Correo &cor);
    void imprimirRegis(Correo &c);

    void modificarCsv(unsigned int id);
    void menuModificarCSV(Correo&);
    void eliminarCsv(unsigned int id);
    //void menuEliminarCSV(CorreoElectronico&);

    //CorreoElectronico estadoFinal(string aux2, int aux, CorreoElectronico c);
    void agregar(Correo c, size_t id);
};

#endif // COPIA_SEGURIDAD_H
