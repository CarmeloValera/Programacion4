#include <stdio.h>
#include <string.h>  // Para usar strcpy
#include "usuarios.h"

// Función que pide el nombre de usuario y lo devuelve como un puntero a char
char* pedir_usuario(void) {
    static char nombre[MAX_USUARIO];  // Usamos static para que la cadena persista fuera de la función
    printf("Ingrese su nombre de usuario: ");
    scanf("%49s", nombre);  // Lee hasta 49 caracteres
    return nombre;
}

// Función que pide la contraseña y lo devuelve como un puntero a char
char* pedir_contrasena(void) {
    static char contrasena[MAX_CONTRASENA];  // Usamos static para que la cadena persista fuera de la función
    printf("Ingrese su contraseña: ");
    scanf("%49s", contrasena);  // Lee hasta 49 caracteres
    return contrasena;
}


