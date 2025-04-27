#ifndef MENU_H
#define MENU_H
#include <stdbool.h> 
#include "usuarios.h"
#include "bbdd/bbddmain.h"

Usuario iniciarSesion(BBDD *baseDatos);
void registrar();
void jugar();
void opcionesUsuario(Usuario);
Usuario obetenerUsuario();

#endif
