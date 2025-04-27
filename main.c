#include <stdio.h>
#include "menu.h"
#include "bbdd/sqlite3.h"
#include "bbdd/bbddmain.h"
BBDD baseDatos;
Usuario user;
int main() {
    int opcion;
    if (abrir_base(&baseDatos, "BaseDeDatos.db") != SQLITE_OK) {
        return 1;
    }

    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Iniciar sesion\n");
        printf("2. Registrar\n");
        printf("3. Jugar\n");
        printf("4. Opciones del usuario\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                user = iniciarSesion(&baseDatos);
                break;
            case 2:
                registrar();
                break;
            case 3:
                jugar();
                break;
            case 4:
                opcionesUsuario(user);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);
    cerrar_base(&baseDatos);
    return 0;
}
