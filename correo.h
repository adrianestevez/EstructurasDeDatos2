#ifndef CORREO_H
#define CORREO_H
#define E 80
#define M 1000
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <string.h>
#include <string>


using namespace std;

class Correo
{
    struct Correos{
        unsigned int id=0;
        char remitente[E];
        char fecha[E];
        char hora[E];
        char destinatario[E];
        char cc[E];
        char bcc[E];
        char asunto[E];
        char contenido[M];

    }email;

    unsigned int distBytes=0,ident=0, contadorCorreos=0;

public:
    Correo();

    friend ostream &operator <<(ostream &escribe, const Correo &c);
    void Escribir();
    bool validarID(const unsigned int &ident);

    void Leer_AD(unsigned int ident);
    void Modificar_AD();

    void Leer_Sec();
    void Modificar_Sec();

    void Eliminar_Id(unsigned int ident);
    void Eliminar_Sec();

    void Exportar();
    void Importar();

    void ModificarCSV();
    void EliminarCSV();


    //Getters y setters del struct
    unsigned int getId() const;
    void setId(unsigned int value);

    void setRemitente(const string &value);
    string getRemitente() const;

    string getFecha() const;
    void setFecha(const string &value);

    string getHora() const;
    void setHora(const string &value);

    void setDestinatario(const string &value);
    string getDestinatario() const;

    void setCc(const string &value);
    string getCc() const;

    void setBcc(const string &value);
    string getBcc() const;

    void setAsunto(const string &value);
    string getAsunto() const;

    void setContenido(const string &value);
    string getContenido() const;

    Correos getCorreo() const;



};

#endif // CORREO_H
