#include "correo.h"
#include "arbolbinario.h"
#include "indiceprimario.h"

Correo::Correo()
{

}

ostream &operator <<(ostream &escribe, const Correo &c)
{
    escribe << "Identificador: " <<  c.getId() << endl
            << "Fecha: " << c.getFecha() << endl
            << "Hora: " << c.getHora() << endl
            << "Remitente: " << c.getRemitente() << endl
            << "Destinatario: " << c.getDestinatario() << endl
            << "Copia Carbon: " << c.getCc() << endl
            << "Copia Carbon Ciega: " << c.getBcc() << endl
            << "Asunto: " << c.getAsunto() << endl
            << "Contenido:" << endl << c.getContenido() << endl << endl;
    return escribe;
}

unsigned int Correo::getId() const
{
    return email.id;
}

void Correo::setId(unsigned int value)
{
    email.id = value;
}

void Correo::setRemitente(const string &value)
{
    strcpy(email.remitente,value.c_str());
}

string Correo::getRemitente() const
{
    return email.remitente;
}

string Correo::getFecha() const
{
    return email.fecha;
}

void Correo::setFecha(const string &value)
{
    strcpy(email.fecha,value.c_str());
}

string Correo::getHora() const
{
    return email.hora;
}

void Correo::setHora(const string &value)
{
    strcpy(email.hora,value.c_str());
}

void Correo::setDestinatario(const string &value)
{
    strcpy(email.destinatario,value.c_str());
}

string Correo::getDestinatario() const
{
    return email.destinatario;
}

void Correo::setCc(const string &value)
{
    strcpy(email.cc,value.c_str());
}

string Correo::getCc() const
{
    return email.cc;
}

void Correo::setBcc(const string &value)
{
    strcpy(email.bcc,value.c_str());
}

string Correo::getBcc() const
{
    return email.bcc;
}

void Correo::setAsunto(const string &value)
{
    strcpy(email.asunto,value.c_str());
}

string Correo::getAsunto() const
{
    return email.asunto;
}

void Correo::setContenido(const string &value)
{
    strcpy(email.contenido,value.c_str());
}

string Correo::getContenido() const
{
    return email.contenido;
}

Correo:: Correos Correo :: getCorreo() const
{
    return email;
}




void Correo::Escribir()
{
    indicePrimario unIndice;
    ArbolBinario <indicePrimario> myTree;
    unsigned long ref;
    string llave;

    fstream readWriteFile;
    int distBytes=0;
    char myCharE[E], myCharM [M];
    readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );//crear archivo binario

    if( !readWriteFile.is_open() )
    {
        cout << "Error al abrir el archivo..." << endl;
        readWriteFile.open("bandeja.bin", ios::out);

        if(!readWriteFile.good() ){
            cout << "Error al crear el archivo" << endl;
        }
        else
        {
            cout<<"Archivo creado"<<endl;
            readWriteFile.close();
        }
    }
    else
    {
        bool band=false;
        do{
            cout<<"Ingrese Identificador: ";
            cin>>ident;
            readWriteFile.close();
            if(validarID(ident)){
                cout<<"id ocupado ingrese uno valido"<<endl;
            }
            else{
                band=true;
            }
        }while(band ==false);
        readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );//crear archivo binario

        //setId(ident);
        setId(ident);

        /*time_t tAct = time(NULL);
        string f=asctime(localtime(&tAct));
        setFecha(f);
        cout << "Fecha: "<<getFecha();*/

        char fecha_hora[15];//fecha y hora del sistema
        time_t date = time(nullptr);
        struct tm *th= localtime(&date);
        strftime(fecha_hora,128,"%d/%m/%y",th);//strftime devuelve la fecha de la computadora
        setFecha(fecha_hora);
        strftime(fecha_hora,128,"%H:%M:%S",th);//strftime devuelve la hora de la computadora
        setHora(fecha_hora);//copia la hora

        cin.ignore();
        cout<<"Remitente: ";
        cin.getline(myCharE,E);
        setRemitente(myCharE);
        cout<<"Destinatario: ";
        cin.getline(myCharE,E);
        setDestinatario(myCharE);
        cout<<"Copia Carbon: ";
        cin.getline(myCharE,E);
        setCc(myCharE);
        cout<<"Copia Carbon Ciega: ";
        cin.getline(myCharE,E);
        setBcc(myCharE);
        cout<<"Asunto: ";
        cin.getline(myCharE,E);
        setAsunto(myCharE);
        cout<<"Contenido(terminar del mensaje '|'): "<<endl;
        cin.getline(myCharM,M,'|');
        setContenido(myCharM);

        distBytes = ((getId() - 1) * sizeof (struct Correos));//buscar por nrr
        readWriteFile.seekp(distBytes);//localizar archivo de escritura
        readWriteFile.write((char*)&email, sizeof (struct Correos));//escribir en el archivo
        readWriteFile.close();//cerrar archivo

        //El archivo de indices se desactualiza
        unIndice.Desactualizar();

        //Lo escribo en el arbol
        ref = distBytes;
        llave = to_string( ident );

        unIndice.setLlave(llave);
        unIndice.setReferencia( ref );

        myTree.insertar(myTree.getRaiz(), unIndice);
    }//fin else
}

