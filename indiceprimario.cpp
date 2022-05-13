#include "indiceprimario.h"

indicePrimario::indicePrimario()
{

}

bool indicePrimario::operator > ( indicePrimario &i )
{
    return misNodosIndice.llave > i.getLlave();
}

bool indicePrimario::operator < ( indicePrimario &i )
{
    return misNodosIndice.llave < i.getLlave();
}

bool indicePrimario::operator == ( indicePrimario &i )
{
    return strcmp(misNodosIndice.llave, i.getLlave().c_str());
}


//Getters y setters
unsigned long indicePrimario::getReferencia() const
{
    return misNodosIndice.referencia;
}

void indicePrimario::setReferencia(unsigned long value)
{
    misNodosIndice.referencia = value;
}

void indicePrimario::setLlave(const string &value)
{
    strcpy(misNodosIndice.llave, value.c_str());
}

string indicePrimario::getLlave() const
{
    return misNodosIndice.llave;
}

indicePrimario::nodoIndicePrimario indicePrimario::getNodos() const
{
    return misNodosIndice;
}


void indicePrimario::llenarArbol()
{
    //cout<<"Por bandeja"<<endl;

    indicePrimario unIndice;
    Correo c;
    unsigned long ref;
    string llave;



    ifstream archivoDatos;
    archivoDatos.open("bandeja.bin", ios::in | ios::binary);

    if( archivoDatos.is_open() ) {

        archivoDatos.clear();

        archivoDatos.seekg( 0 );
        while ( !archivoDatos.eof() ) {

            if ( archivoDatos.eof() ) {
                break;
            }

            ref = archivoDatos.tellg();//Posicion del correo

            archivoDatos.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) ); //extrae un correo

            if(c.getId()!=0){

                //meter indice
                llave = to_string( c.getId() );
                unIndice.setLlave(llave);
                unIndice.setReferencia( ref );
                myTree.insertar( myTree.getRaiz(), unIndice ); //uso sobrecarga de operadores
            }
        }
        archivoDatos.close();
    }
    else {
        cout << "Error al crear el archivo. No se pudo abrir archivo de datos." << endl << endl;
    }
}

void indicePrimario::funcionAdmin()
{

    fstream archivoIndice;

     //abro el archivo
    archivoIndice.open("indices.dat", ios::in|ios::binary|ios::out);
    if(!archivoIndice.is_open()){
        archivoIndice.open("indices.dat", ios::in|ios::binary|ios::out);
    }
    archivoIndice.close();
    //Checo si el archivo esta vacio.
    //Si esta vacio, checo si el de correos tambien esta vacio
    //Si el de correos no esta vacio, estonces pongo el estado de desactualizado


    if(Actualizado()){//si esta actualizado, se queda asi hasta que se haga alguna modificacion
        //el arbol se carga desde el archivo de indices
        LlenarDesdeIndice();

    }else{//el arbol y el archivo de indices se cargan desde el archivo de correos electronicos
        llenarArbol(); //lleno el arbol con el archivo correos
        ActualizarArchivo(); //leno el archivo de indices con el arbol que acabo de llenar
    }
}

void indicePrimario::mostrarCorreo(string& myId){
    llenarArbol();
    indicePrimario unIndice;
    Nodo<indicePrimario> *aux = nullptr;

    aux = buscaEnArbol(myTree.getRaiz(), myId );

    if (aux && aux->getDato().getLlave() != "0") {


        unIndice.setLlave( aux->getDato().getLlave() );
        unIndice.setReferencia( aux->getDato().getReferencia() );

        //En este punto ya se tiene el registro y se puede sacar el correo

        Correo c;
        ifstream correoEntrada;
        correoEntrada.open("bandeja.bin", ios::in | ios::binary);

        if (!correoEntrada) {
            cout << "No se pudo abrir el archivo." << endl << endl;
        }else {
            // Buscar la posicion a leer
            correoEntrada.seekg(unIndice.getReferencia());
            correoEntrada.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) );
            correoEntrada.close();

            cout << "Elemento: " << unIndice.getLlave() << " ha sido encontrado en el arbol." << endl;
            cout << c;
           /* if(c.getFecha()==" "){//Si el usuario fue eliminado
                cout<<"El elemento fue eliminado"<<endl;
            }else{
            }*/
        }
    }else {
        cout << "Elemento no encontrado." << endl << endl;
    }
}

Nodo<indicePrimario> * indicePrimario::buscaEnArbol(Nodo<indicePrimario> *Apunt, string &d){
    if ( Apunt != nullptr ) {
        if ( Apunt->getDato().getLlave() == d ){
            return Apunt;
        }
        else if ( Apunt->getDato().getLlave() > d) {
            return buscaEnArbol( Apunt->getIzq(), d );
        }else {
            return buscaEnArbol( Apunt->getDer(), d );
        }
    }
    else {
        return nullptr;
    }
}

void indicePrimario::LlenarArchivo(Nodo<indicePrimario> *Apunt, ofstream& archivoTemporal)
{
    indicePrimario unIndice;
    unsigned long ref;
    string llave;

    if(banderaAct==0){ //cuando llamamos al recorridoInOrden por pirmera vez
        if(!archivoTemporal.is_open()){
            cout<<"Error. El archivo Temporal no se ha podido abrir"<<endl;
            archivoTemporal.open("temporal.dat",ios::out|ios::binary); //ios::out|
        }else{
            banderaAct=1;
            archivoTemporal.seekp(sizeof( unIndice.getNodos() ));
        }

    }
    if(banderaAct==1){ //cuando llamo
        //recorrido inorder
        if(Apunt == nullptr){
            return;
        }
        LlenarArchivo(Apunt->getIzq() ,archivoTemporal);
        ref=Apunt->getDato().getReferencia();
        llave=Apunt->getDato().getLlave();

        unIndice.setLlave(llave);
        unIndice.setReferencia(ref);

        archivoTemporal.write(reinterpret_cast<const char *>( &unIndice ), sizeof( unIndice.getNodos() ));

        LlenarArchivo( Apunt->getDer(),archivoTemporal );

    }

}

