#ifndef DISPERSION_H
#define DISPERSION_H
#include <iostream>
#define PRIMO 211
#define E 80
#include "lista.h"
#include "indicesdest.h"
#include <string.h>

using namespace std;

class dispersion
{
    struct NodoDispersion{
       char remitente[E];
       int id;
    }misNodosDispersion;

    ListaSimple<dispersion> tabla[PRIMO];
public:
    dispersion();

    string getRemitente() const;
    void setRemitente(const string &value);
    int getId() const;
    void setId(const int &value);
    NodoDispersion getMisNodosDispersion();



    int funcionDispersionPJW(char *clave);//la llave o clave sera el remitente
    void anadirRegistro(int pos, dispersion);
    void LlenarTabla();
    void BuscarEnTabla(string remitente);
    void FuncionAdminBuscar();

    void SerializarTabla();
    void ImportarDesdeArchTabla();





};

#endif // DISPERSION_H