bool Correo::validarID(const unsigned int &ident)
{
    fstream readWriteFile;
    bool b=false;
    readWriteFile.open( "bandeja.bin", ios::in | ios::binary |ios::out);

    // Mover el apuntador de escritura al final del archivo para demostrar la
    // persistencia de datos y la capacidad de mover los apuntadores de archivo
    distBytes= (ident-1)*sizeof (Correos);
    readWriteFile.seekg(distBytes, ios::beg);
    readWriteFile.read((char*)&email, sizeof (struct Correos));
    if(ident==getId())
        b=true;


    readWriteFile.close();
    return b;
}

void Correo::Leer_AD(unsigned int ident)
{
    fstream readWriteFile;
    int distBytes=0;
    readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );//crear archivo binario


    if( !readWriteFile.is_open() )
    {
        cout << "Error al abrir el archivo..." << endl;
        readWriteFile.open("bandeja.bin", ios::out);

        if(!readWriteFile.good() ){
            cout << "Error al crear el archivo" << endl;
        }
        else
        {
            cout<<"Archivo creado"<<endl;
            readWriteFile.close();
        }
    }
    else
    {
        distBytes=(ident-1) * sizeof (Correos);
        readWriteFile.seekg(distBytes, ios::beg);
        readWriteFile.read((char *) &email, sizeof(Correos));

        if(getId()!=0){
            cout<<endl<<"Identificador: "<<getId()<<endl;
            cout<<endl<<"Fecha: "<<getFecha()<<endl;
            cout<<"Hora: "<<getHora()<<endl;
            cout<<"Remitente: "<<getRemitente()<<endl;
            cout<<"Destinatario: "<<getDestinatario()<<endl;
            cout<<"CC: "<<getCc()<<endl;
            cout<<"BCC: "<<getBcc()<<endl;
            cout<<"Asunto: "<<getAsunto()<<endl;
            cout<<"Contenido: "<<getContenido()<<endl;
        }else{
            cout<<"El dato no se encuentra..."<<endl;
        }



    }
    readWriteFile.close();
}

void Correo::Modificar_AD()
{
    fstream readWriteFile;
    int op;
    unsigned int ident;
    char myCharE[E], myCharM[M];
    cout<<"Identificador: ";
    cin>>ident; cout<<endl;

    int distBytes=0;
    readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );//abrir archivo binario


    if( !readWriteFile.is_open() )
    {
        cout << "Error al abrir el archivo..." << endl;
        readWriteFile.open("bandeja.bin", ios::out);

        if(!readWriteFile.good() ){
            cout << "Error al crear el archivo" << endl;
        }
        else
        {
            cout<<"Archivo creado"<<endl;
            readWriteFile.close();
        }
    }
    else
    {
        distBytes=(ident-1) * sizeof (Correos);
        readWriteFile.seekg(distBytes, ios::beg);
        readWriteFile.read((char *) &email, sizeof(Correos));
        if(getId()!=0){
            cout<<"1) Remitente: "<<getRemitente()<<endl;
            cout<<"2) Destinatario: "<<getDestinatario()<<endl;
            cout<<"3) CC: "<<getCc()<<endl;
            cout<<"5) BCC: "<<getBcc()<<endl;
            cout<<"5) Asunto: "<<getAsunto()<<endl;
            cout<<"6) Contenido: "<<getContenido()<<endl;
            cout<<endl<<"----¿Que desea modificar?----"<<endl;
            cin>>op; cin.ignore();
            switch (op){
            case 1:

                cout<<"Nuevo Remitente: ";
                cin.getline(myCharE,E);
                setRemitente(myCharE);
                break;

            case 2:
                cout<<"Nuevo Destinatario: ";
                cin.getline(myCharE,E);
                setDestinatario(myCharE);
                break;

            case 3:
                cout<<"Nueva Copia Carbon: ";
                cin.getline(myCharE,E);
                setCc(myCharE);

                break;

            case 4:
                cout<<"Nueva Copia Carbon Ciega: ";
                cin.getline(myCharE,E);
                setBcc(myCharE);

                break;

            case 5:
                cout<<"Nuevo Asunto: ";
                cin.getline(myCharE,E);
                setAsunto(myCharE);

                break;

            case 6:
                cout<<"Nuevo Contenido(terminar del mensaje '|'): "<<endl;
                cin.getline(myCharM,M,'|');
                setAsunto(myCharM);
                break;

            case 7:
                break;
            default:
                cout<<"Opcion no valida"<<endl;
                break;
            }
            distBytes = ((getId() - 1) * sizeof (struct Correos));//buscar por nrr
            readWriteFile.seekp(distBytes);//localizar archivo de escritura
            readWriteFile.write((char*)&email, sizeof (struct Correos));//escribir en el archivo
            readWriteFile.close();
        }else{
            cout<<"Correo no encontrado..."<<endl;
        }
    }

}

