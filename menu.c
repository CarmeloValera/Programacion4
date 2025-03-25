#include <stdio.h>
#include "menu.h"

void iniciarSesion() {
    printf("Iniciando sesion...\n");
}

void registrar() {
    printf("Registrando usuario...\n");
}

void jugar() {
    int opcion;
    do {
        printf("\n=== Menu Jugar ===\n");
        printf("1. Jugar al ahorcado\n");
        printf("2. Jugar a la secuencia numerica\n");
        printf("3. Historial del usuario\n");
        printf("4. Salir al menu principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("ahorcado...\n");
                break;
            case 2:
                printf("secuencia numerica...\n");
                break;
            case 3:
                printf("historial del usuario...");
                break;
            case 4:
                printf("Saliendo al menú principal...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 4);
}

// Submenú de opciones del usuario
void opcionesUsuario() {
    int opcion;
    do {
        printf("\n=== Opciones del Usuario ===\n");
        printf("1. Cambiar nombre de usuario\n");
        printf("2. Cambiar contrasena\n");
        printf("3. Volver\n");
        printf("Seleccione una opción: ");
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
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 3);
}