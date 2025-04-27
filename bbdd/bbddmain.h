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
int cambiar_nombre_usuario(BBDD *base, const char *usuario_actual, const char *nuevo_nombre);
int cambiar_contrasena(BBDD *base, const char *usuario, const char *nueva_contrasena);

#endif 