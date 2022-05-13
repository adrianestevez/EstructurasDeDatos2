#include "menu.h"
#include "copia_seguridad.h"
#include "propietario.h"
#include "busquedas_eficientes.h"
#include "indiceprimario.h"
#include "indicesrem.h"
#include "indicesdest.h"
#include "indiceS.h"
#include "indicepaginado.h"
#include "dispersion.h"
#include "cifrado.h"
#include "compresion.h"

Menu::Menu()
{

}

void Menu::Mostrar_Menu()
{
    Correo c;
    int op;

    indicePrimario ip;

    ip.funcionAdmin();


    do{
        system("cls");

        cout <<"1. Escribir correo "<<endl;
        cout <<"2. Leer Correo" <<endl;
        cout <<"3. Modificar correo"<<endl;
        cout <<"4. Eliminar Correo"<<endl;
        cout <<"5. Copia de Seguridad"<<endl;
        cout <<"6. Formato Propietario"<<endl;
        cout <<"7. Busquedas Eficientes"<<endl;
        cout <<"8. Comprimir"<<endl;
        cout <<"9. Cifrado"<<endl;
        cout <<"0. Salir "<<endl;
        cout <<"Elige tu opcion: "; cin>>op; cin.ignore();
        cout<<endl<<endl;


        if(op==1){
            c.Escribir();
            system("pause");
        }

        else if (op==2) {
            Menu_Leer();
            system("pause");
        }

        else if (op==3) {
            Menu_Modificar();
            system("pause");
        }

        else if (op==4) {
            Menu_Eliminar();
            system("pause");
        }

        else if (op==5) {
            Menu_Copia_Seguridad();
            system("pause");
        }

        else if (op==6) {
            Menu_Formato_Propietario();
            system("pause");
        }

        else if (op==7) {
            Menu_Busquedas_Eficiente();
            system("pause");
        }

        else if (op==8) {
            Compresion comp;
            comp.comprimir();
            system("pause");
        }

        else if (op==9) {
            Cifrado cif;
            cif.menuCifrado();
            system("pause");
        }

        else if(op==0){
            indicePrimario ip;
            if(!ip.Actualizado()){
                ip.ActualizarArchivo();
                cout<<"No esta actualizado";
            }else{
                cout<<"Si esta actualizado";
            }
        }
    }while(op!=0);
}

void Menu::Menu_Eliminar()
{
    int opc;
    Correo c;

    system("cls");
    cout<<"-----Menu Eliminar-------"<<endl<<endl;
    cout<<"1) Eliminar por Id"<<endl;
    cout<<"2) Eliminar por Remitente"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opc; cout<<endl;

    switch (opc) {
    case 1:
        unsigned int ident;
        cout<<"Identificador: ";
        cin>>ident; cout<<endl;
        c.Eliminar_Id(ident);
        break;
    case 2:
        c.Eliminar_Sec();
        break;
    default:
        cout<<"Ingrese una opcion valida";
    }
}

void Menu::Menu_Modificar()
{

    int opc;
    Correo c;

    system("cls");
    cout<<"-----Menu Modificar-------"<<endl<<endl;
    cout<<"1) Modificar por Id"<<endl;
    cout<<"2) Modificar por Remitente"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opc; cout<<endl;

    switch (opc) {
    case 1:
        c.Modificar_AD();
        break;
    case 2:
        c.Modificar_Sec();
        break;
    default:
        cout<<"Ingrese una opcion valida";
    }
}

void Menu::Menu_Leer()
{
    int opc;
    Correo c;

    system("cls");
    cout<<"-----Menu Leer-------"<<endl<<endl;
    cout<<"1) Leer por Id"<<endl;
    cout<<"2) Leer por Remitente"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opc; cout<<endl;

    switch (opc) {
    case 1:
        unsigned int ident;
        cout<<"Identificador: ";
        cin>>ident;cout<<endl;
        c.Leer_AD(ident);
        break;
    case 2:
        c.Leer_Sec();
        break;
    default:
        cout<<"Ingrese una opcion valida";
    }
}

