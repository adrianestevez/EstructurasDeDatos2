#include "dispersion.h"

dispersion::NodoDispersion dispersion::getMisNodosDispersion()
{
    return misNodosDispersion;
}

dispersion::dispersion()
{

}

string dispersion::getRemitente() const
{
    return misNodosDispersion.remitente;
}

void dispersion::setRemitente(const string &value)
{
    strcpy(misNodosDispersion.remitente, value.c_str());
}

int dispersion::getId() const
{
    return misNodosDispersion.id;
}

void dispersion::setId(const int &value)
{
    misNodosDispersion.id = value;
}

int dispersion::funcionDispersionPJW(char *clave)
{
    char *p;
    unsigned int h = 0, g;
    for(p = clave ; *p != '\0' ; p++)
    {
        h = (h << 4) + (*p);
        g = h&0xF0000000;
        if(g > 1)
        {
            h = h ^ (g << 24);
            h = h ^ g;
        }
    }
    return (h%PRIMO);
}

void dispersion::anadirRegistro(int pos, dispersion miNodo)
{
    tabla[pos].push_back(miNodo);
}

void dispersion::LlenarTabla()
{

    ifstream archivoDatos;
    archivoDatos.open("bandeja.bin", ios::in | ios::binary);

    if( archivoDatos.is_open() ) {
        archivoDatos.clear();

        cerr << "Creando tabla..." << endl << endl;

        //Indices unIndice;
        Correo unCorreo;
        unsigned int NRR;
        int llavePrim;
        int pos = 0;
        dispersion TablaDispersion;

        char clave[E];
        string aux;

        //recorrer todo el archivo de datos
        //extraer correo por correo

        archivoDatos.seekg( 0 );
        while ( !archivoDatos.eof() ) {
            NRR = archivoDatos.tellg();

            archivoDatos.read(reinterpret_cast<char *>(&unCorreo), sizeof(unCorreo.getCorreo())); // extrae un correo

            if ( archivoDatos.eof() )
                break;


            //meter indice
            llavePrim = unCorreo.getId();
            aux = unCorreo.getRemitente();

            TablaDispersion.setId( llavePrim );
            TablaDispersion.setRemitente( aux );

            strcpy(clave, " ");

            //este for quita a partir del @ para evitar el peor caso donde todo colisiona
            for ( size_t i = 0 ; i< aux.length() ; i++ ) {
                if( aux[i] == '@') {
                    clave[i] = '\0';
                    break;
                }
                else{
                    clave[i] = aux[i];
                }
            }

            pos = funcionDispersionPJW(clave);

            anadirRegistro(pos, TablaDispersion);
        }
        archivoDatos.close();

    }
    else {
        cerr << "Error al crear el archivo. No se pudo abrir archivo de datos." << endl << endl;
    }
}

void dispersion::BuscarEnTabla(string remitente)
{
    string aux = remitente;
    char clave[E];
    ListaSimple <dispersion> TablaDispersion;


    //este for quita a partir del @ para evitar el peor caso donde todo colisiona
    for ( size_t i = 0 ; i< aux.length() ; i++ ) {
        if( aux[i] == '@') {
            clave[i] = '\0';
            break;
        }
        else{
            //cout <<aux[i]<<endl;
            clave[i] = aux[i];
        }
    }

    int pos = funcionDispersionPJW( clave );
    unsigned int id;
    TablaDispersion = tabla[pos];

    if ( TablaDispersion.size() != 0) {

        Correo unCorreo;
        dispersion element;

        for ( size_t i = 0 ; i < TablaDispersion.size() ; i++ ) {
            element = TablaDispersion.position(i);

            id = element.getId();
            unCorreo.Leer_AD(id);
        }
    }
    else {
        cout << "No hay registros con esa llave." << endl << endl;
    }
}

void dispersion::FuncionAdminBuscar()
{
    LlenarTabla();
    string remitente;
    cout<<"Ingrese el remitente a buscar: ";
    cin>>remitente; cout<<endl;
    BuscarEnTabla(remitente);
}

void dispersion::SerializarTabla()
{
    LlenarTabla();
    fstream archivoTemporal("temporal.dat",ios::out|ios::binary);

    if(!archivoTemporal.is_open()){
        archivoTemporal.open("temporal.dat", ios::out|ios::binary);
    }

    archivoTemporal.clear();
    archivoTemporal.seekp(0);
    ListaSimple <dispersion> TablaDispersion;
    Correo unCorreo;
    dispersion element;
    //unsigned int id;
    //string remitente;

    if(archivoTemporal.is_open()){
        for (unsigned int j = 0; j < PRIMO; ++j) {
            TablaDispersion = tabla[j];

            if(!TablaDispersion.empty()){
                for ( size_t i = 0 ; i < TablaDispersion.size() ; i++ ) {
                    element = TablaDispersion.position(i);

                    archivoTemporal<<j<<"|";
                    archivoTemporal<<element.getId()<<"|";
                    archivoTemporal<<element.getRemitente()<<endl;
                }
            }


        }
    }else{
        cout<<"Problema al abrir el archivo"<<endl;
    }

    archivoTemporal.close();
    remove("tabladispersion.dat");
    rename("temporal.dat","tabladispersion.dat");


}

void dispersion::ImportarDesdeArchTabla()
{
    string s;
    //LlenarTabla();
    fstream archivoTabla("tabladispersion.dat",ios::in|ios::binary);

    if(!archivoTabla.is_open()){
        archivoTabla.open("tabladispersion.dat", ios::in|ios::binary);
    }

     int pos;
     dispersion TablaDispersion;
    while (!archivoTabla.eof()) {

        getline(archivoTabla,s,'|');

        if(archivoTabla.eof())
            break;

        pos =stoi(s);

        getline(archivoTabla,s,'|');
        TablaDispersion.setId(stoi(s));


        getline(archivoTabla,s);
        TablaDispersion.setRemitente(s);
        anadirRegistro(pos, TablaDispersion);

    }

    archivoTabla.close();

}



/*dispersion unaTabla;

LlenarTabla();
ofstream archivoTemporal;
archivoTemporal.open("temporal.dat", ios::out|ios::binary);
if(!archivoTemporal.is_open()){
    archivoTemporal.open("temporal.dat", ios::out|ios::binary);
}

archivoTemporal.clear();
archivoTemporal.seekp(0);
ListaSimple <dispersion> TablaDispersion;
Correo unCorreo;
dispersion element;
//unsigned int id;
//string remitente;

for(int i = 0; i < PRIMO ; i++){
    TablaDispersion = tabla[i];

    if ( TablaDispersion.size() != 0) {
        for ( size_t i = 0 ; i < TablaDispersion.size() ; i++ ) {
            element = TablaDispersion.position(i);
            archivoTemporal.write(reinterpret_cast<const char *>( &element ), sizeof( element.getMisNodosDispersion() ));
        }
    }
}

archivoTemporal.close();
remove("tabladispersion.dat");
rename("temporal.dat","tabladispersion.dat");*/
