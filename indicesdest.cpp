#include "indicesdest.h"
#include "indiceprimario.h"

indiceSDest::indiceSDest()
{

}

ArbolBinario<indiceSDest> indiceSDest::getTreeDest()
{
    llenarArbol();
    return myTreeDest;
}

string indiceSDest::getDest() const
{
    return misNodosDesti.dest;
}

void indiceSDest::setDest(const string &value)
{
    strcpy(misNodosDesti.dest, value.c_str());
}

ListaSimple<unsigned int> indiceSDest::getIdents() const
{
    return misNodosDesti.idents;
}

void indiceSDest::setIdents(ListaSimple<unsigned int> value)
{
    misNodosDesti.idents = value;
}

indiceSDest::nodoIndiceSDest indiceSDest::getNodosDest() const
{
    return misNodosDesti;
}

void indiceSDest::addId(unsigned int value)
{
    misNodosDesti.idents.push_back(value);
}

bool indiceSDest::operator >(indiceSDest &i)
{
    return misNodosDesti.dest > i.getDest();
}

bool indiceSDest::operator <(indiceSDest &i)
{
    return misNodosDesti.dest < i.getDest();
}

bool indiceSDest::operator ==(indiceSDest &i)
{
    return strcmp(misNodosDesti.dest, i.getDest().c_str());
}

void indiceSDest::llenarArbol()
{
    indiceSDest unIndice;
    Correo c;
    unsigned int ident;
    string destinatario;

    Nodo<indiceSDest> *aux = nullptr;

    ifstream archivoDatos;
    archivoDatos.open("bandeja.bin", ios::in | ios::binary);

    if( archivoDatos.is_open() ) {

        archivoDatos.clear();
        archivoDatos.seekg( 0 );

        while ( !archivoDatos.eof() ) {

            archivoDatos.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) ); //extrae un correo
            if ( archivoDatos.eof() ) {
                break;
            }

            destinatario = c.getDestinatario();
            ident = c.getId();
            bool aux = false;
            aux = buscarDest(myTreeDest.getRaiz(), destinatario, ident);
            if(aux==false){
                indiceSDest aux;
                aux.setDest(destinatario);
                aux.addId(ident);

                myTreeDest.insertar(myTreeDest.getRaiz(), aux);
            }
        }
        archivoDatos.close();
    }
    else {
        cout << "Error al crear el archivo. No se pudo abrir archivo de datos." << endl << endl;
    }
}

Nodo<indiceSDest> *indiceSDest::buscaEnArbol(Nodo<indiceSDest> *Apunt, string &d)
{
    if ( Apunt != nullptr ) {
        if ( Apunt->getDato().getDest() == d ){
            return Apunt;
        }
        else if ( Apunt->getDato().getDest() > d) {
            return buscaEnArbol( Apunt->getIzq(), d );
        }else {
            return buscaEnArbol( Apunt->getDer(), d );
        }
    }
    else {
        return nullptr;
    }
}

void indiceSDest::mostrarCorreo(string &s)
{
    indiceSDest unIndiceSecun;
    indicePrimario unIndicePrim;
    Nodo<indiceSDest> *aux = nullptr;

    string destinatario;
    string id;

    aux = buscaEnArbol(myTreeDest.getRaiz(), s);

    if(aux){

        destinatario = aux->getDato().getDest();
        ListaSimple<unsigned int> listaux = aux->getDato().getIdents();

        for(size_t i=0; i < listaux.size();i++){
            id = to_string(listaux[i]);
            unIndicePrim.mostrarCorreo(id);
        }
    }else{
        cout<<"No se encontro el elemento"<<endl;
    }
}

void indiceSDest::BuscarDest()
{
    string destinatario;

    cin.ignore();
    cout<<"Ingrese el destinatario a buscar: ";
    getline(cin, destinatario); cout<<endl;

    llenarArbol();
    mostrarCorreo(destinatario);
}

bool indiceSDest::buscarDest(Nodo<indiceSDest> *Apunt, string &llavesec, unsigned int id)
{
    if ( Apunt != nullptr ) {
        if ( Apunt->getDato().getDest() == llavesec ){
            Apunt->getDato().addId(id);
            return true;
        }
        else if ( Apunt->getDato().getDest() > llavesec) {
            return buscarDest( Apunt->getIzq(), llavesec, id);
        }else {
            return buscarDest( Apunt->getDer(), llavesec, id );
        }
    }
    else {
        return false;
    }
}

Nodo<indiceSDest> *indiceSDest::getNodoEspecifico(string desti)
{
    llenarArbol();
    Nodo<indiceSDest> *aux = buscaEnArbol(myTreeDest.getRaiz(), desti);
    return aux;
}











