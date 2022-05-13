#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H


#include <iostream>
#include "correo.h"
//#include "indices.h"

using namespace std;

// Prototipos de la plantilla clase arbolBinario para que nodo pueda hacer referencia en ella
template <class T>
class ArbolBinario;


//Nodo
template <class T>
class Nodo{
private:
    T dato;
    Nodo<T> *der;
    Nodo<T> *izq;

    int FE; //Factor de Equilibrio
public:
    Nodo();
    T getDato();
    void setDato(T &d);

    Nodo<T> * getDer();
    void setDer( Nodo<T> *);
    Nodo<T> * getIzq();
    void setIzq( Nodo<T> *);
    friend class ArbolBinario<T>;
};

template <class T>
Nodo<T>::Nodo(){
    izq = nullptr;
    der = nullptr;
}

template <class T>
T Nodo<T>::getDato(){
    return dato;
}

template<class T>
void Nodo<T>::setDato(T &d)
{
    dato = d;
}

template<class T>
Nodo<T> *Nodo<T>::getDer()
{
    return der;
}

template<class T>
void Nodo<T>::setDer(Nodo<T> *d)
{
    der = d;
}

template<class T>
Nodo<T> *Nodo<T>::getIzq()
{
    return izq;
}

template<class T>
void Nodo<T>::setIzq(Nodo<T> *i)
{
    izq = i;
}

template <class T>
class ArbolBinario
{
private:
    Nodo<T> *raiz;
public:
    ArbolBinario();
    ~ArbolBinario();

    Nodo<T> *getRaiz();
    void setRaiz( Nodo<T> *);

    void menu();

    void insertar(Nodo<T> *Apunt, T &d);
    //void insertarAVL(Nodo<T> *Apunt, T d, int Band);
    void mostrar(Nodo<T> *Apunt, int contador);
    Nodo<T> *buscar(Nodo<T> *Apunt, T &d);
    void recorridoPreOrden(Nodo<T> *Apunt);
    void recorridoInOrden(Nodo<T> *Apunt);
    void recorridoPostOrden(Nodo<T> *Apunt);
    void eliminar(Nodo<T> *Apunt, T &d);
    void eliminarTodo(Nodo<T> *Apunt);


    // AVL

    unsigned int altura(Nodo<T>*&);
    int factorEquilibrio(Nodo<T>*&);

    void balancear(Nodo<T>*&);

    void rsI(Nodo<T>*&); ///Rotacion simple a la izquierda
    void rsD(Nodo<T>*&); ///Rotacion simple a la derecha
    void rdI(Nodo<T>*&); ///Rotacion doble a la izquierda
    void rdD(Nodo<T>*&); ///Rotacion doble a la derecha

};

template <class T>
ArbolBinario<T>::ArbolBinario()
{
    raiz = nullptr;
}

template<class T>
ArbolBinario<T>::~ArbolBinario()
{
    eliminarTodo( raiz );
}

template<class T>
Nodo<T> *ArbolBinario<T>::getRaiz()
{
    return raiz;
}

template<class T>
void ArbolBinario<T>::setRaiz(Nodo<T> * r)
{
    raiz = r;
}

