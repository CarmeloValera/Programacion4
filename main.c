#include <stdio.h>
#include "menu.h"
#include "bbdd/sqlite3.h"
#include "bbdd/bbddmain.h"
#include "menu.h"
#include "util.h"

BBDD baseDatos;
Usuario user;
int main() {
    int opcion;
    if (abrir_base(&baseDatos, "BaseDeDatos.db") != SQLITE_OK) {
        return 1;
    }

    do {
        mostrarMenuPrincipal();
        opcion = leer_entero("Elige una opción: ", 1, 5);


        switch ((OpcionMenu)opcion) {

            case OP_INICIAR_SESION: user = iniciarSesion(&baseDatos); 
            break;
            case OP_REGISTRAR:      registrar();                   
            break;
            case OP_JUGAR:          jugar(user);                   
            break;
            case OP_OPCIONES_USUARIO: opcionesUsuario(user);       
            break;
            case OP_SALIR:          printf("Saliendo…\n");         
            break;

            default:
                printf("Opción invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);
    cerrar_base(&baseDatos);
    return 0;
}
