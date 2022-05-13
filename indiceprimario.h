#ifndef INDICEPRIMARIO_H
#define INDICEPRIMARIO_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "arbolbinario.h"
#include "correo.h"


class indicePrimario
{

private:

    //nodoIndicePrimario misNodosIndice;
    struct nodoIndicePrimario{
        char llave[10];
        unsigned long referencia;
    }misNodosIndice;

    ArbolBinario <indicePrimario> myTree;
    int banderaAct =0;



public:
    indicePrimario();

    //getters y setters del struct
    unsigned long getReferencia() const;
    void setReferencia(unsigned long value);
    string getLlave() const;
    void setLlave(const string &value);
    nodoIndicePrimario getNodos()  const;


    //sobrecarga de operadores para imprimir datos
    friend ostream &operator << ( ostream&, const indicePrimario &);

    //sobrecarga de operadores para comparar datos
    bool operator > (indicePrimario &);
    bool operator < (indicePrimario &);
    bool operator == (indicePrimario &);

    void funcionAdmin();

    void llenarArbol();//Llenar Arbol desde archivo de correos
    void LlenarDesdeIndice();//Llenar arbol desde archivo de indices

    void ActualizarArchivo();

    void mostrarCorreo(string&);//Mostrar el correo buscado
    Nodo<indicePrimario> * buscaEnArbol(Nodo<indicePrimario> *, string &);//Buscar el nodo

    void LlenarArchivo(Nodo<indicePrimario> *Apunt, ofstream& archivoTemporal);//Exportar el arbol con recorrido en orden

    bool Actualizado();
    void Desactualizar();

    void BuscarId();

    void Eliminar(string& myId);

};

#endif // INDICEPRIMARIO_H
