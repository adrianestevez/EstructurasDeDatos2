#ifndef INDICESECUNDARIO_H
#define INDICESECUNDARIO_H
#include <iostream>
#include "arbolbinario.h"
#define E 80
#include "lista.h"
#include "indicesdest.h"
#include "indicesrem.h"


using namespace std;

class indicesecundario
{
    ArbolBinario <indiceSDest> myTreeDest;
    ArbolBinario <indiceSRem> myTreeRem;
public:
    indicesecundario();
    void OrComparasion(string destinatario, string remitente);

    void AndComparasion(string destinatario, string remitente);

    Nodo<indiceSRem> * buscaEnArbolRemi(Nodo<indiceSRem> *, string &);//Buscar el nodo
    Nodo<indiceSDest> * buscaEnArbolDest(Nodo<indiceSDest> *, string &);//Buscar el nodo

    bool Yaesta(unsigned int id, ListaSimple<unsigned int> &identsresultantes);

    void OrAdmin();
    void AndAdmin();

};

#endif // INDICESECUNDARIO_H