template <class T>
void ArbolBinario<T>::menu()
{
    int dato;
    //system("CLEAR");
    char menuBuscar;
    //int contador = 0;
    cout << "\n# # # # # # # Arbol Binario de Busqueda # # # # # # #" << endl << endl;
    cout << "1. Insertar un nuevo nodo." << endl;
    cout << "2. Mostar arbol completo." << endl;
    cout << "3. Buscar nodo." << endl;
    cout << "4. Recorrido PreOrden." << endl;
    cout << "5. Recorrido InOrden." << endl;
    cout << "6. Recorrido PostOrden." << endl;
    cout << "7. Eliminar nodo." << endl;
    cout << "8. Eliminar todo." << endl;

    cout << "0. Regresar al menu principal." << endl;

    cout << "Ingrese opcion: ";
    cin >> menuBuscar;
    cout << endl;

    switch(menuBuscar){
    case '1':
    {
        cout << "Ingrese entero: " << endl;
        cin >> dato;

        cout << "dato:" << dato << "\nraiz: " << getRaiz() << endl;

        //insertarAVL(getRaiz(), dato, 0);
        insertar(getRaiz(), dato);
        cout<<"xDXDXDXd\n\n";
    }
        break;

    case '2':
    {
        if ( getRaiz() == nullptr ){
            cout << "Imposible mostrar. Arbol vacio." << endl << endl;
        }
        else {
            mostrar(getRaiz(), 0); //es 0 para que imprima desde la raiz
        }
    }
        break;

    case '3':
    {
        if ( getRaiz() == nullptr ){
            cout << "Imposible buscar. Arbol vacio." << endl << endl;
        }
        else {
            cout << "Ingrese dato a buscar: " << endl;
            cin >> dato;
            Nodo<int> *aux;

            aux = buscar( getRaiz(), dato );

            //if ( buscar( getRaiz(), dato ) ) {
            if ( aux ) {
                cout << "Elemento: " << aux->getDato() << " ha sido encontrado en el arbol." << endl << endl;
            }
            else {
                cout << "Elemento no encontrado." << endl << endl;
            }
        }
    }
        break;

    case '4':
    {
        if ( getRaiz() == nullptr ){
            cout << "Imposible hacer recorrido PreOrden. Arbol vacio." << endl << endl;
        }
        else {
            recorridoPreOrden( getRaiz() );
        }
    }
        break;

    case '5':
    {
        if ( getRaiz() == nullptr ){
            cout << "Imposible hacer recorrido InOrden. Arbol vacio." << endl << endl;
        }
        else {
            recorridoInOrden( getRaiz() );
        }
    }
        break;

    case '6':
    {
        if ( getRaiz() == nullptr ){
            cout << "Imposible hacer recorrido PostOrden. Arbol vacio." << endl << endl;
        }
        else {
            recorridoPostOrden( getRaiz() );
        }
    }
        break;

    case '7':
    {
        if ( getRaiz() == nullptr ){
            cout << "Imposible eliminar. Arbol vacio." << endl << endl;
        }
        else{
            cout << "Ingrese dato a eliminar: " << endl;
            cin >> dato;

            if ( !buscar( getRaiz(), dato ) ) {
                cout << "No se encontro el dato a eliminar." << endl << endl;
            }
            else {
                eliminar(getRaiz(), dato);
            }
        }
    }
        break;

    case '8':
    {
        if ( getRaiz() == nullptr ){
            cout << "Imposible eliminar. Arbol vacio." << endl << endl;
        }
        else{
            cout << "Eliminando todos los nodos: " << endl;
                eliminarTodo( getRaiz() );
        }
    }
        break;

    case '0': break; //Regresar al menu principal

    default: cout << "Ha ingresado un valor no valido." << endl << endl;
    }
}

template <class T>
void ArbolBinario<T>::insertar(Nodo<T> *Apunt, T &d)
{
    //Si esta bien pero lo borre para hacerlo avl
    //agregar balanceo
    Nodo<T> *Aux;

    if ( Apunt != nullptr ) { //Se evalua si el  nodo esta definidio
        if ( d < Apunt->dato ) {
            insertar( Apunt->izq, d);
            Apunt->izq = raiz;
        }
        else if ( d > Apunt->dato ) {
            insertar( Apunt->der, d);
            Apunt->der = raiz;
        }

        balancear(Apunt);

        raiz = Apunt;


    }
    else {
        //Aux = crearNodo(d);
        Aux = new Nodo<T>();
        Aux->dato = d;
        raiz = Aux;
    }
}

template <class T>
void ArbolBinario<T>::mostrar(Nodo<T> *Apunt, int cont)
{
    if ( Apunt == nullptr ) {
        //cout << "El arbol esta vacio." << endl << endl;
        return;
    }
    else {
        mostrar( Apunt->der, cont + 1);
        for ( int i = 0; i < cont; i++ ) {
            cout << "   ";
        }
        cout << Apunt->getDato() << endl;
        mostrar( Apunt->izq, cont + 1);
    }
}

template <class T>
Nodo<T> *ArbolBinario<T>::buscar(Nodo<T> *Apunt, T &d)
{
    if ( Apunt != nullptr ) {
        if ( Apunt->getDato() == d ){
            return Apunt;
        }
        else if ( Apunt->getDato() > d) {
            return buscar( Apunt->izq, d );
        }
        else {
            return buscar( Apunt->der, d );
        }
    }
    else {
        return nullptr;
    }
}

template <class T>
void ArbolBinario<T>::recorridoPreOrden(Nodo<T> *Apunt)
{
    if ( Apunt != nullptr ) {
        cout << Apunt->getDato() << " - ";
        recorridoPreOrden( Apunt->izq );
        recorridoPreOrden( Apunt->der );
    }
}

template <class T>
void ArbolBinario<T>::recorridoInOrden(Nodo<T> *Apunt)
{
    if ( Apunt != nullptr ) {
        recorridoInOrden( Apunt->izq );
        cout << Apunt->getDato() << " - ";
        recorridoInOrden( Apunt->der );
    }
}

template <class T>
void ArbolBinario<T>::recorridoPostOrden(Nodo<T> *Apunt)
{
    if ( Apunt != nullptr ) {
        recorridoPostOrden( Apunt->izq );
        recorridoPostOrden( Apunt->der );
        cout << Apunt->getDato() << " - ";
    }
}