void Correo::Leer_Sec()
{
    fstream readWriteFile;
    string sender;
    bool b=false;


    cout << " Remitente: ";
    cin >> sender;
    cout << endl;

    readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );// Abrir el archivo

    if( !readWriteFile.is_open() ) {
        cout << " Creando archivo" << endl;

        readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );// Verificar si existe el archivo

        if( !readWriteFile.good() ) {
            cout << " Error al crear el archivo" << endl;
        }
        else {
            readWriteFile.close();
        }
    }
    else {
        while(!readWriteFile.eof() && b == false) {
            readWriteFile.read((char*)&email,sizeof(Correos));
            if(getId()!=0){
                if(getRemitente() == sender) {

                    cout<<endl<<"Identificador: "<<getId()<<endl;
                    cout << " Fecha: " << getFecha()<< endl;
                    cout << " Hora: " << getHora()<< endl;
                    cout << " Remitente: " << getRemitente() << endl;
                    cout << " Destinatario: " << getDestinatario() << endl;
                    cout << " CC: " << getCc() << endl;
                    cout << " BCC: " << getBcc() << endl;
                    cout << " Asunto: " << getAsunto() << endl;
                    cout << " Contenido: " << getContenido() << endl << endl;
                    b=true;
                }
            }

        }
        if(b==false){
            cout<<"El dato no se encuentra..."<<endl;
        }
    }

    readWriteFile.close();
}

void Correo::Modificar_Sec()
{
    fstream readWriteFile;
    string sender;
    bool b=false;
    int op;
    char myCharM[M], myCharE[E];

    cout << " Remitente: ";
    cin >> sender;
    cout << endl;

    readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );// Abrir el archivo

    if( !readWriteFile.is_open() ) {
        cout << " Creando archivo" << endl;

        readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );// Verificar si existe el archivo

        if( !readWriteFile.good() ) {
            cout << " Error al crear el archivo" << endl;
        }
        else {
            readWriteFile.close();
        }
    }
    else {
        while(!readWriteFile.eof() && b == false) {
            readWriteFile.read((char*)&email,sizeof(Correos));
            if(getId()!=0){
                if(getRemitente() == sender) {
                    b=true;
                    cout<<"1) Remitente: "<<getRemitente()<<endl;
                    cout<<"2) Destinatario: "<<getDestinatario()<<endl;
                    cout<<"3) CC: "<<getCc()<<endl;
                    cout<<"5) BCC: "<<getBcc()<<endl;
                    cout<<"5) Asunto: "<<getAsunto()<<endl;
                    cout<<"6) Contenido: "<<getContenido()<<endl;

                    cout<<endl<<"----¿Que desea modificar?----"<<endl;
                    cin>>op; cin.ignore();
                    switch (op){
                    case 1:

                        cout<<"Nuevo Remitente: ";
                        cin.getline(myCharE,E);
                        setRemitente(myCharE);
                        break;

                    case 2:
                        cout<<"Nuevo Destinatario: ";
                        cin.getline(myCharE,E);
                        setDestinatario(myCharE);
                        break;

                    case 3:
                        cout<<"Nueva Copia Carbon: ";
                        cin.getline(myCharE,E);
                        setCc(myCharE);

                        break;

                    case 4:
                        cout<<"Nueva Copia Carbon Ciega: ";
                        cin.getline(myCharE,E);
                        setBcc(myCharE);

                        break;

                    case 5:
                        cout<<"Nuevo Asunto: ";
                        cin.getline(myCharE,E);
                        setAsunto(myCharE);

                        break;

                    case 6:
                        cout<<"Nuevo Contenido(terminar del mensaje '|'): "<<endl;
                        cin.getline(myCharM,M,'|');
                        setAsunto(myCharM);
                        break;

                    case 7:
                        break;
                    default:
                        cout<<"Opcion no valida"<<endl;
                        break;
                    }
                    distBytes = ((getId() - 1) * sizeof (struct Correos));//buscar por nrr
                    readWriteFile.seekp(distBytes);//localizar archivo de escritura
                    readWriteFile.write((char*)&email, sizeof (struct Correos));//escribir en el archivo
                }
            }

        }
        if(b==false){
            cout<<"Correo no encontrado..."<<endl;
        }

    }

    readWriteFile.close();

}