void Menu::Menu_Copia_Seguridad()
{
    Copia_Seguridad copia;
    Correo c;
    int index, opc;

    system("cls");
    cout<<"-----Menu Copia de Seguridad-------"<<endl<<endl;
    cout<<"1) Exportar"<<endl;
    cout<<"2) Importar"<<endl;
    cout<<"3) Modificar"<<endl;
    cout<<"4) Eliminar"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opc; cout<<endl;


    switch (opc) {
    case 1:
       copia.exportar(c);
        break;
    case 2:
        copia.importar();
        break;
    case 3:
        cout<<"Ingrese la posicion a modificar: ";
        cin>>index; cin.ignore();
        cout<<endl;
        copia.modificarCsv(index);
        break;
    case 4:
        cout<<"Ingrese la posicion a eliminar: ";
        cin>>index; cin.ignore();
        cout<<endl;
        copia.eliminarCsv(index);
        break;
    default:
        cout<<"Ingrese una opcion valida";
    }
}

void Menu::Menu_Formato_Propietario()
{
    Propietario p;
    int opc;
    unsigned int index;

    system("cls");
    cout<<"-----Menu Formato propietario-------"<<endl<<endl;
    cout<<"1) Exportar"<<endl;
    cout<<"2) Eliminar"<<endl;
    cout<<"3) Modificar"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opc; cout<<endl;

    Correo c;
    switch (opc) {
    case 1:
        p.Exportar();
        break;
    case 2:
        cout<<"Ingrese el id a eliminar: ";
        cin>>index;cout<<endl;
        p.Eliminar(index);
        break;
    case 3:
        cout<<"Ingrese el id a modificar: ";
        cin>>index;cout<<endl;
        p.Modificar(index);
        break;
    default:
        cout<<"Ingrese una opcion valida";
    }
}

void Menu::Menu_Busquedas_Eficiente()
{
    int opc;
    Busquedas_eficientes be;
    indicePrimario indicep;
    indiceSRem indiceS;
    indiceSDest indiceSdest;
    indicesecundario indSec;
    indicePaginado indicePag;


    system("cls");
    cout<<"-----Menu Busquedas Eficientes-------"<<endl<<endl;
    cout<<"1) Buscar por remitente"<<endl;
    cout<<"2) Buscar por indice primario"<<endl;
    cout<<"3) Buscar por indice remitente"<<endl;
    cout<<"4) Buscar por indice destinatario"<<endl;
    cout<<"5) Buscar Indice secundario AND"<<endl;
    cout<<"6) Buscar por Indice Secundario OR"<<endl;
    cout<<"7) Buscar en Indice Paginado"<<endl;
    cout<<"8) Menu Tabla de Dispersion"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opc; cout<<endl;

    Correo c;
    string s;
    switch (opc) {
    case 1:
        cin.ignore();
        cout<<"Ingrese el remitente: ";
        getline(cin,s);
        be.BinarySearch(s);
        break;
    case 2:
        indicep.BuscarId();
        break;
    case 3:
        indiceS.BuscarRem();
        break;
    case 4:
        indiceSdest.BuscarDest();
        break;
    case 5:
        indSec.AndAdmin();
        break;
    case 6:
        indSec.OrAdmin();
        break;
    case 7:
        indicePag.funcionAdmin();
        indicePag.buscarPorID();
        break;
    case 8:
        Menu_Tabla_Dispersion();
        break;
    default:
        cout<<"Ingrese una opcion valida";
    }
}

void Menu::Menu_Tabla_Dispersion()
{
    int opc;
    dispersion TablaDispersion;

    system("cls");
    cout<<"-----Menu Busquedas Eficientes-------"<<endl<<endl;
    cout<<"1) Buscar por remitente en Tabla"<<endl;
    cout<<"2)  Exportar Tabla de Dispersion"<<endl;
    cout<<"3)  Importar Tabla Dispersion(desde archivo de tabla)"<<endl;
    cout<<"Ingrese su opcion: ";
    cin>>opc; cout<<endl;

    Correo c;
    string s;
    switch (opc) {
    case 1:
        TablaDispersion.FuncionAdminBuscar();
        break;
    case 2:
        TablaDispersion.SerializarTabla();
        cout<<"Datos Exportados"<<endl;
        break;
    case 3:
        TablaDispersion.ImportarDesdeArchTabla();
        cout<<"Datos Importados"<<endl;
        break;
    }
}
