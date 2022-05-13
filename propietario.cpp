#include "propietario.h"
#define E 160
#define M 1000

Propietario::Propietario()
{

}

void Propietario::Modificar(unsigned int identificadorBuscado){
    Correo c;
    ifstream archivoPropietario;
    archivoPropietario.open("CopiaSeguridadPROPIETARIO.dat",ios::binary |ios::in);

    ofstream temporal;
    temporal.open("temporal.dat",ios::binary |ios::out);

    bool flag=false;
    int tamId, tamFecha, tamHora, tamRemi, tamDest, tamCC, tamCCC, tamAsu, tamCont;
    unsigned int id;
    char fecha[E], hora[E], remitente[E], destinatario[E], copiaC[E], copiaCC[E], asunto[E], contenido[M];

    //puntero a donde queremos mandar el dato, el tamano en bytes del dato que vamos a leer,
    //la cantidad de datos a leer multiplicada por el tamanio de cada dato


    if(!archivoPropietario.is_open() or !temporal.is_open()){
        cout<<"No se pudieron abrir los archivos."<<endl;
//        archivoPropietario.open("CopiaSeguridadPROPIETARIO.dat",ios::binary |ios::in|ios::out);
//        temporal.open("temporal.dat",ios::binary |ios::out);
        archivoPropietario.close();
        temporal.close();
    }else{
        archivoPropietario.seekg(0);
        temporal.seekp(0);
        while(!archivoPropietario.eof()){
            if(archivoPropietario.eof()){
                break;
            }
            //tam=sizeof(unsigned int);
            archivoPropietario.read(reinterpret_cast<char*>(&tamId), sizeof(tamId) );
            archivoPropietario.read(reinterpret_cast<char*>(&id), tamId );
            c.setId(id);


            archivoPropietario.read(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha) );
            archivoPropietario.read(reinterpret_cast<char*>(&fecha), tamFecha );
            c.setFecha(fecha);

            archivoPropietario.read(reinterpret_cast<char*>(&tamHora), sizeof(tamHora) );
            archivoPropietario.read(reinterpret_cast<char*>(&hora), tamHora );
            c.setHora(hora);

            archivoPropietario.read(reinterpret_cast<char*>(&tamRemi), sizeof(tamRemi) );
            archivoPropietario.read(reinterpret_cast<char*>(&remitente), tamRemi );
            c.setRemitente(remitente);

            archivoPropietario.read(reinterpret_cast<char*>(&tamDest), sizeof(tamDest) );
            archivoPropietario.read(reinterpret_cast<char*>(&destinatario), tamDest );
            c.setDestinatario(destinatario);

            archivoPropietario.read(reinterpret_cast<char*>(&tamCC), sizeof(tamCC) );
            archivoPropietario.read(reinterpret_cast<char*>(&copiaC), tamCC );
            c.setCc(copiaC);

            archivoPropietario.read(reinterpret_cast<char*>(&tamCCC), sizeof(tamCCC) );
            archivoPropietario.read(reinterpret_cast<char*>(&copiaCC), tamCCC );
            c.setBcc(copiaCC);

            archivoPropietario.read(reinterpret_cast<char*>(&tamAsu), sizeof(tamAsu) );
            archivoPropietario.read(reinterpret_cast<char*>(&asunto), tamAsu );
            c.setAsunto(asunto);

            archivoPropietario.read(reinterpret_cast<char*>(&tamCont), sizeof(tamCont) );
            archivoPropietario.read(reinterpret_cast<char*>(&contenido), tamCont );
            c.setContenido(contenido);


            if(id==identificadorBuscado){
                flag=true;
                //cout<<id<<endl<<tamFecha<<endl<<tamHora<<endl<<tamRemi<<endl<<tamDest<<endl<<tamCC<<endl<<tamCCC<<endl<<tamAsu<<endl<<tamCont;
                menuModificarPROPIETARIO(c,id,remitente,destinatario,copiaC,copiaCC,asunto,contenido,
                                         tamId,tamRemi,tamDest,tamCC,tamCCC,tamAsu,tamCont);
                //cout<<"Modificacion realizada con exito"<<endl;
            }
            temporal.write(reinterpret_cast<char*>(&tamId), sizeof(tamId) );
            temporal.write(reinterpret_cast<char*>(&id), tamId);

            temporal.write(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha) );
            temporal.write(reinterpret_cast<char*>(&fecha), tamFecha );

            temporal.write(reinterpret_cast<char*>(&tamHora), sizeof(tamHora) );
            temporal.write(reinterpret_cast<char*>(&hora), tamHora);

            temporal.write(reinterpret_cast<char*>(&tamRemi), sizeof(tamRemi) );
            temporal.write(reinterpret_cast<char*>(&remitente), tamRemi );

            temporal.write(reinterpret_cast<char*>(&tamDest), sizeof(tamDest) );
            temporal.write(reinterpret_cast<char*>(&destinatario), tamDest);

            temporal.write(reinterpret_cast<char*>(&tamCC), sizeof(tamCC) );
            temporal.write(reinterpret_cast<char*>(&copiaC), tamCC );

            temporal.write(reinterpret_cast<char*>(&tamCCC), sizeof(tamCCC) );
            temporal.write(reinterpret_cast<char*>(&copiaCC), tamCCC);

            temporal.write(reinterpret_cast<char*>(&tamAsu), sizeof(tamAsu) );
            temporal.write(reinterpret_cast<char*>(&asunto), tamAsu );

            temporal.write(reinterpret_cast<char*>(&tamCont), sizeof(tamCont) );
            temporal.write(reinterpret_cast<char*>(&contenido), tamCont );

        }
        if(flag==false){
            cout<<"El dato no se ha encontrado."<<endl;
        }else if(flag==true){
            cout<<"Modificacion exitosa."<<endl;
        }

    }
    archivoPropietario.close();
    temporal.close();
    remove("CopiaSeguridadPROPIETARIO.dat");
    rename("temporal.dat","CopiaSeguridadPROPIETARIO.dat");



}

