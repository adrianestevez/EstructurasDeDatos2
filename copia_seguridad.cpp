#include "copia_seguridad.h"
#include <correo.h>

Copia_Seguridad::Copia_Seguridad()
{

}


string Copia_Seguridad::unirRegistro(Correo &c) //pongo las comas entre cada dato
{
    fstream archivoCsv;
    string result;

    archivoCsv.open("CopiaSeguridad.csv", ios::in);
    if(!archivoCsv.is_open()){
        cout << "Su archivo no ha sido creado..." << endl;
        archivoCsv.close();
        return 0;
    }
    else{
        string id = to_string(c.getId());
        string fe = c.getFecha();
        string hr = c.getHora();
        string remi =convertir(c.getRemitente());
        string dest=convertir(c.getDestinatario());
        string copiaC=convertir(c.getCc());
        string copiaCC=convertir(c.getBcc());
        string asun=convertir(c.getAsunto());
        string cont=convertir(c.getContenido());
        string result = id + ","+ fe + "," + hr + "," + remi + "," + dest + "," + copiaC + "," + copiaCC + "," + asun + "," + cont + "\n";
        return result;
    }


}

string Copia_Seguridad::convertir(string aux2) //comillas, comas, saltos de linea detro de cada campo
{
    //aux= leo comillas, comas y saltos de linea dentro de cada campo
    //cadena=guardo los campos de aux ya con las dobles comillas y todoo
    //si cambiar es true, guardo en cont lo que habia en cadena, pero con comillas afuera, si no, lo guardo sin comillas
    string cont="";
    if(aux2 != ""){
        bool cambiar=false;
        string cadena="";
        string aux=aux2;
        for(unsigned int i=0; i<=aux.size(); i++){
            if(aux[i] == ','){
                cadena+=aux[i];
                cambiar=true;
            }if(aux[i]=='\"'){
                cadena+=aux[i];
                cadena+=aux[i];
                cambiar=true;
            }if(aux[i]=='\n'){
                cadena+=aux[i];
                cambiar=true;
            }
            if(aux[i]!=','&&aux[i]!='\"'&&aux[i]!='\n'){
                cadena+=aux[i];
            }
        }
        if(cambiar){
            cont+='\"'+cadena+'\"';
        }else{
            cont=cadena;
        }
    }
return cont;
}


void Copia_Seguridad::exportar(Correo &c)
{

    ifstream readWriteFile;
    fstream archivoCsv;

    readWriteFile.open( "bandeja.bin", ios::in | ios::binary);
    archivoCsv.open("CopiaSeguridad.csv",ios::out);


     if( !readWriteFile.is_open() or !archivoCsv.is_open()){
        cout<<"No se pudieron abrir los archivos. "<<endl;
        readWriteFile.close();
        archivoCsv.close();
      }else{
           archivoCsv   << "IDENTIFICADOR" << ','
                        << "FECHA" << ','
                        << "HORA" << ','
                        << "REMITENTE" << ','
                        << "DESTINATARIO" << ','
                        << "COPIA_CARBON" << ','
                        << "COPIA_CARBON_CIEGA" << ','
                        << "ASUNTO" << ','
                        << "CONTENIDO" << '\n';
           while(!readWriteFile.eof()){
                readWriteFile.read((char*) &c, sizeof (c.getCorreo()));
                if(c.getId()!=0 && unirRegistro(c)!=""){
                    archivoCsv<<unirRegistro(c);
                    c.setId(0);
                }
           }
            readWriteFile.close();

     }
}



void Copia_Seguridad::imprimirRegis(Correo &c)
{
    cout << endl << endl;
    cout << "Identificador: "<<c.getId()<< endl;
    cout << "Fecha: "<< c.getFecha() << endl;
    cout << "Hora: " << c.getHora()<< endl;
    cout << "Remitente: "<< c.getRemitente() << endl;
    cout << "Destinatario: " << c.getDestinatario() <<endl;
    cout << "Copia Carbon: " << c.getCc() << endl;
    cout << "Copia Carbon Copia: " << c.getBcc() << endl;
    cout << "Asunto: " << c.getAsunto()<< endl;
    cout << "Contenido: " << c.getContenido() << endl;
    cout << endl;
}
//Correo Copia_Seguridad:: guardarCampo(string cadena, int contador, Correo &cor){ //aux2, aux, c


    //return cor;
