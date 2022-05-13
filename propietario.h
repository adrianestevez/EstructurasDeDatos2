#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include<fstream>
#include <iostream>
#include <string>
#include <string.h>

#include "correo.h"

class Propietario
{
public:
    Propietario();
    void Exportar();
    void Modificar(unsigned int);
    void Eliminar(unsigned int);
    void menuModificarPROPIETARIO(Correo&,const unsigned int,char* remitente,char* destinatario,char* copiaC,
                                  char* copiaCC,char* asunto,char* contenido,
                                  int& tamId,int& tamRemi,int&tamDest,int&tamCC,int&tamCCC,int&tamAsu,int&tamCont);

};

#endif // PROPIETARIO_H


//#include <iostream>
//#include <fstream>
//#include "correo.h"

//using namespace std;

//class Propietario
//{
//public:
//    Propietario();
//    void Exportar();
//    void Eliminar(int identificador);
//    void Modificar(int identificador);

//};
