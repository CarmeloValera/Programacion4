// main.c
#include <stdio.h>
#include "menu.h"

int main() {
    int opcion;

    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Iniciar sesión\n");
        printf("2. Registrar\n");
        printf("3. Jugar\n");
        printf("4. Opciones del usuario\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                iniciarSesion();
                break;
            case 2:
                registrar();
                break;
            case 3:
                jugar();
                break;
            case 4:
                opcionesUsuario();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}
