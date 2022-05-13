#include "cifrado.h"
#include <string.h>
#include <iostream>


Cifrado::Cifrado()
{

}

void Cifrado::menuCifrado()
{
    char unChar;
    cout << "# # # # # # # Cifrado # # # # # # #" << endl << endl;
    cout << "1. Cifrar." << endl;
    cout << "2. Descifrar." << endl;
    cout << "0. Regresar al menu principal." << endl;

    cout << "Ingrese opcion: ";
    cin >> unChar;
    cout << endl;

    switch(unChar){
    case '1':
        cifrar();
        break;

    case '2':
        descifrar();
        break;

    case '0': break; //Regresar al menu principal

    default: cout << "Ha ingresado un valor no valido." << endl << endl;
    }
}

void Cifrado::cifrar()
{
    ifstream archOrigen( "CopiaSeguridad.csv", ios::in );

    if( !archOrigen ) {
        cerr << "No se pudo abrir el archivo origen." << endl << endl;
    }
    else {
        ofstream archDestino( "ArchivoCifrado.CSV", ios::out );

        archOrigen.seekg(0);
        archDestino.seekp(0);

        char contrasena[500];

        cout << "Ingrese la contraseña: ";
        cin >> contrasena;

        //cout << "contrasena: " <<  contrasena << endl;

        // Se mete la contrasena al archivo destino
        char cc[500]; //contrasena cifrada
        int i = 0;

        while ( contrasena[i] != '\0' ) {
            cc[ i ] = contrasena[ i ] + 3;

            //cout << cc[i] << " = " << contrasena[i] << endl;
            i++;
        }

        cc[i] = '\0';

        archDestino << cc << '#';

        char unChar;

        // Mientras el archivo origen no llegue a eof
        while ( !archOrigen.eof() ) {
            //   Del archivo origen se extrae caracter por caracter
            archOrigen.get(unChar);

            if ( archOrigen.eof() ) {
                break;
            }

            //   Al caracter extraido se le suman tres y se mete al archivo destino
            unChar = unChar + 3;

            archDestino.put(unChar);
        }

        archOrigen.close();
        archDestino.close();

        cout << "Archivo Cifrado. " << endl << endl;
    }
}

void Cifrado::descifrar()
{
    ifstream archOrigen( "ArchivoCifrado.CSV", ios::in );

    if( !archOrigen ) {
        cerr << "No se pudo abrir el archivo origen." << endl << endl;
    }
    else {
        ofstream archDestino( "ArchivoDescifrado.CSV", ios::out );

        archOrigen.seekg(0);
        archDestino.seekp(0);

        char contrasena[500];

        cout << "Ingrese la contraseña: ";
        cin >> contrasena;

        // Se lee la contrasena del archivo origen
        char unChar = ' ';
        char cd[500]; //contrasena descifrada
        int i = 0;

        while ( unChar != '#' ) {
            archOrigen >> unChar;

            if ( unChar == '#') {
                break;
            }
            cd[ i ] = unChar - 3;
            //cout << cd[i] << " = " << unChar << endl;
            i++;
        }
        cd[i] = '\0';

        //cout << "contrasena: " <<  contrasena << endl;
        //cout << "contrasenaArch: " <<  cd << endl;

        // Si la contrasena del archivo origen es igual a la del parametro
        if ( strcmp( cd, contrasena ) == 0 ) {
            //archOrigen >> unChar; // extrae el delimitador de contrasena #

            //   Mientras el archivo origen no llegue a eof
            while ( !archOrigen.eof() ) {
                //      Del archivo origen se extrae caracter por caracter
                archOrigen.get(unChar);

                if ( archOrigen.eof() ) {
                    break;
                }

                //      Al caracter extraido se le restan tres y se mete al archivo destino
                unChar = unChar - 3;

                archDestino.put(unChar);
            }

            cout << "Archivo Descifrado. " << endl << endl;
        }
        else { // Si las contrasenas son diferentes
            //   mostrar contrasena incorrecta
            cout << endl << "ERROR: CONTRASENA INCORRECTA." << endl << endl;
        }

        archOrigen.close();
        archDestino.close();
    }
}
