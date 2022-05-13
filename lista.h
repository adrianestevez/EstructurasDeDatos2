#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>
using namespace std;

template <class T>
class Nod{
public:
    Nod(T dato, Nod *s = nullptr){
        this->dato = dato;
        this->siguiente = s;
    }

private:
    T dato;
    Nod *siguiente;

    template<class>
    friend class ListaSimple;
    size_t listSize = 0;

};

template<class T>
class ListaSimple
{
public:
    ListaSimple();

    bool empty();
    void insert(const T &dato);
    void push_back(const T &dato);
    void clear();
    void pop_back();
    size_t size()const;

    T position(int p);
    T operator [](int p)const;

private:
    Nod<T> *raiz; //mantendra enlace de nodos

};

template<class T>
ListaSimple<T>::ListaSimple()
{
    raiz = nullptr;
}

template<class T>
bool ListaSimple<T>::empty(){
    return raiz == nullptr;
}

template<class T>
size_t ListaSimple<T>::size()const{
    return raiz->listSize;
}

template<class T>
void ListaSimple<T>::insert(const T &dato){
    Nod<T> *nuevo=new Nod<T>(dato);

    if(empty()){
        raiz = nuevo;
    }else{
        nuevo->siguiente = raiz;
        raiz = nuevo;
        // ++listSize;
    }

}

template<class T>
void ListaSimple<T>::push_back(const T &dato){
    Nod<T> *nuevo = new Nod<T>(dato);
    //size_t i;
    if(empty()){
        raiz = nuevo;
        //i=raiz->listSize;
        //++i;
        raiz->listSize++;

    }else{
        Nod<T> *temp = raiz;

        while (temp->siguiente != nullptr){
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;

        //i=raiz->listSize;
        //++i;
        raiz->listSize++;
    }

}

template<class T>
void ListaSimple<T>::clear(){
    if(!empty()){
        Nod<T> *temp = raiz;
        raiz = raiz->siguiente;
        delete temp;
    }else{
        throw out_of_range("Imposible eliminar: lista vacia");
    }
}

template<class T>
void ListaSimple<T>::pop_back(){
    if(!empty()){
        Nod<T> *temp = raiz;

        if(temp->siguiente == nullptr){
            clear();
        }else{
            //2 o mas elementos
            while (temp->siguiente->siguiente != nullptr) {
                temp = temp->siguiente;
        }

            delete temp->siguiente;
            temp->siguiente = nullptr;
        }
        // --listSize;
    }else{
        throw out_of_range("Imposible eliminar: lista vacia");

    }
}


template<class T>
T ListaSimple<T>::position(int p){
    Nod<T> *temp = raiz;
    int cont= 0;
    while(temp and cont!=p){
            temp = temp->siguiente;
            cont++;
    }
    if(temp==nullptr){
            throw out_of_range("Imposible buscar, fuera de Rango");
    }
    return temp->dato;
}



template<class T>
T ListaSimple<T>::operator [](int p) const{
    Nod<T> *temp = raiz;
    int cont= 0;
    while(temp and cont!=p){
            temp = temp->siguiente;
            cont++;
    }
    if(temp==nullptr){
            throw out_of_range("Imposible buscar, fuera de Rango");
    }
    return temp->dato;
}


#endif // LISTA_H_INCLUDED