void Propietario::Eliminar(unsigned int identificadorBuscado)
{
    Correo c;
    ifstream archivoPropietario;
    archivoPropietario.open("CopiaSeguridadPROPIETARIO.dat",ios::binary |ios::in);

    ofstream temporal;
    temporal.open("temporal.dat",ios::binary |ios::out);

    bool flag=false;
    int tamId, tamFecha, tamHora, tamRemi, tamDest, tamCC, tamCCC, tamAsu, tamCont;
    unsigned int id;
    char fecha[E], hora[E], remitente[E], destinatario[E], copiaC[E], copiaCC[E], asunto[E], contenido[M];

    //puntero a donde queremos mandar el dato, el tamano en bytes del dato que vamos a leer,
    //la cantidad de datos a leer multiplicada por el tamanio de cada dato


    if(!archivoPropietario.is_open() or !temporal.is_open()){
        cout<<"No se pudieron abrir los archivos."<<endl;
        archivoPropietario.close();
        temporal.close();
    }else{
        archivoPropietario.seekg(0);
        temporal.seekp(0);
        while(!archivoPropietario.eof()){
            if(archivoPropietario.eof()){
                break;
            }
            //tam=sizeof(unsigned int);
            archivoPropietario.read(reinterpret_cast<char*>(&tamId), sizeof(tamId) );
            archivoPropietario.read(reinterpret_cast<char*>(&id), tamId );
            c.setId(id);


            archivoPropietario.read(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha) );
            archivoPropietario.read(reinterpret_cast<char*>(&fecha), tamFecha );
            c.setFecha(fecha);

            archivoPropietario.read(reinterpret_cast<char*>(&tamHora), sizeof(tamHora) );
            archivoPropietario.read(reinterpret_cast<char*>(&hora), tamHora );
            c.setHora(hora);

            archivoPropietario.read(reinterpret_cast<char*>(&tamRemi), sizeof(tamRemi) );
            archivoPropietario.read(reinterpret_cast<char*>(&remitente), tamRemi );
            c.setRemitente(remitente);

            archivoPropietario.read(reinterpret_cast<char*>(&tamDest), sizeof(tamDest) );
            archivoPropietario.read(reinterpret_cast<char*>(&destinatario), tamDest );
            c.setDestinatario(destinatario);

            archivoPropietario.read(reinterpret_cast<char*>(&tamCC), sizeof(tamCC) );
            archivoPropietario.read(reinterpret_cast<char*>(&copiaC), tamCC );
            c.setCc(copiaC);

            archivoPropietario.read(reinterpret_cast<char*>(&tamCCC), sizeof(tamCCC) );
            archivoPropietario.read(reinterpret_cast<char*>(&copiaCC), tamCCC );
            c.setBcc(copiaCC);

            archivoPropietario.read(reinterpret_cast<char*>(&tamAsu), sizeof(tamAsu) );
            archivoPropietario.read(reinterpret_cast<char*>(&asunto), tamAsu );
            c.setAsunto(asunto);

            archivoPropietario.read(reinterpret_cast<char*>(&tamCont), sizeof(tamCont) );
            archivoPropietario.read(reinterpret_cast<char*>(&contenido), tamCont );
            c.setContenido(contenido);

            //cout<<id<<endl<<asunto<<endl;

            if(id==identificadorBuscado){
                flag=true;
                cout<<"Eliminacion exitosa."<<endl;
            }else{
                temporal.write(reinterpret_cast<char*>(&tamId), sizeof(tamId) );
                temporal.write(reinterpret_cast<char*>(&id), tamId);

                temporal.write(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha) );
                temporal.write(reinterpret_cast<char*>(&fecha), tamFecha );

                temporal.write(reinterpret_cast<char*>(&tamHora), sizeof(tamHora) );
                temporal.write(reinterpret_cast<char*>(&hora), tamHora);

                temporal.write(reinterpret_cast<char*>(&tamRemi), sizeof(tamRemi) );
                temporal.write(reinterpret_cast<char*>(&remitente), tamRemi );

                temporal.write(reinterpret_cast<char*>(&tamDest), sizeof(tamDest) );
                temporal.write(reinterpret_cast<char*>(&destinatario), tamDest);

                temporal.write(reinterpret_cast<char*>(&tamCC), sizeof(tamCC) );
                temporal.write(reinterpret_cast<char*>(&copiaC), tamCC );

                temporal.write(reinterpret_cast<char*>(&tamCCC), sizeof(tamCCC) );
                temporal.write(reinterpret_cast<char*>(&copiaCC), tamCCC);

                temporal.write(reinterpret_cast<char*>(&tamAsu), sizeof(tamAsu) );
                temporal.write(reinterpret_cast<char*>(&asunto), tamAsu );

                temporal.write(reinterpret_cast<char*>(&tamCont), sizeof(tamCont) );
                temporal.write(reinterpret_cast<char*>(&contenido), tamCont );
            }


        }
        if(flag==false){
            cout<<"El dato no se ha encontrado."<<endl;
        }

    }
    archivoPropietario.close();
    temporal.close();
    remove("CopiaSeguridadPROPIETARIO.dat");
    rename("temporal.dat","CopiaSeguridadPROPIETARIO.dat");

}
void Propietario::Exportar(){
    Correo c;
    fstream readWriteFile;
    fstream archivoPropietario;
    readWriteFile.open( "bandeja.bin", ios::in | ios::binary);
    archivoPropietario.open("CopiaSeguridadPROPIETARIO.dat",ios::out| ios::binary);
     if( !readWriteFile.is_open() or !archivoPropietario.is_open()){
        cout<<"No se pudieron abrir los archivos. "<<endl;
        readWriteFile.close();
        archivoPropietario.close();
      }else{
        readWriteFile.seekg(0);
    unsigned int id=0;
    int tam=0;

    char fecha[E], hora[E], remitente[E], destinatario[E], copiaC[E], copiaCC[E], asunto[E], contenido[M];

        //readWriteFile.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreoE()) );
        while(!readWriteFile.eof()){
            if(readWriteFile.eof()){
                break;
            }
            readWriteFile.read(reinterpret_cast<char*>(&c), sizeof(c.getCorreo()) );
            if(c.getId()!=0){
                //tam es la longitud de cada campo. Excepto en el del id, porque este es entero y me da los bytes maximos que necesita cualquier int

                tam=sizeof(unsigned int);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                id=c.getId();
                archivoPropietario.write(reinterpret_cast<char*>(&id), tam );

                strcpy(fecha,c.getFecha().c_str());
                tam=strlen(fecha);  //size of =24, .size()=8 y es el correcto
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(fecha,c.getFechaEnvio().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&fecha), tam );
                //cout<<fecha<<"      ";


                strcpy(hora,c.getHora().c_str());
                tam=strlen(hora);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(hora,c.getHoraEnvio().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&hora), tam );
                //cout<<hora<<endl;


                strcpy(remitente,c.getRemitente().c_str());
                tam=strlen(remitente);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(remitente,c.getRemitente().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&remitente), tam );

                strcpy(destinatario,c.getDestinatario().c_str());
                tam=strlen(destinatario);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(destinatario,c.getDestinatario().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&destinatario), tam );


                strcpy(copiaC,c.getCc().c_str());
                tam=strlen(copiaC);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(copiaC,c.getCopiaCarbon().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&copiaC), tam );


                strcpy(copiaCC,c.getBcc().c_str());
                tam=strlen(copiaCC);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(copiaCC,c.getCopiaCarbonCiega().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&copiaCC), tam );


                strcpy(asunto,c.getAsunto().c_str());
                tam=strlen(asunto);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(asunto,c.getAsunto().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&asunto), tam );


                strcpy(contenido,c.getContenido().c_str());
                tam=strlen(contenido);
                archivoPropietario.write(reinterpret_cast<char*>(&tam), sizeof(tam) );
                //strcpy(contenido,c.getContenido().c_str());
                archivoPropietario.write(reinterpret_cast<char*>(&contenido), tam );
            }


        }
            readWriteFile.close();

     }
}