//}
/*
void Copia_Seguridad::agregarAlArchivo(Correo &cor){
    Correo c;
    fstream archivo;
    int answer;
    archivo.open("bandeja.bin", ios::binary| ios::out| ios::in);
    unsigned int distanciaBytes=(cor.getId()-1)*sizeof(c.getCorreo());
    //cout<<"DISTANCIA: "<<distanciaBytes;

    if (archivo.is_open())
    {
        archivo.seekg(distanciaBytes);
        archivo.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) );
        if(c.getId()==cor.getId()){
            cout<<"Correo "<<cor.getId()<<" ya existe. Desea sobrescribirlo? "<<endl
               <<"1. Si"<<endl<<"2. No"<<endl<<"Respuesta: ";
            cin>>answer; cin.ignore();
            if(answer==1){
                archivo.seekp(distanciaBytes);
                archivo.write(reinterpret_cast<char*>(&cor), sizeof(cor.getCorreo()) );
                cout<<"Correo "<<cor.getId()<<" copiados correctamente."<<endl;
                archivo.close();
            }
        }



    }else{
        archivo.open("bandeja.bin", ios::out);
        cout<<"El archivo apenas se abrio... (agregarAlArchivo)"<<endl;
    }

}*/

void Copia_Seguridad::agregarAlArchivo(Correo &cor){
    Correo c;
    fstream archivo;
    //int answer;
    archivo.open("bandeja.bin", ios::binary| ios::out| ios::in);
    unsigned int distanciaBytes=(cor.getId()-1)*sizeof(c.getCorreo());
    //cout<<"DISTANCIA: "<<distanciaBytes;

    if (archivo.is_open())
    {
        //archivo.seekg(distanciaBytes);
        //archivo.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) );
        /*if(c.getId()==cor.getId()){
                archivo.seekp(distanciaBytes);
                archivo.write(reinterpret_cast<char*>(&cor), sizeof(cor.getCorreo()) );
                cout<<"Correo "<<cor.getId()<<" copiados correctamente."<<endl;
                archivo.close();
            }*/

        archivo.seekp(distanciaBytes);
        archivo.write(reinterpret_cast<char*>(&cor), sizeof(cor.getCorreo()) );
       // cout<<"Correo "<<cor.getId()<<" copiados correctamente."<<endl;




    }else{
        archivo.open("bandeja.bin", ios::out);
        cout<<"El archivo apenas se abrio... (agregarAlArchivo)"<<endl;
    }

}
void Copia_Seguridad::importar()
{
    ifstream archivoCsv;
    archivoCsv.open("CopiaSeguridad.csv", ios::in);
    if(archivoCsv.is_open()){
        string conca = "";
        int estado=0;
        int cont = 0;
        Correo cor;
        archivoCsv.seekg(98);//contando el salto de linea
        while(!archivoCsv.eof()){
            if(archivoCsv.eof()){
                break;
            }
            char c;
            archivoCsv.get(c);
            switch (estado) {
            case 0:
                if(c=='"' && cont<9){
                    estado=2;
                }else if((c!='"' && c!=',' && c!='\n') && cont<9){
                    conca+=c;
                    estado=1;
                }else if(c==','){ //cuando el campo esta vacio
                    cont++;
                    if(cont>=1 && cont<=9){
                        //cor=guardarCampo(conca,cont, cor);
                        switch (cont) {
                        case 1: {
                            stringstream sstream (conca);
                            unsigned int result;
                            sstream >> result;
                            cor.setId(result);
                        }break;


                        case 2:{
                            const char *d = conca.c_str();
                            cor.setFecha(d);
                        }break;

                        case 3:{
                            const char *d = conca.c_str();
                            cor.setHora(d);
                        }break;

                        case 4:{
                            const char *d = conca.c_str();
                            cor.setRemitente(d);
                        }break;

                        case 5:
                        {
                            const char *d = conca.c_str();
                            cor.setDestinatario(d);
                        }break;

                        case 6:
                        {
                            const char *d = conca.c_str();
                            cor.setCc(d);
                        }break;

                        case 7:
                        {
                            const char *d = conca.c_str();
                            cor.setBcc(d);
                        }break;

                        case 8:
                        {
                            const char *d = conca.c_str();
                            cor.setAsunto(d);
                        }break;

                        case 9:
                        {
                            const char *d = conca.c_str();
                            cor.setContenido(d);
                        }break;

                        }

                        //imprimirRegis(cor);
                        estado=0;
                        conca="";
                        //auxi=cont;
                    }
                    if(cont==9){
                        agregarAlArchivo(cor);
                        estado=0;
                        conca="";
                        cont=0; //reiniciamos el contador para el siguiente registro
                    }
                    estado=0;
                }

                break;
            case 1:
                if(c==',' or c=='\n'){
                    cont++;
                    if(cont>=1 && cont<=9){
                        //cor=guardarCampo(conca,cont, cor);
                        switch (cont) {
                        case 1: {
                            stringstream sstream (conca);
                            unsigned int result;
                            sstream >> result;
                            cor.setId(result);
                        }break;


                        case 2:{
                            const char *d = conca.c_str();
                            cor.setFecha(d);
                        }break;

                        case 3:{
                            const char *d = conca.c_str();
                            cor.setHora(d);
                        }break;

                        case 4:{
                            const char *d = conca.c_str();
                            cor.setRemitente(d);
                        }break;

                        case 5:
                        {
                            const char *d = conca.c_str();
                            cor.setDestinatario(d);
                        }break;

                        case 6:
                        {
                            const char *d = conca.c_str();
                            cor.setCc(d);
                        }break;

                        case 7:
                        {
                            const char *d = conca.c_str();
                            cor.setBcc(d);
                        }break;

                        case 8:
                        {
                            const char *d = conca.c_str();
                            cor.setAsunto(d);
                        }break;

                        case 9:
                        {
                            const char *d = conca.c_str();
                            cor.setContenido(d);
                        }break;

                        }
                        //imprimirRegis(cor);
                        estado=0;
                        conca="";
                        //auxi=cont;
                    }
                    if(cont==9){
                        agregarAlArchivo(cor);
                        estado=0;
                        conca="";
                        cont=0; //reiniciamos el contador para el siguiente registro
                        //auxi=0;
                        //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                    }
                    estado=0;
                }else if(c!=',' && c!='"' && c!='\n'){
                    conca+=c;
                }

                break;
            case 2:
                if(c!='"'){
                    conca+=c;
                }else{
                    estado=3;
                }
                break;
            case 3:
                if(c=='"'){
                    conca+=c;
                    estado=2;
                }else if(c=='\n'){
                    conca+=c;
                    cont++;
                    if(cont>=1 && cont<=9){
                        //cor=guardarCampo(conca,cont, cor);
                        switch (cont) {
                        case 1: {
                            stringstream sstream (conca);
                            unsigned int result;
                            sstream >> result;
                            cor.setId(result);
                        }break;


                        case 2:{
                            const char *d = conca.c_str();
                            cor.setFecha(d);
                        }break;

                        case 3:{
                            const char *d = conca.c_str();
                            cor.setHora(d);
                        }break;

                        case 4:{
                            const char *d = conca.c_str();
                            cor.setRemitente(d);
                        }break;

                        case 5:
                        {
                            const char *d = conca.c_str();
                            cor.setDestinatario(d);
                        }break;

                        case 6:
                        {
                            const char *d = conca.c_str();
                            cor.setCc(d);
                        }break;

                        case 7:
                        {
                            const char *d = conca.c_str();
                            cor.setBcc(d);
                        }break;

                        case 8:
                        {
                            const char *d = conca.c_str();
                            cor.setAsunto(d);
                        }break;

                        case 9:
                        {
                            const char *d = conca.c_str();
                            cor.setContenido(d);
                        }break;

                        }
                        //imprimirRegis(cor);
                        estado=0;
                        conca="";
                    }
                    if(cont==9){
                        agregarAlArchivo(cor);
                        estado=0;
                        conca="";
                        cont=0; //reiniciamos el contador para el siguiente registro
                    }
                    estado=0;
                }else if(c==','){
                    cont++;
                    if(cont>=1 && cont<=9){
                        //cor=guardarCampo(conca,cont, cor);
                        switch (cont) {
                        case 1: {
                            stringstream sstream (conca);
                            unsigned int result;
                            sstream >> result;
                            cor.setId(result);
                        }break;


                        case 2:{
                            const char *d = conca.c_str();
                            cor.setFecha(d);
                        }break;

                        case 3:{
                            const char *d = conca.c_str();
                            cor.setHora(d);
                        }break;

                        case 4:{
                            const char *d = conca.c_str();
                            cor.setRemitente(d);
                        }break;

                        case 5:
                        {
                            const char *d = conca.c_str();
                            cor.setDestinatario(d);
                        }break;

                        case 6:
                        {
                            const char *d = conca.c_str();
                            cor.setCc(d);
                        }break;

                        case 7:
                        {
                            const char *d = conca.c_str();
                            cor.setBcc(d);
                        }break;

                        case 8:
                        {
                            const char *d = conca.c_str();
                            cor.setAsunto(d);
                        }break;

                        case 9:
                        {
                            const char *d = conca.c_str();
                            cor.setContenido(d);
                        }break;

                        }
                        //imprimirRegis(cor);
                        estado=0;
                        conca="";
                    }
                    if(cont==9){
                        agregarAlArchivo(cor);
                        estado=0;
                        conca="";
                        cont=0; //reiniciamos el contador para el siguiente registro
                        //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                    }
                    estado=0;

                }
                break;
            default:
                cout<<"OPCION INCORRECTA... REVISAR";
                break;
            }
        }
        archivoCsv.close();
    }else{
        cout << "Su archivo no ha sido creado..." << endl;
        }


}

void Copia_Seguridad::eliminarCsv(unsigned int id)
{
    fstream temporal;

    temporal.open("temporal.txt", ios::out);


    if( !temporal.is_open() ){
        //Archivo no ha sido creado.
        temporal.close();
        return;
    }

    ifstream archivoCsv;

    archivoCsv.open("CopiaSeguridad.csv", ios::in);
    if(!archivoCsv.is_open()){
        cout << "Su archivo CSV no existe" << endl;
        archivoCsv.close();
    }

    temporal << "IDENTIFICADOR,FECHA,HORA,REMITENTE,DESTINATARIO,COPIA_CARBON,COPIA_CARBON_CIEGA,ASUNTO,CONTENIDO" << endl;

    string conca = "";
    int estado=0;
    int cont = 0;

    Correo cor;

    bool found = false;
    archivoCsv.seekg(98);//contando el salto de linea

    while(!archivoCsv.eof()){
        if(archivoCsv.eof()){
            break;
        }
        char c;
        archivoCsv.get(c);
        switch (estado) {
        case 0:
            if(c=='"' && cont<9){
                estado=2;
            }else if((c!='"' && c!=',' && c!='\n') && cont<9){
                conca+=c;
                estado=1;
            }else if(c==','){ //cuando el campo esta vacio
                cont++;
                if(cont>=1 && cont<=9){
                    //cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    estado=0;
                    conca="";
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        //menuEliminarCSV(cor);
                    }else{
                        temporal<<unirRegistro(cor);
                    }
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                }
                estado=0;
            }

            break;
        case 1:
            if(c==',' or c=='\n'){
                cont++;
                if(cont>=1 && cont<=9){
                    //cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    //imprimirRegis(cor);
                    estado=0;
                    conca="";
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        //menuEliminarCSV(cor);
                    }else{
                        temporal<<unirRegistro(cor);
                    }
                    estado=0;
                    conca="";
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        //menuEliminarCSV(cor);
                    }else{
                        temporal<<unirRegistro(cor);
                    }
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                    //auxi=0;
                    //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                }
                estado=0;
            }else if(c!=',' && c!='"' && c!='\n'){
                conca+=c;
            }

            break;
        case 2:
            if(c!='"'){
                conca+=c;
            }else{
                estado=3;
            }
            break;
        case 3:
            if(c=='"'){
                conca+=c;
                estado=2;
            }else if(c=='\n'){
                conca+=c;
                cont++;
                if(cont>=1 && cont<=9){
                    //cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    //imprimirRegis(cor);
                    estado=0;
                    conca="";
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        //menuEliminarCSV(cor);
                    }else{
                        temporal<<unirRegistro(cor);
                    }
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                    //auxi=0;
                    //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                }
                estado=0;
            }else if(c==','){
                cont++;
                if(cont>=1 && cont<=9){
                   // cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    //imprimirRegis(cor);
                    estado=0;
                    conca="";
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        //menuEliminarCSV(cor);
                    }else{
                        temporal<<unirRegistro(cor);
                    }
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                    //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                }
                estado=0;

            }
            break;
        default:
            cout<<"OPCION INCORRECTA... REVISAR";
            break;
        }
    }
    archivoCsv.close();
    temporal.close();
    remove("CopiaSeguridad.csv");
    rename("temporal.txt","CopiaSeguridad.csv");

}


