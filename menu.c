#include <stdio.h>
#include "menu.h"
#include "ahorcado.h"
#include "codigo.h"
#include "util.h"
#include "usuarios.h"    // <-- nuevo
#include "bbdd/bbddmain.h" 
#include <string.h>

extern BBDD baseDatos; 
void iniciarSesion() {
    Usuario user;

    strcpy(user.nombre, pedir_usuario());  
    strcpy(user.contrasena, pedir_contrasena()); 

    if (iniciar_sesion(&baseDatos, user.nombre, user.contrasena)) {
        printf("Inicio de sesión exitoso.\n");
        // Aquí podrías continuar con el juego o el menú principal
    } else {
        printf("Nombre de usuario o contraseña incorrectos.\n");
    }
}

void registrar() {
    Usuario user;
    printf("\n=== Registrar Usuario ===\n");

    strcpy(user.nombre, pedir_usuario());   // Primero solo pedimos el nombre

    if (existe_usuario(&baseDatos, user.nombre)) {   // <-- FUNCION NUEVA que comprobaremos en bbddmain.c
        printf("El nombre de usuario ya existe. Intenta con otro.\n");
        return;
    }

    strcpy(user.contrasena, pedir_contrasena());  // Si no existe, ahora pedimos la contraseña

    if (registrar_usuario(&baseDatos, user.nombre, user.contrasena) == SQLITE_OK) {
        printf("Usuario registrado exitosamente.\n");
    } else {
        printf("Error al registrar usuario.\n");
    }
}

void jugar() {
    int opcion;
    do {
        printf("\n=== Menu Jugar ===\n");
        printf("1. Jugar al ahorcado\n");
        printf("2. Jugar a la secuencia numerica\n");
        printf("3. Historial del usuario\n");
        printf("4. Salir al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("ahorcado...\n");
                jugarAhorcado();
                break;
            case 2:
                printf("secuencia numerica...\n");
                jugarCodigo();
                break;
            case 3:
                printf("historial del usuario...");
                mostrarHistorial();
                break;
            case 4:
                printf("Saliendo al menu principal...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 4);
}

void opcionesUsuario() {
    int opcion;
    do {
        printf("\n=== Opciones del Usuario ===\n");
        printf("1. Cambiar nombre de usuario\n");
        printf("2. Cambiar contrasena\n");
        printf("3. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Cambiando nombre de usuario...\n");
                break;
            case 2:
                printf("Cambiando contrasena...\n");
                break;
            case 3:
                printf("Voloviendo...\n");
                break;
            default:
                printf("Opción invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 3);
}