void Correo::Eliminar_Id(unsigned int ident)
{

    fstream readWriteFile;
    indicePrimario unIndice;
    ArbolBinario <indicePrimario> myTree;
    unsigned long ref;
    string llave;

    int distBytes=0;
    readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );//abrir archivo binario


    if( !readWriteFile.is_open() )
    {
        cout << "Error al abrir el archivo..." << endl;
        readWriteFile.open("bandeja.bin", ios::out);

        if(!readWriteFile.good() ){
            cout << "Error al crear el archivo" << endl;
        }
        else
        {
            cout<<"Archivo creado"<<endl;
            readWriteFile.close();
        }
    }
    else{
        distBytes=(ident-1) * sizeof (Correos);
        readWriteFile.seekg(distBytes, ios::beg);
        readWriteFile.read((char *) &email, sizeof(Correos));

        if(getId()!=0){
            string myString = " ";
            setRemitente(myString);
            setFecha(myString);
            setHora(myString);
            setDestinatario(myString);
            setCc(myString);
            setBcc(myString);
            setAsunto(myString);
            setContenido(myString);

            distBytes = ((getId() - 1) * sizeof (struct Correos));//buscar por nrr
            setId(NULL);
            readWriteFile.seekp(distBytes);//localizar archivo de escritura
            readWriteFile.write((char*)&email, sizeof (struct Correos));//escribir en el archivo

            //El archivo de indices se desactualiza
            unIndice.Desactualizar();

            //Lo elimino en el arbol
            ref = distBytes;
            llave = to_string( ident );

            unIndice.setLlave(llave);
            unIndice.setReferencia( ref );

            myTree.eliminar(myTree.getRaiz(),unIndice);

            cout<<"Correo eliminado correctamente."<<endl;
        }else{
            cout<<"Ese correo no existe."<<endl;
        }
    }



    readWriteFile.close();
}

void Correo::Eliminar_Sec()
{
    string sender;
    bool b=false;
    fstream readWriteFile;

    cout << " Remitente: ";
    cin >> sender;
    cout << endl;

    readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );// Abrir el archivo

    if( !readWriteFile.is_open() ) {
        cout << " Creando archivo" << endl;

        readWriteFile.open( "bandeja.bin", ios::in | ios::out | ios::binary );// Verificar si existe el archivo

        if( !readWriteFile.good() ) {
            cout << " Error al crear el archivo" << endl;
        }
        else {
            readWriteFile.close();
        }
    }
    else {
        while(!readWriteFile.eof() && b == false) {
            readWriteFile.read((char*)&email,sizeof(Correos));
            if(getId()!=0){
                if(getRemitente() == sender) {
                    b=true;
                    cout<<endl<<"Identificador: "<<getId()<<endl;
                    cout<<"Remitente: "<<getRemitente()<<endl;
                    cout<<"Destinatario: "<<getDestinatario()<<endl;
                    cout<<"CC: "<<getCc()<<endl;
                    cout<<"BCC: "<<getBcc()<<endl;
                    cout<<"Asunto: "<<getAsunto()<<endl;
                    cout<<"Contenido: "<<getContenido()<<endl;


                    distBytes = ((getId() - 1) * sizeof (struct Correos));//buscar por nrr
                    setId(NULL);//
                    readWriteFile.seekp(distBytes);//localizar archivo de escritura
                    readWriteFile.write((char*)&email, sizeof (struct Correos));//escribir en el archivo

                    cout<<"Correo eliminado correctamente."<<endl;

                }
            }

        }
        if(b==false){
            cout<<"El correo no existe."<<endl;
        }



    }

    readWriteFile.close();
}

