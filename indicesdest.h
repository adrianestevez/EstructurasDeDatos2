#ifndef INDICESDEST_H
#define INDICESDEST_H
#include <iostream>
#include "lista.h"
#include "arbolbinario.h"
#define E 80

using namespace std;


class indiceSDest
{
    struct nodoIndiceSDest{
        char dest[E];
        ListaSimple <unsigned int> idents;
    }misNodosDesti;

    ArbolBinario <indiceSDest> myTreeDest;
public:
    indiceSDest();

    ArbolBinario<indiceSDest> getTreeDest();

    //getters y setters del struct nodoIndiceRem
    string getDest() const;
    void setDest(const string &value);

    ListaSimple<unsigned int>  getIdents() const;
    void setIdents(ListaSimple<unsigned int> value);

    nodoIndiceSDest getNodosDest()  const;

    void addId(unsigned int value);

    //sobrecarga de operadores para imprimir datos
    friend ostream &operator << ( ostream&, const indiceSDest &);

    //sobrecarga de operadores para comparar datos
    bool operator > (indiceSDest &);
    bool operator < (indiceSDest &);
    bool operator == (indiceSDest &);

    void llenarArbol();//Llenar Arbol desde archivo de correos
    Nodo<indiceSDest> * buscaEnArbol(Nodo<indiceSDest> *, string &);//Buscar el nodo

    void mostrarCorreo(string&);//Mostrar el correo buscado
    void BuscarDest();

    bool buscarDest(Nodo<indiceSDest> *, string &, unsigned int);

    Nodo<indiceSDest> *getNodoEspecifico(string desti);


};

#endif // INDICESDEST_H
