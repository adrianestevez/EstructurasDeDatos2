#ifndef INDICESREM_H
#define INDICESREM_H
#include <iostream>
#include "lista.h"
#include "arbolbinario.h"
#define E 80

using namespace std;

class indiceSRem
{
    struct nodoIndiceSRem{
        char rem[E];
        ListaSimple <unsigned int> idents;
    }misNodosRemi;

    ArbolBinario <indiceSRem> myTreeRem;


public:
    indiceSRem();

    ArbolBinario <indiceSRem> getmyTreeRem();

    //getters y setters del struct nodoIndiceRem
    string getRem() const;
    void setRem(const string &value);

    ListaSimple<unsigned int>  getIdents() const;
    void setIdents(ListaSimple<unsigned int> value);

    nodoIndiceSRem getNodosRem()  const;

    void addId(unsigned int value);

    //sobrecarga de operadores para imprimir datos
    friend ostream &operator << ( ostream&, const indiceSRem &);

    //sobrecarga de operadores para comparar datos
    bool operator > (indiceSRem &);
    bool operator < (indiceSRem &);
    bool operator == (indiceSRem &);


    void llenarArbol();//Llenar Arbol desde archivo de correos
    Nodo<indiceSRem> * buscaEnArbol(Nodo<indiceSRem> *, string &);//Buscar el nodo

    void mostrarCorreo(string&);//Mostrar el correo buscado
    void BuscarRem();

    bool buscarRem(Nodo<indiceSRem> *, string &, unsigned int);

    Nodo<indiceSRem> *getNodoEspecifico(string desti);


};

#endif // INDICESREM_H
