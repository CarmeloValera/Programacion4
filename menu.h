#ifndef MENU_H
#define MENU_H
#define MAX_OPC 5
#include <stdbool.h> 
#include "usuarios.h"
#include "bbdd/bbddmain.h"


typedef enum {
    OP_INICIAR_SESION = 1,
    OP_REGISTRAR,
    OP_JUGAR,
    OP_OPCIONES_USUARIO,
    OP_SALIR
} OpcionMenu;

Usuario iniciarSesion(BBDD *baseDatos);
void registrar();
void jugar(Usuario);
void opcionesUsuario(Usuario);
void mostrarMenuPrincipal(void);
void mostrarMenuJugar(void);
void mostrarMenuUsuario(void);



#endif
