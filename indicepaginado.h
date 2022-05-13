#ifndef INDICEPAGINADO_H
#define INDICEPAGINADO_H

//#include <iostream>
//#include <fstream>
//#include <string.h>
#include <sys/time.h>
#include "indiceprimario.h"

using namespace std;

class indicePaginado
{

private:

    struct nodoindicePaginado{
        char llave[10];
        unsigned long referencia;
        char fecha_hora[64];
    }misNodosIndicePaginado;

    indicePrimario ip;

    ArbolBinario<indicePaginado> myTreePaginado;
    string idMenor, fechaHoraMenor;
    unsigned long referenciaMenor;


public:
    indicePaginado();

    //getters y setters del struct
    unsigned long getReferencia() const;
    void setReferencia(unsigned long value);
    string getLlave() const;
    void setLlave(const string &value);
    nodoindicePaginado getMisNodosIndice()  const;
    string getFecha_hora() const;
    void setFecha_hora(const string &value);

    //sobrecarga de operadores para imprimir datos
    friend ostream &operator << ( ostream&, const indicePaginado &);

    //sobrecarga de operadores para comparar datos
    bool operator > (indicePaginado &);
    bool operator < (indicePaginado &);
    bool operator == (indicePaginado &);

    //funciones
    void funcionAdmin();//
    void llenarArbolDesdeArchivoCorreo();//
    void llenarArbolDesdeArchivoIndice();//
    void buscarPorID();//
    void mostrarCorreo(string& myId);//
    Nodo<indicePaginado> * buscaEnArbol(Nodo<indicePaginado> *, string &);//
    void recorridoInOrden(Nodo<indicePaginado> *Apunt, string&);


};


#endif // INDICEPAGINADO_H
