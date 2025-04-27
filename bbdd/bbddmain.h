#ifndef BBDDMAIN_H
#define BBDDMAIN_H

#include "sqlite3.h"

// Estructura para manejar la base de datos
typedef struct {
    sqlite3 *db;
} BBDD;

// Funciones públicas
int abrir_base(BBDD *base, const char *nombre_archivo);
void cerrar_base(BBDD *base);
int registrar_usuario(BBDD *base, const char *usuario, const char *contrasena);
int iniciar_sesion(BBDD *base, const char *usuario, const char *contrasena);
int existe_usuario(BBDD *bd, const char *nombre_usuario);

#endif 