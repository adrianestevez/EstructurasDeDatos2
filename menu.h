#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "correo.h"
#include "copia_seguridad.h"

using namespace std;

class Menu
{

public:
    Menu();
    void Mostrar_Menu();
    void Menu_Eliminar();
    void Menu_Modificar();
    void Menu_Leer();
    void Menu_Copia_Seguridad();
    void Menu_Formato_Propietario();
    void Menu_Busquedas_Eficiente();
    void Menu_Tabla_Dispersion();
};

#endif // MENU_H