void Copia_Seguridad::modificarCsv(unsigned int id)
{
    fstream temporal;

    temporal.open("temporal.txt", ios::out);


    if( !temporal.is_open() ){
        //Archivo no ha sido creado.
        temporal.close();
        return;
    }

    ifstream archivoCsv;

    archivoCsv.open("CopiaSeguridad.csv", ios::in);
    if(!archivoCsv.is_open()){
        cout << "Su archivo CSV no existe" << endl;
        archivoCsv.close();
    }

    temporal << "IDENTIFICADOR,FECHA,HORA,REMITENTE,DESTINATARIO,COPIA_CARBON,COPIA_CARBON_CIEGA,ASUNTO,CONTENIDO" << endl;

    string conca = "";
    int estado=0;
    int cont = 0;
    //Email cor;
    //bool encabezado = false;
    Correo cor;

    bool found = false;
    archivoCsv.seekg(98);//contando el salto de linea

    while(!archivoCsv.eof()){
        if(archivoCsv.eof()){
            break;
        }
        char c;
        archivoCsv.get(c);
        switch (estado) {
        case 0:
            if(c=='"' && cont<9){
                estado=2;
            }else if((c!='"' && c!=',' && c!='\n') && cont<9){
                conca+=c;
                estado=1;
            }else if(c==','){ //cuando el campo esta vacio
                cont++;
                if(cont>=1 && cont<=9){
                    //cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    //imprimirRegis(cor);
                    estado=0;
                    conca="";
                    //auxi=cont;
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        menuModificarCSV(cor);

                    }
                    temporal<<unirRegistro(cor);
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                    //auxi=0;
                    //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                }
                estado=0;
            }

            break;
        case 1:
            if(c==',' or c=='\n'){
                cont++;
                if(cont>=1 && cont<=9){
                    //cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    //imprimirRegis(cor);
                    estado=0;
                    conca="";
                    //auxi=cont;
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        menuModificarCSV(cor);
                    }
                    temporal<<unirRegistro(cor);
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                    //auxi=0;
                    //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                }
                estado=0;
            }else if(c!=',' && c!='"' && c!='\n'){
                conca+=c;
            }

            break;
        case 2:
            if(c!='"'){
                conca+=c;
            }else{
                estado=3;
            }
            break;
        case 3:
            if(c=='"'){
                conca+=c;
                estado=2;
            }else if(c=='\n'){
                conca+=c;
                cont++;
                if(cont>=1 && cont<=9){
                   // cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    //imprimirRegis(cor);
                    estado=0;
                    conca="";
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        menuModificarCSV(cor);
                    }
                    temporal<<unirRegistro(cor);
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                    //auxi=0;
                    //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                }
                estado=0;
            }else if(c==','){
                cont++;
                if(cont>=1 && cont<=9){
                    //cor=guardarCampo(conca,cont, cor);
                    switch (cont) {
                    case 1: {
                        stringstream sstream (conca);
                        unsigned int result;
                        sstream >> result;
                        cor.setId(result);
                    }break;


                    case 2:{
                        const char *d = conca.c_str();
                        cor.setFecha(d);
                    }break;

                    case 3:{
                        const char *d = conca.c_str();
                        cor.setHora(d);
                    }break;

                    case 4:{
                        const char *d = conca.c_str();
                        cor.setRemitente(d);
                    }break;

                    case 5:
                    {
                        const char *d = conca.c_str();
                        cor.setDestinatario(d);
                    }break;

                    case 6:
                    {
                        const char *d = conca.c_str();
                        cor.setCc(d);
                    }break;

                    case 7:
                    {
                        const char *d = conca.c_str();
                        cor.setBcc(d);
                    }break;

                    case 8:
                    {
                        const char *d = conca.c_str();
                        cor.setAsunto(d);
                    }break;

                    case 9:
                    {
                        const char *d = conca.c_str();
                        cor.setContenido(d);
                    }break;

                    }
                    //imprimirRegis(cor);
                    estado=0;
                    conca="";
                }
                if(cont==9){
                    if(id==cor.getId() && found==false){
                        found=true;
                        menuModificarCSV(cor);
                    }
                    temporal<<unirRegistro(cor);
                    estado=0;
                    conca="";
                    cont=0; //reiniciamos el contador para el siguiente registro
                    //cout<<"Contador ya es 9, se guardo el registro"<<endl;
                }
                estado=0;

            }
            break;
        default:
            cout<<"OPCION INCORRECTA... REVISAR";
            break;
        }
    }
    archivoCsv.close();
    temporal.close();
    remove("CopiaSeguridad.csv");
    rename("temporal.txt","CopiaSeguridad.csv");

}