void Propietario:: menuModificarPROPIETARIO(Correo& cor,const unsigned int identificador,char*remitente,
                                                   char*destinatario, char* copiaC,char*copiaCC,char*asunto,char*contenido,
                                                   int& tamId,int& tamRemi,int&tamDest,
                                                   int&tamCC,int&tamCCC,int&tamAsu,int&tamCont){
    char myChar[E], myCharContenido[M];

    string op;
    cout << endl << endl;
    cout << "Identificador: "<<cor.getId()<< endl;
    cout << "Fecha: "<< cor.getFecha() << endl;
    cout << "Hora: " << cor.getHora()<< endl;
    cout << "Remitente: "<< cor.getRemitente() << endl;
    cout << "Destinatario: " << cor.getDestinatario() <<endl;
    cout << "Copia Carbon: " << cor.getCc() << endl;
    cout << "Copia Carbon Copia: " << cor.getBcc() << endl;
    cout << "Asunto: " << cor.getAsunto()<< endl;
    cout << "Contenido: " << cor.getContenido() << endl;
    cout << endl;
    while(true){
        cin.ignore();
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
            cin.getline(myChar,E);
            cor.setRemitente(myChar);
            strcpy(remitente,myChar);
            tamRemi=strlen(remitente);
        }
        else if(op == "2"){
            cout<<"Nuevo Destinatario: ";
            cin.getline(myChar,E);
            cor.setDestinatario(myChar);
            strcpy(destinatario,myChar);
            tamDest=strlen(destinatario);
        }
        else if(op == "3"){
            cout<<"Nueva Copia Carbon: ";
            cin.getline(myChar,E);
            cor.setCc(myChar);
            strcpy(copiaC,myChar);
            tamCC=strlen(copiaC);
        }
        else if(op == "4"){
            cout<<"Nueva Copia Carbon Ciega: ";
            cin.getline(myChar,E);
            cor.setBcc(myChar);
            strcpy(copiaCC,myChar);
            tamCCC=strlen(copiaCC);
        }
        else if(op == "5"){
            cout<<"Nuevo Asunto: ";
            cin.getline(myChar,E);
            cor.setAsunto(myChar);
            strcpy(asunto,myChar);
            tamAsu=strlen(asunto);
        }
        else if(op == "6"){
            cout<<"Nuevo Contenido: ";
            cin.getline(myCharContenido,M,'|');
            cor.setContenido(myCharContenido);
            strcpy(contenido,myChar);
            tamCont=strlen(contenido);
        }
        else if(op == "7"){
            break;
        }else{
            cout<<"Opcion incorrecta"<<endl;
        }
    }
}

