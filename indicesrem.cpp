#include "indicesrem.h"
#include "indiceprimario.h"

indiceSRem::indiceSRem()
{

}

ArbolBinario<indiceSRem> indiceSRem::getmyTreeRem()
{
    llenarArbol();
    return myTreeRem;
}

string indiceSRem::getRem() const
{
    return misNodosRemi.rem;
}

void indiceSRem::setRem(const string &value)
{
    strcpy(misNodosRemi.rem, value.c_str());
}

ListaSimple<unsigned int> indiceSRem::getIdents() const
{
    return misNodosRemi.idents;
}

void indiceSRem::setIdents(ListaSimple<unsigned int> value)
{
    misNodosRemi.idents = value;
}

indiceSRem::nodoIndiceSRem indiceSRem::getNodosRem() const
{
    return misNodosRemi;
}

void indiceSRem::addId(unsigned int value)
{
    misNodosRemi.idents.push_back(value);
}

bool indiceSRem::operator > ( indiceSRem &i )
{
    return misNodosRemi.rem > i.getRem();
}

bool indiceSRem::operator < ( indiceSRem &i )
{
    return misNodosRemi.rem < i.getRem();
}

bool indiceSRem::operator == ( indiceSRem &i )
{
    return strcmp(misNodosRemi.rem, i.getRem().c_str());
}

void indiceSRem::llenarArbol()
{

    indiceSRem unIndice;
    Correo c;
    unsigned int ident;
    string remitente;

    Nodo<indiceSRem> *aux = nullptr;

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

           /* if(c.getId()!=0){

                //meter indice
                ident = c.getId();
                remitente = c.getRemitente();

                aux = buscaEnArbol(myTreeRem.getRaiz(), remitente);

                if(aux==nullptr){
                    unIndice.setRem(remitente);
                    unIndice.addId(ident);
                    myTreeRem.insertar( myTreeRem.getRaiz(), unIndice ); //uso sobrecarga de operadores
                }else{
                    aux->getDato().addId(ident);
                }
            }*/
            remitente = c.getRemitente();
            ident = c.getId();
            bool aux = false;
            aux = buscarRem(myTreeRem.getRaiz(), remitente, ident);
            if(aux==false){
                indiceSRem aux;
                aux.setRem(remitente);
                aux.addId(ident);

                myTreeRem.insertar(myTreeRem.getRaiz(), aux);
            }
        }
        archivoDatos.close();
    }
    else {
        cout << "Error al crear el archivo. No se pudo abrir archivo de datos." << endl << endl;
    }
}



Nodo<indiceSRem> *indiceSRem::buscaEnArbol(Nodo<indiceSRem> *Apunt, string &d)
{
    if ( Apunt != nullptr ) {
        if ( Apunt->getDato().getRem() == d ){
            return Apunt;
        }
        else if ( Apunt->getDato().getRem() > d) {
            return buscaEnArbol( Apunt->getIzq(), d );
        }else {
            return buscaEnArbol( Apunt->getDer(), d );
        }
    }
    else {
        return nullptr;
    }
}

void indiceSRem::mostrarCorreo(string &s)
{
    indiceSRem unIndiceSecun;
    indicePrimario unIndicePrim;
    Nodo<indiceSRem> *aux = nullptr;

    string remitente;
    string id;

    aux = buscaEnArbol(myTreeRem.getRaiz(), s);

    if(aux){

        remitente = aux->getDato().getRem();
        ListaSimple<unsigned int> listaux = aux->getDato().getIdents();

        for(size_t i=0; i < listaux.size();i++){
            id = to_string(listaux[i]);
            unIndicePrim.mostrarCorreo(id);
        }
    }else{
        cout<<"No se encontro el elemento"<<endl;
    }

}

void indiceSRem::BuscarRem()
{
    string remitente;

    cin.ignore();
    cout<<"Ingrese el remitente a buscar: ";
    getline(cin, remitente); cout<<endl;

    llenarArbol();
    mostrarCorreo(remitente);
}

bool indiceSRem::buscarRem(Nodo<indiceSRem> *Apunt, string &llavesec, unsigned int id)
{
    if ( Apunt != nullptr ) {
        if ( Apunt->getDato().getRem() == llavesec ){
            //cout<<"Remitente ya existente "<<llavesec<<"     id:" << id;
            Apunt->getDato().addId(id);
            return true;
        }
        else if ( Apunt->getDato().getRem() > llavesec) {
            return buscarRem( Apunt->getIzq(), llavesec, id);
        }else {
            return buscarRem( Apunt->getDer(), llavesec, id );
        }
    }
    else {
        return false;
    }
}

Nodo<indiceSRem> *indiceSRem::getNodoEspecifico(string desti)
{
    llenarArbol();
    Nodo<indiceSRem> *aux = buscaEnArbol(myTreeRem.getRaiz(), desti);
    return aux;
}


