#include "busquedas_eficientes.h"

Busquedas_eficientes::Busquedas_eficientes()
{

}

Busquedas_eficientes::~Busquedas_eficientes()
{
    delete [] emails;
}

void Busquedas_eficientes::shellsort()
{
    LlenarArreglo();
    size_t i,division=MAX;
    Correo aux;
    bool bandera;
    while(division>1){
        division=division/2;
        bandera=true;
        while (bandera==true){
            bandera=false;
            i=0;
            while(i+division<=M-1){
                if(emails[i].getRemitente()>emails[i+division].getRemitente()){
                    aux=emails[i];
                    emails[i]=emails[i+division];
                    emails[i+division]=aux;
                    bandera=true;
                }
                i++;
            }
         }
    }
}

void Busquedas_eficientes::imprimirCorreo(Correo a[], int pos)
{
    cout << endl << endl;
    cout << "Identificador: "<<a[pos].getId()<< endl;
    cout << "Fecha: "<< a[pos].getFecha() << endl;
    cout << "Hora: " << a[pos].getHora()<< endl;
    cout << "Remitente: "<< a[pos].getRemitente() << endl;
    cout << "Destinatario: " << a[pos].getDestinatario() <<endl;
    cout << "Copia Carbon: " << a[pos].getBcc() << endl;
    cout << "Copia Carbon Copia: " << a[pos].getCc() << endl;
    cout << "Asunto: " << a[pos].getAsunto()<< endl;
    cout << "Contenido: " << a[pos].getContenido() << endl;
    cout << endl;
}

void Busquedas_eficientes::LlenarArreglo()
{
    Correo c;
    ifstream readWriteFile;
    int i=0;
    readWriteFile.open("bandeja.bin", ios::in | ios::binary);  //in->lectura
    if(!readWriteFile.is_open()){
        cout << "Su archivo no ha sido creado..." << endl;
        readWriteFile.close();
    }else{
        readWriteFile.seekg(0);
        while(!readWriteFile.eof() && i<=MAX){
            if(readWriteFile.eof()){
                //last=i;
                break;
            }
            readWriteFile.read((char*) &c, sizeof (c.getCorreo()));
            if(c.getId()!=0){
                emails[i++] = c;
            }
        }
    }
}

void Busquedas_eficientes::BinarySearch(const string &rem)
{
    shellsort();

    int i(0);
    int j(MAX);
    int m;
    bool flag(0);

    while(i <= j) {
        m = (i + j) / 2;
        if(emails[m].getRemitente() == rem) {
            flag=1;
            imprimirCorreo(emails, m);
            break;

        }
        if(rem <= emails[m].getRemitente()) {
            j = m - 1;
        }
        else {
            i = m + 1;
        }
    }
    if(flag==0){
        cout<<"Ese remitente no fue encontrado."<<endl;
    }

}
