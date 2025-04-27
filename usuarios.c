#include <stdio.h>
#include <string.h> 
#include "usuarios.h"


char* pedir_usuario(void) {
    static char nombre[MAX_USUARIO];  // Usamos static para que la cadena persista fuera de la función
    printf("Ingrese su nombre de usuario: ");
    scanf("%49s", nombre);  // Lee hasta 49 caracteres
    return nombre;
}


char* pedir_contrasena(void) {
    static char contrasena[MAX_CONTRASENA];  // Usamos static para que la cadena persista fuera de la función
    printf("Ingrese su contraseña: ");
    scanf("%49s", contrasena);  // Lee hasta 49 caracteres
    return contrasena;
}


