#include "compresion.h"

Compresion::Compresion()
{

}

void Compresion::comprimir()
{
    ifstream archOrigen( "CopiaSeguridad.csv", ios::in );

    if( !archOrigen ) {
        cerr << "No se pudo abrir el archivo origen para la compresion." << endl << endl;
    }
    else {
        cout << "Comprimiendo..." << endl << endl;

        ofstream archDestino( "comprimido.CSV", ios::out );

        archOrigen.seekg(0);
        archDestino.seekp(0);

        char unChar;
        char otroChar;

        int cont = 1;

        // Del archivo origen se extrae un caracter
        archOrigen.get(unChar);

        // Mientras el archivo origen no llegue a eof
        // Del archivo origen se extrae caracter por caracter
        while ( !archOrigen.eof() ) {

            // Del archivo origen se extrae otro caracter
            archOrigen.get(otroChar);

            //si los dos caracteres son iguales
            if ( unChar == otroChar ) {
                cont++; //el contador se incrementa en 1
            }
            else{ // Pero si son diferentes

                if ( cont == 1 ) { // si el contador es igual a 1
                    // mete al archivo destino el unChar
                    archDestino.put(unChar);
                    unChar = otroChar;
                }
                else if ( cont == 2 ) { // si el contador es igual a 2
                    // mete al archivo destino el unChar dos veces
                    archDestino.put(unChar);
                    archDestino.put(unChar);
                    unChar = otroChar;
                    cont = 1;
                }
                else if ( cont >= 3 ) { // si el contador es mayor o igual a 3
                    archDestino << cont;
                    archDestino.put(unChar);
                    unChar = otroChar;
                    cont = 1;
                }
            }

            if ( archOrigen.eof() ) {
                break;
            }
        }

        archOrigen.close();
        archDestino.close();

        cout << "Archivo comprimido. " << endl << endl;
    }
}
