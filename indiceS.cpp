#include "indiceS.h"
#include "lista.h"
#include "indiceprimario.h"

indicesecundario::indicesecundario()
{

}

void indicesecundario::OrComparasion(string destinatario, string remitente)
{
    indiceSDest dest;
    indiceSRem rem;

    ListaSimple<unsigned int> identsrem;
    ListaSimple<unsigned int> identsdest;
    ListaSimple<unsigned int> identsresultantes;

    Nodo<indiceSRem> *auxrem = nullptr;
    Nodo<indiceSDest> *auxdest = nullptr;

    indicePrimario ip;

    int idsUsados[100];
    int id;
    bool bandera= false;


    auxrem = rem.getNodoEspecifico(remitente);
    auxdest = dest.getNodoEspecifico(destinatario);

    if(auxrem!=nullptr or auxdest!=nullptr){
        if(auxdest!=nullptr){
            identsdest = auxdest->getDato().getIdents();
            for(size_t j=0; j < identsdest.size() ;j++){
                id = identsdest[j];

                string identi = to_string(id);
                ip.mostrarCorreo(identi);
                idsUsados[j]=id;
            }
        }
        if(auxrem!=nullptr){
            identsrem = auxrem->getDato().getIdents();
                for(size_t i=0; i < identsrem.size() ;i++){
                    id = identsrem[i];
                    bandera=false;
                    for(int j=0; j<=100;j++){
                        if(id==idsUsados[j]){
                            bandera=true;
                        }
                    }
                    if(bandera==false){
                        string identi = to_string(id);
                        ip.mostrarCorreo(identi);
                    }
                }
        }
    }


}

void indicesecundario::AndComparasion(string destinatario, string remitente)
{
    indiceSDest dest;
    indiceSRem rem;

    ListaSimple<unsigned int> identsrem;
    ListaSimple<unsigned int> identsdest;
    ListaSimple<unsigned int> identsresultantes;

    Nodo<indiceSRem> *auxrem = nullptr;
    Nodo<indiceSDest> *auxdest = nullptr;


    auxrem = rem.getNodoEspecifico(remitente);
    auxdest = dest.getNodoEspecifico(destinatario);

    if(auxrem){
        if(auxdest){
            identsrem = auxrem->getDato().getIdents();
            identsdest = auxdest->getDato().getIdents();
            for(size_t i=0; i < identsrem.size() ;i++){
                for(size_t j=0; j < identsdest.size() ;j++){
                    if(identsrem[i]==identsdest[j])
                        identsresultantes.push_back(identsrem[i]);
                }
            }
        }
    }

    indicePrimario ip;

    for(size_t j=0; j < identsresultantes.size() ;j++){
        string id = to_string(identsresultantes[j]);
        ip.mostrarCorreo(id);
    }

}

Nodo<indiceSRem> *indicesecundario::buscaEnArbolRemi(Nodo<indiceSRem> *Apunt, string &d)
{
    if ( Apunt != nullptr ) {
        if ( Apunt->getDato().getRem() == d ){
            return Apunt;
        }
        else if ( Apunt->getDato().getRem() > d) {
            return buscaEnArbolRemi( Apunt->getIzq(), d );
        }else {
            return buscaEnArbolRemi( Apunt->getDer(), d );
        }
    }
    else {
        return nullptr;
    }
}

Nodo<indiceSDest> *indicesecundario::buscaEnArbolDest(Nodo<indiceSDest> *Apunt, string &d)
{
        if ( Apunt != nullptr ) {
            if ( Apunt->getDato().getDest() == d ){
                return Apunt;
            }
            else if ( Apunt->getDato().getDest() > d) {
                return buscaEnArbolDest( Apunt->getIzq(), d );
            }else {
                return buscaEnArbolDest( Apunt->getDer(), d );
            }
        }
        else {
            return nullptr;
        }
}

bool indicesecundario::Yaesta(unsigned int id,  ListaSimple<unsigned int> &identsresultantes)
{
    for(size_t i=0; i < identsresultantes.size(); i++){
        if(id==identsresultantes[i])
            return true;
    }
    return false;
}

void indicesecundario::OrAdmin()
{
    string remitente, destinatario;

    cin.ignore();
    cout<<"Ingrese el remitente: ";
    getline(cin, remitente); cout<<endl;

    cout<<"Ingrese el destinatario: ";
    getline(cin, destinatario); cout<<endl;

    OrComparasion(destinatario,remitente);
}

void indicesecundario::AndAdmin()
{
    string remitente, destinatario;

    cin.ignore();
    cout<<"Ingrese el remitente: ";
    getline(cin, remitente); cout<<endl;

    cout<<"Ingrese el destinatario: ";
    getline(cin, destinatario); cout<<endl;

    AndComparasion(destinatario,remitente);

}