bool indicePrimario::Actualizado()
{
    indicePrimario unIndice;
    ifstream archivoIndice;
    archivoIndice.open("indices.dat", ios::in|ios::binary);
    if(!archivoIndice.is_open()){
        archivoIndice.open("indices.dat", ios::in|ios::binary);
        return false;
    }else{
        archivoIndice.seekg(0);
        archivoIndice.read( reinterpret_cast<char *>( &unIndice ), sizeof( unIndice.getNodos() ) );

        if(unIndice.getLlave()=="1" && unIndice.getReferencia()==1){ //archivo actualizado
            return 1;
        }else{
            return 0;
        }
        archivoIndice.close();
    }

}

void indicePrimario::Desactualizar()
{
    ofstream archivoIndice;
    indicePrimario unIndice;
    archivoIndice.open("indices.dat", ios::out|ios::binary);
    if(!archivoIndice.is_open()){
        archivoIndice.open("indices.dat", ios::out|ios::binary);
    }
    archivoIndice.seekp(0);
    unIndice.setLlave("0");
    unIndice.setReferencia(0);
    archivoIndice.write( reinterpret_cast<char *>( &unIndice ), sizeof( unIndice.getNodos() ) );
    archivoIndice.close();
}

void indicePrimario::BuscarId()
{
    string myId;
    //Para este momento se supone que el arbol ya debe estar cargado y actualizado
    cout<<"Ingresa el id a buscar: ";
    cin>>myId;

    mostrarCorreo(myId);
}

void indicePrimario::LlenarDesdeIndice()
{
    cout<<"Por indice"<<endl;

    indicePrimario unIndice;
    unsigned long ref;
    string llave;

    ifstream archivoIndice;
    archivoIndice.open("indices.dat", ios::in|ios::binary);

    if( archivoIndice.is_open() ) {

        archivoIndice.clear();

        archivoIndice.seekg( sizeof( unIndice.getNodos() ), ios::beg ); //saltar la posicion del encabezado
        while ( !archivoIndice.eof() ) {

            if ( archivoIndice.eof() ) {
                break;
            }
            archivoIndice.read( reinterpret_cast<char *>( &unIndice ), sizeof( unIndice.getNodos() ) ); //extrae un indice

            ref = unIndice.getReferencia();
            llave = unIndice.getLlave();

            unIndice.setLlave(llave);
            unIndice.setReferencia( ref );
            myTree.insertar( myTree.getRaiz(), unIndice );

        }
        archivoIndice.close();

    }
    else {
        cout << "Error al crear el archivo. No se pudo abrir archivo de indices." << endl << endl;
    }
}

void indicePrimario::ActualizarArchivo()
{
    indicePrimario unIndice;

    llenarArbol();
    ofstream archivoTemporal;
    archivoTemporal.open("temporal.dat", ios::out|ios::binary);
    if(!archivoTemporal.is_open()){
        archivoTemporal.open("temporal.dat", ios::out|ios::binary);
    }

    archivoTemporal.clear();
    archivoTemporal.seekp(0);

    //archivo desactualizado
    unIndice.setLlave("0");
    unIndice.setReferencia(0);
    archivoTemporal.write(reinterpret_cast<const char *>( &unIndice ), sizeof( unIndice.getNodos() ));

    //archivo actualizado
    archivoTemporal.seekp(0);
    unIndice.setLlave("1");
    unIndice.setReferencia(1);
    archivoTemporal.write(reinterpret_cast<const char *>( &unIndice ), sizeof( unIndice.getNodos() ));
    LlenarArchivo(myTree.getRaiz(), archivoTemporal);

    archivoTemporal.close();
    remove("indices.dat");
    rename("temporal.dat","indices.dat");
}



void indicePrimario::Eliminar(string& myId)
{
    indicePrimario unIndice;
    Nodo<indicePrimario> *aux = nullptr;
    Correo c;

    aux = buscaEnArbol(myTree.getRaiz(), myId );
    ofstream archivoindice;

    if (aux) {

        //cout << "Elemento: " << aux->getDato().getLlave() << " ha sido encontrado en el arbol." << endl << endl;
        unIndice.setLlave( aux->getDato().getLlave() );
        unIndice.setReferencia( aux->getDato().getReferencia() );

        cout << "Elemento: " << unIndice.getLlave() << " ha sido encontrado en el arbol." << endl << endl;

        c.Eliminar_Id(stoi(unIndice.getLlave()));
        myTree.eliminar(aux,unIndice);

    }else {
        cout << "Elemento no encontrado." << endl << endl;
    }
    system("pause");
}


/*
distBytes = ((stoi(Apunt->getDato().getLlave()) - 1) * sizeof (struct nodoIndicePrimario));//buscar por nrr
archivoindices.seekp(distBytes);//localizar archivo de escritura
archivoindices.write((char*)&misNodosIndice, sizeof (struct nodoIndicePrimario));//escribir en el archivo
archivoindices.close();//cerrar archivo
*/