void Copia_Seguridad:: menuModificarCSV(Correo &cor){
    char myChar[160], myCharAsunto[200], myCharContenido[1000];
    string op;
    imprimirRegis(cor);
    while(true){
        cout<< "Selecciona una opcion para modificar:" << endl;
        cout<<"1)Remitente" << endl;
        cout<<"2)Destinatario" << endl;
        cout<<"3)Copia Carbon" << endl;
        cout<<"4)Copia Carbon Ciega" << endl;
        cout<<"5)Asunto " << endl;
        cout<<"6)Contenido" << endl;
        cout<<"7)Salir" << endl;
        getline(cin,op);
        if(op == "1"){
            cout<<"Nuevo Remitente: ";
            cin.getline(myChar,160);
            cor.setRemitente(myChar);
        }
        else if(op == "2"){
            cout<<"Nuevo Destinatario: ";
            cin.getline(myChar,160);
            cor.setDestinatario(myChar);
        }
        else if(op == "3"){
            cout<<"Nueva Copia Carbon: ";
            cin.getline(myChar,160);
            cor.setCc(myChar);
        }
        else if(op == "4"){
            cout<<"Nueva Copia Carbon Ciega: ";
            cin.getline(myChar,160);
            cor.setBcc(myChar);
        }
        else if(op == "5"){
            cout<<"Nuevo Asunto: ";
            cin.getline(myCharAsunto,200);
            cor.setAsunto(myCharAsunto);
        }
        else if(op == "6"){
            cout<<"Nuevo Contenido: ";
            cin.getline(myCharContenido,1000,'|');
            cor.setContenido(myCharContenido);
        }
        else if(op == "7"){
            break;
        }else{
            cout<<"Opcion incorrecta"<<endl;
        }
    }
}
