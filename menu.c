#include <stdio.h>
#include "menu.h"
#include "ahorcado.h"
#include "codigo.h"
#include "util.h"
#include "usuarios.h"    
#include "bbdd/bbddmain.h" 
#include "adivina.h"
#include <string.h>

extern BBDD baseDatos; 
Usuario usuarioLogueado = {"Invitado", ""};

Usuario iniciarSesion(BBDD *baseDatos) {
    Usuario user = { "", "" }; 

    // Pedimos el nombre y la contraseña
    strcpy(user.nombre, pedir_usuario());  
    strcpy(user.contrasena, pedir_contrasena()); 

    // Verificamos si el inicio de sesión es exitoso
    if (iniciar_sesion(baseDatos, user.nombre, user.contrasena)) {
        printf("Inicio de sesión exitoso.\n");
        usuarioLogueado = user;  // Cambia el usuario logueado
        return user;
    } else {
        printf("Nombre de usuario o contraseña incorrectos.\n");
        return usuarioLogueado;  // Retorna el usuario invitado si la autenticación falla
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

    // Intentamos cerrar la base de datos correctamente
}

void jugar(Usuario user) {
    int opcion;
    do {
        mostrarMenuJugar();
        opcion = leer_entero("Elige una opción: ", 1, 5);


        switch (opcion) {
            case 1:
                printf("ahorcado...\n");
                jugarAhorcado(user);
                break;
            case 2:
                printf("secuencia numerica...\n");
                jugarCodigo(user);
                break;
            case 3: 
                printf("generando numero aleatorio...\n");
                jugarAdivinaNumero(user.nombre); 
                break;
            case 4:
                printf("historial del usuario...");
                mostrarHistorial(user);
                break;
            case 5:
                printf("Saliendo al menu principal...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);
}

void opcionesUsuario(Usuario user) {
    if (strcmp(user.nombre, "Invitado") == 0) {
        // Si el usuario es "Invitado", significa que no ha iniciado sesión
        printf("El usuario debe iniciar sesión antes de acceder a estas opciones.\n");
        return;  // Sale de la función sin ofrecer las opciones
    }

    int opcion;
    do {
        mostrarMenuUsuario();
        opcion = leer_entero("Elige una opción: ", 1, 5);
        switch ((OpcionMenu)opcion) {
            case 1:
                {
                    char nuevo_nombre[50];  // Declarar dentro de un bloque para evitar el error
                    printf("Ingrese el nuevo nombre de usuario: ");
                    leer_cadena("Introduce nombre: ", nuevo_nombre, sizeof nuevo_nombre);
                    
                    int intentos = 3;
                    int exito = 0;

                    while (intentos > 0 && !exito) {
                        if (cambiar_nombre_usuario(&baseDatos, user.nombre, nuevo_nombre) == 0) {
                            printf("Nombre de usuario actualizado con éxito.\n");
                            exito = 1;  // Si la operación es exitosa, salimos del ciclo
                        } else {
                            printf("La base de datos está bloqueada, reintentando...\n");
                            intentos--;
                            sqlite3_sleep(500);  // Esperamos un poco antes de intentar de nuevo
                        }
                    }
                    if (intentos == 0) {
                        printf("Error: No se pudo actualizar el nombre de usuario. La base de datos sigue bloqueada.\n");
                    }
                }
                break;

            case 2:
                {
                    char nueva_contrasena[MAX_USUARIO];  // Declarar dentro de un bloque para evitar el error
                    printf("Ingrese la nueva contraseña: ");
                    leer_cadena("Introduce nombre: ", nueva_contrasena , sizeof nueva_contrasena);
                    
                    int intentos = 3;
                    int exito = 0;

                    while (intentos > 0 && !exito) {
                        if (cambiar_contrasena(&baseDatos, user.nombre, nueva_contrasena) == 0) {
                            printf("Contraseña del usuario actualizada con éxito.\n");
                            exito = 1;  // Si la operación es exitosa, salimos del ciclo
                        } else {
                            printf("La base de datos está bloqueada, reintentando...\n");
                            intentos--;
                            sqlite3_sleep(500);  // Esperamos un poco antes de intentar de nuevo
                        }
                    }
                    if (intentos == 0) {
                        printf("Error: No se pudo actualizar la contraseña. La base de datos sigue bloqueada.\n");
                    }
                }
                break;

            case 3:
                printf("Volviendo...\n");
                break;

            default:
                printf("Opción invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 3);

    // Cerramos la base de datos después de salir del bucle
}
void mostrarMenuPrincipal(void) {
    const char *ops[] = {
        "Iniciar sesión",
        "Registrar",
        "Jugar",
        "Opciones del usuario",
        "Salir"
    };
    mostrarMenu("Menu Principal", ops, 5);
}

void mostrarMenuJugar(void) {
    const char *ops[] = {
      "Jugar al ahorcado",
      "Jugar a la secuencia numerica",
      "Adivinar numero",
      "Historial del usuario",
      "Volver al menu principal"
    };
    mostrarMenu("Menu Jugar", ops, 5);
}

void mostrarMenuUsuario(void){
    const char *ops[] = {
        "Cambiar nombre de usuario",
        "Cambiar contrasena",
        "Volver al menu principal"
      };
      mostrarMenu("Menu Usuario", ops, 3);
  }


