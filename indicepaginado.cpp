#include "indicepaginado.h"

indicePaginado::indicePaginado()
{

}


//Getters y setters
unsigned long indicePaginado::getReferencia() const
{
    return misNodosIndicePaginado.referencia;
}

void indicePaginado::setReferencia(unsigned long value)
{
    misNodosIndicePaginado.referencia = value;
}


void indicePaginado::setLlave(const string &value)
{
    strcpy(misNodosIndicePaginado.llave, value.c_str());
}

string indicePaginado::getLlave() const
{
    return misNodosIndicePaginado.llave;
}

indicePaginado::nodoindicePaginado indicePaginado::getMisNodosIndice() const
{
    return misNodosIndicePaginado;
}

void indicePaginado::setFecha_hora(const string &value)
{
    strcpy(misNodosIndicePaginado.fecha_hora, value.c_str());
}

string indicePaginado::getFecha_hora() const
{
    return misNodosIndicePaginado.fecha_hora;
}


//Sobrecarga de operadores
ostream &operator <<( ostream &escribe, const indicePaginado &unIndice )
{
    escribe << "LLave: " << unIndice.getLlave()<<endl
            << "Referencia  : " << unIndice.getReferencia() << endl
            << "Fecha y hora: " << unIndice.getFecha_hora() <<endl;
    return escribe;
}

bool indicePaginado::operator > ( indicePaginado &i )
{
    return misNodosIndicePaginado.llave > i.getLlave();
}

bool indicePaginado::operator < ( indicePaginado &i )
{
    return misNodosIndicePaginado.llave < i.getLlave();
}

bool indicePaginado::operator == ( indicePaginado &i )
{
    return strcmp(misNodosIndicePaginado.llave, i.getLlave().c_str());
}



void indicePaginado::funcionAdmin()
{
      fstream archivoIndice;

     //abro el archivo
    archivoIndice.open("indices.dat", ios::in|ios::binary|ios::out);
    if(!archivoIndice.is_open()){
        archivoIndice.open("indices.dat", ios::in|ios::binary|ios::out);
    }
    archivoIndice.close();
    //llenarArbolDesdeArchivoCorreo();

    if(ip.Actualizado()){//si esta actualizado, se queda asi hasta que se haga alguna modificacion el arbol se carga desde el archivo de indices
        llenarArbolDesdeArchivoIndice();

    }else{//el arbol y el archivo de indices se cargan desde el archivo de correos electronicos
        llenarArbolDesdeArchivoCorreo(); //lleno el arbol con el archivo correos

    }




}

void indicePaginado::llenarArbolDesdeArchivoCorreo() //antes era llenarArbol
{

    cout<<endl<<"Desde correos INDICE PAGINADO"<<endl;
    //fecha y hr
    char            fmt[64], buf[64];
    struct timeval  tv;
    struct tm       *tm;
    //
    indicePaginado unIndice;
    Correo c;
    unsigned long ref;
    //char llave[10];
    string llave;
    unsigned int cont=0;



    ifstream archivoCorreo;
    archivoCorreo.open("bandeja.bin", ios::in | ios::binary);

    if( archivoCorreo.is_open() ) {

        archivoCorreo.clear();

        //recorrer todo el archivo de datos guardar correo por correo

        archivoCorreo.seekg(0);
        while ( !archivoCorreo.eof() and cont<10) {

            if ( archivoCorreo.eof() ) {
                break;
            }

            ref = archivoCorreo.tellg();

            archivoCorreo.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) ); //extrae un correo

            if(c.getId()!=0){

                //meter indice
                llave = to_string( c.getId() );


                gettimeofday(&tv, NULL);
                char buff[100];
                time_t now = time (0);

                strftime (buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
                //cout << buff;
               /* if(tm = localtime(&tv.tv_sec) != NULL)
                {
                    strftime(fmt, sizeof fmt, "%Y%m%d%H%M%S%%06u", tm);
                    snprintf(buf, sizeof buf, fmt, tv.tv_usec);
                }*/

                unIndice.setLlave(llave);
                unIndice.setReferencia( ref );
                unIndice.setFecha_hora(buf);

                cout<<unIndice.getFecha_hora()<<endl;
                myTreePaginado.insertar( myTreePaginado.getRaiz(), unIndice ); //uso sobrecarga de operadores
                cont++;
            }
        }
        archivoCorreo.close();

    }
    else {
        cout << "Error al crear el archivo. No se pudo abrir archivo de datos." << endl << endl;
    }
}

