#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_USUARIO 50
#define MAX_CONTRASENA 50

typedef struct {
    char nombre[MAX_USUARIO];
    char contrasena[MAX_CONTRASENA];
} Usuario;

char* pedir_usuario();
char* pedir_contrasena();


#endif