template <class T>
void ArbolBinario<T>::eliminar(Nodo<T> *Apunt, T &d)
{

    //Nodo<T> *Aux;

    if ( Apunt != nullptr ) { //Se evalua si el  nodo esta definidio
        if ( d < Apunt->dato ) { //si es menor busca por la izq
            eliminar( Apunt->izq, d);
            Apunt->izq = raiz;
        }
        else if ( d > Apunt->dato ) { //si es mayor busca por la der
                eliminar( Apunt->der, d);
                Apunt->der = raiz;
        }
        else { // si lo encuentra

            Nodo<T> *aux1, *aux2, *aux3;
            aux3 = Apunt;
            //verifica si tiene hijos
            if ( !aux3->der ) { // si no tiene hijo der
                if ( !aux3->izq ) { // y no tiene hijo izq
                    //si no tiene hijos simplemente se elimina
                    //Apunt->getDato().setLlave("0");
                    Apunt = nullptr;
                    delete( Apunt);
                }
                else{ //si solo tiene hijo izq
                    Apunt = aux3->izq;
                }
            }
            else if ( !aux3->izq){ //solo tiene hijo der
                Apunt = aux3->der;
            }
            else { //tiene ambos hijos
                //se reemplaza por el que esta mas a la derehca del sub arbol izq
                aux1 = aux3->izq;
                aux2 = aux3;
                while ( aux1->der ) {
                    aux2 = aux1;
                    aux1 = aux1->der;
                }
                aux3->dato = aux1->dato;
                if (aux3 == aux2 ) {
                    aux3->izq = nullptr;
                }
                else if ( !aux1->izq ) {
                    aux2->der = nullptr;
                }
                else {
                    aux2->der = aux1->izq;
                }
                aux3 = aux1;
            }
            //aux3->getDato().setLlave("0");
            delete( aux3 );


            //if ( factorEquilibrio(Apunt) != 0 ) {
                //balancear( aux2 );
            //}

        }
        raiz = Apunt;
    }
}

template<class T>
void ArbolBinario<T>::eliminarTodo(Nodo<T> *Apunt)
{
    if ( Apunt != nullptr ) {
        eliminarTodo( Apunt->izq );
        eliminarTodo( Apunt->der );
        //cout << Apunt->getDato() << " - ";
        if ( Apunt == raiz ) {
            //cout << "Todos los nodos han sido destruidos" << endl << endl;
            raiz = nullptr;
        }
        delete Apunt;
    }
}

template<class T>
unsigned int ArbolBinario<T>::altura(Nodo<T> *&Apunt)
{
    if(Apunt == nullptr) {
        return 0;
        }

    unsigned int altI = altura(Apunt->izq );
    unsigned int altD = altura(Apunt->der);

    return 1 + (altI > altD ? altI : altD);
}

template<class T>
int ArbolBinario<T>::factorEquilibrio(Nodo<T> *&Apunt)
{
    return altura( Apunt->der) - altura(Apunt->izq );
}

template<class T>
void ArbolBinario<T>::balancear(Nodo<T> *&Apunt)
{
    //cout <<"balancenadno\n\n";
    if(factorEquilibrio(Apunt) < -1){
        if(factorEquilibrio(Apunt->izq) == -1){
      //      cout << "RSD [" << Apunt->getDato() << "] " << endl; ///Borrar
            rsD(Apunt);
        }
        else{
        //    cout << "RDD [" << Apunt->getDato() << "] " << endl; ///Borrar
            rdD(Apunt);
        }
    }

    if(factorEquilibrio(Apunt) > 1){
        if(factorEquilibrio(Apunt->der) == 1){
          //  cout << "RSI [" << Apunt->getDato() << "] " << endl; ///Borrar
            rsI(Apunt);
        }
        else{
           // cout << "RDI [" << Apunt->getDato() << "] " << endl; ///Borrar
            rdI(Apunt);
        }
    }
}

template<class T>
void ArbolBinario<T>::rsI(Nodo<T> *&Apunt)
{
    Nodo<T>* aux1 = Apunt->der;
    Nodo<T>* aux2 = aux1->izq;

    Apunt->der = aux2;
    aux1->izq = Apunt;
    Apunt = aux1;
}

template<class T>
void ArbolBinario<T>::rsD(Nodo<T> *&Apunt)
{
    Nodo<T>* aux1 = Apunt->izq;
    Nodo<T>* aux2 = aux1->der;

    Apunt->izq = aux2;
    aux1->der = Apunt;
    Apunt = aux1;
}

template<class T>
void ArbolBinario<T>::rdI(Nodo<T> *&Apunt)
{
    rsD( Apunt->der );
    rsI( Apunt );
}

template<class T>
void ArbolBinario<T>::rdD(Nodo<T> *&Apunt)
{
    rsI( Apunt->izq );
    rsD( Apunt );
}

#endif // ARBOLBINARIO_H