void indicePaginado::llenarArbolDesdeArchivoIndice()
{

    cout<<endl<<"Desde indices INDICE PAGINADO"<<endl;
    //fecha y hr
    char            fmt[64], buf[64];
    struct timeval  tv;
    struct tm       *tm;
    //
    indicePaginado unIndice;
    indicePrimario unIndicePrimario;
    unsigned long ref;
    //char llave[10];
    string llave;
    unsigned int cont=0;

    ifstream archivoIndice;
    archivoIndice.open("indices.dat", ios::in|ios::binary);


    if( archivoIndice.is_open() ) {

        archivoIndice.clear();

        //recorrer todo el archivo indice por indice

        archivoIndice.seekg( sizeof( unIndicePrimario.getNodos() ), ios::beg); //saltar la posicion del encabezado

        while ( !archivoIndice.eof() and cont<10) {

            if ( archivoIndice.eof() ) {
                break;
            }
            archivoIndice.read( reinterpret_cast<char *>( &unIndice ), sizeof( unIndicePrimario.getNodos() ) ); //extrae un indice


            gettimeofday(&tv, NULL);
            char buff[100];
            time_t now = time (0);

            strftime (buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
           /* if((tm = localtime(&tv.tv_sec)) != NULL)
            {
                strftime(fmt, sizeof fmt, "%Y%m%d%H%M%S%%06u", tm);
                snprintf(buf, sizeof buf, fmt, tv.tv_usec);
            }*/


            unIndice.setFecha_hora(buf);

            myTreePaginado.insertar( myTreePaginado.getRaiz(), unIndice ); //uso sobrecarga de operadores
            cont++;

        }
        archivoIndice.close();

    }
    else {
        cout << "Error al crear el archivo. No se pudo abrir archivo de indices." << endl << endl;
    }

}

void indicePaginado::buscarPorID()
{
    system("pause");
    string myId;
    //Para este momento se supone que el arbol ya debe estar cargado y actualizado
    cout<<"Ingresa el id a buscar: ";
    cin>>myId;

    mostrarCorreo(myId);
}

void indicePaginado::mostrarCorreo(string& myId){
    cout<<"Mostrar "<<myId<<endl;

    //fecha y hr
    char            fmt[64], buf[64];
    struct timeval  tv;
    struct tm       *tm;
    //
    indicePaginado unIndice, unIndiceAuxEliminar;
    indicePrimario unIndicePrimario;
    Correo c;
    ifstream correoEntrada;
    Nodo<indicePaginado> *aux = nullptr;
    bool encontrado=false;
    //myTreePaginado.recorridoInOrden(myTreePaginado.getRaiz());
    aux = buscaEnArbol(myTreePaginado.getRaiz(), myId );

    if (aux and aux->getDato().getLlave()!="0") {

        unIndice.setLlave( aux->getDato().getLlave() );
        unIndice.setReferencia( aux->getDato().getReferencia() );

        //modifico la fecha y la hora del arbol
        gettimeofday(&tv, NULL);
        char buff[100];
        time_t now = time (0);

        strftime (buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
        /*if((tm = localtime(&tv.tv_sec)) != NULL){
            strftime(fmt, sizeof fmt, "%Y%m%d%H%M%S%%06u", tm);
            snprintf(buf, sizeof buf, fmt, tv.tv_usec);
        }*/
        unIndice.setFecha_hora(buf); //aux->getDato().getFecha_hora()

        correoEntrada.open("bandeja.bin", ios::in | ios::binary);

        if (!correoEntrada) {
            cout << "No se pudo abrir el archivo." << endl << endl;
        }else {
            // Buscar la posicion a leer
            correoEntrada.seekg(unIndice.getReferencia());
            correoEntrada.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) );
            correoEntrada.close();
            if(c.getFecha()==" "){ //lo hago para saber si el correo sigue vigente en el archivo de correos o si el usuario lo elimino
                cout<<"Elemento no encontrado."<<endl;
            }else{
                cout << "Elemento: " << unIndice.getLlave() << " ha sido encontrado en el arbol." << endl << endl;
                cout << c;
            }

        }
    }else {
        cout << "Elemento no encontrado en el arbol, lo buscaremos en el archivo." << endl;
        ifstream archivoIndice;
        archivoIndice.open("indices.dat", ios::in|ios::binary);


        if( archivoIndice.is_open() ) {

            archivoIndice.clear();

            //recorrer todo el archivo indice por indice

            archivoIndice.seekg( sizeof( unIndicePrimario.getNodos()), ios::beg); //saltar la posicion del encabezado
            //cout<<"Tellg: "<<archivoIndice.tellg();
            while ( !archivoIndice.eof()) {

                if ( archivoIndice.eof() ) {
                    break;
                }
                archivoIndice.read( reinterpret_cast<char *>( &unIndice ), sizeof( unIndicePrimario.getNodos() ) ); //extrae un indice

                if(unIndice.getLlave()==myId){ //si lo encontramos en el archivo de indices

                    //Borrar el elemento mas antiguo del arbol
                    string fechaHora;
                    fechaHora=myTreePaginado.getRaiz()->getDato().getFecha_hora();
                    recorridoInOrden(myTreePaginado.getRaiz(), fechaHora);
                    cout<<"Id del correo a eliminar del arbol:"<<idMenor<<endl;
                    //eliminamos unIndiceAuxEliminar

                    unIndiceAuxEliminar.setFecha_hora(fechaHora);
                    unIndiceAuxEliminar.setLlave(idMenor);
                    unIndiceAuxEliminar.setReferencia(referenciaMenor);

                    myTreePaginado.eliminar(myTreePaginado.getRaiz(),unIndiceAuxEliminar);

                    cout<<"Eliminamos uno..."<<endl;
                    //myTreePaginado.recorridoInOrden(myTreePaginado.getRaiz());

                    //insertar el nuevo elemento al arbol
                    encontrado=true;
                    gettimeofday(&tv, NULL);
                    gettimeofday(&tv, NULL);
                    char buff[100];
                    time_t now = time (0);

                    strftime (buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
                    /*if((tm = localtime(&tv.tv_sec)) != NULL){
                        strftime(fmt, sizeof fmt, "%Y%m%d%H%M%S%%06u", tm);
                        snprintf(buf, sizeof buf, fmt, tv.tv_usec);
                    }*/
                    unIndice.setFecha_hora(buf);
                    myTreePaginado.insertar(myTreePaginado.getRaiz(),unIndice);
                    cout<<"Agregamos el nuevo..."<<endl;

                    //imprimimos el correo
                    correoEntrada.open("bandeja.bin", ios::in | ios::binary);

                    if (!correoEntrada) {
                        cout << "No se pudo abrir el archivo." << endl << endl;
                    }else {
                        // Buscar la posicion a leer
                        correoEntrada.seekg(unIndice.getReferencia());
                        correoEntrada.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) );
                        correoEntrada.close();
                        if(c.getFecha()==" "){ //lo hago para saber si el correo sigue vigente en el archivo de correos o si el usuario lo elimino
                            cout<<"Elemento no encontrado."<<endl;
                        }else{
                            cout << "Elemento: " << unIndice.getLlave() << " ha sido encontrado en el arbol." << endl << endl;
                            cout << c;
                        }

                    }
                }
            }
            if(encontrado==false){
                cout<<"El correo no esta ni en el arbol ni en el archivo de indices"<<endl;
            }
            archivoIndice.close();

        }else {
            cout << "Error al crear el archivo. No se pudo abrir archivo de indices." << endl << endl;
        }

    }
    system("pause");


}

void indicePaginado::recorridoInOrden(Nodo<indicePaginado> *Apunt, string& fechaHora)
{

    if ( Apunt != nullptr ) {
        recorridoInOrden( Apunt->getIzq(),fechaHora );
        if(Apunt->getDato().getFecha_hora()<fechaHora){
            fechaHora=Apunt->getDato().getFecha_hora();
            idMenor=Apunt->getDato().getLlave();
            fechaHoraMenor=Apunt->getDato().getFecha_hora();
            referenciaMenor=Apunt->getDato().getReferencia();
        }
        //cout << Apunt->getDato() << " - ";
        recorridoInOrden( Apunt->getDer(),fechaHora );

    }

}


Nodo<indicePaginado> * indicePaginado::buscaEnArbol(Nodo<indicePaginado> *Apunt, string &d){

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
















































