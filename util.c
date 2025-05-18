#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "usuarios.h"
#include "menu.h"

#define MAX_LINEA 1024
#define MAX_PALABRAS 100
#define MAX_LONGITUD 256

char* leerProxPalabra(const char* fichero) {
    FILE* archivo = fopen(fichero, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    static char palabraElegida[MAX_LONGITUD];
    char palabras[MAX_PALABRAS][MAX_LONGITUD];
    int contador = 0;
    char buffer[MAX_LINEA];

    while (fgets(buffer, sizeof(buffer), archivo)) {
        char* token = strtok(buffer, " \t\r\n");
        while (token != NULL) {
            strncpy(palabras[contador], token, MAX_LONGITUD);
            contador++;
            if (contador >= MAX_PALABRAS) {
                break;
            }
            token = strtok(NULL, " \t\r\n");
        }
    }

    fclose(archivo);

    if (contador == 0) {
        fprintf(stderr, "No se encontraron palabras en el archivo.\n");
        exit(1);
    }

    srand(time(NULL));

    int indiceAleatorio = rand() % contador;
    strncpy(palabraElegida, palabras[indiceAleatorio], MAX_LONGITUD);

    return palabraElegida;
}

void guardarHistorialAhorcado(const char *usuario, const char* palabraSecreta, int aciertos, int intentosRestantes) {
    if (usuario == NULL || strlen(usuario) == 0) {
        // No hay usuario, no guardamos nada
        return;
    }

    FILE* historial = fopen("historial.txt", "a");
    if (historial == NULL) {
        perror("Error al abrir historial.txt");
        return;
    }

    time_t ahora = time(NULL);
    struct tm* t = localtime(&ahora);

    fprintf(historial, "=== Partida de Ahorcado ===\n");
    fprintf(historial, "Usuario: %s\n", usuario);
    fprintf(historial, "Fecha: %02d/%02d/%04d %02d:%02d\n", t->tm_mday, t->tm_mon+1, t->tm_year+1900, t->tm_hour, t->tm_min);
    fprintf(historial, "Palabra secreta: %s\n", palabraSecreta);
    fprintf(historial, "Aciertos: %d\n", aciertos);
    fprintf(historial, "Intentos restantes: %d\n", intentosRestantes);
    fprintf(historial, "Resultado: %s\n", (aciertos == strlen(palabraSecreta)) ? "Victoria" : "Derrota");
    fprintf(historial, "---------------------------\n\n");

    fclose(historial);
}

void guardarHistorialCodigo(const char *usuario, int codigoSecreto[4], int exito, int intentosUsados) {
    if (usuario == NULL || strlen(usuario) == 0) {
        // No hay usuario, no guardamos nada
        return;
    }

    FILE* historial = fopen("historial.txt", "a");
    if (historial == NULL) {
        perror("Error al abrir historial.txt");
        return;
    }

    time_t ahora = time(NULL);
    struct tm* t = localtime(&ahora);

    fprintf(historial, "=== Partida de Codigo Numerico ===\n");
    fprintf(historial, "Usuario: %s\n", usuario);
    fprintf(historial, "Fecha: %02d/%02d/%04d %02d:%02d\n", t->tm_mday, t->tm_mon+1, t->tm_year+1900, t->tm_hour, t->tm_min);
    fprintf(historial, "Codigo secreto: ");
    for (int i = 0; i < 4; i++) {
        fprintf(historial, "%d", codigoSecreto[i]);
    }
    fprintf(historial, "\n");

    fprintf(historial, "Intentos usados: %d\n", intentosUsados);
    fprintf(historial, "Resultado: %s\n", (exito) ? "Victoria" : "Derrota");
    fprintf(historial, "---------------------------\n\n");

    fclose(historial);
}
void mostrarHistorial(Usuario user) {
    if (strlen(user.nombre) == 0) {
        printf("\nDebes iniciar sesión para ver tu historial.\n");
        return;
    }

    FILE* historial = fopen("historial.txt", "r");
    if (historial == NULL) {
        printf("\nNo se encontró historial de partidas.\n");
        return;
    }

    char *lineas[MAX_LINEA];
    int numLineas = 0;
    char buffer[MAX_LINEA];

    while (fgets(buffer, sizeof(buffer), historial) != NULL) {
        lineas[numLineas] = strdup(buffer); 
        numLineas++;
        if (numLineas >= MAX_LINEA) {
            break;
        }
    }
    fclose(historial);

    if (numLineas == 0) {
        printf("\nEl historial está vacío.\n");
        return;
    }

    // Buscar partidas que correspondan al usuario
    int indicesPartidas[MAX_LINEA];
    int numPartidas = 0;
    int partidaInicio = -1;
    int perteneceUsuario = 0;

    for (int i = 0; i < numLineas; i++) {
        if (strstr(lineas[i], "=== Partida") != NULL) {
            partidaInicio = i;
            perteneceUsuario = 0; // reset para nueva partida
        }
        if (partidaInicio != -1 && strstr(lineas[i], "Usuario: ") != NULL) {
            char nombreUsuario[MAX_LONGITUD];
            sscanf(lineas[i], "Usuario: %s", nombreUsuario);

            if (strcmp(nombreUsuario, user.nombre) == 0) {
                perteneceUsuario = 1;
            }
        }
        if (perteneceUsuario && ((i + 1 >= numLineas) || strstr(lineas[i + 1], "=== Partida") != NULL)) {
            indicesPartidas[numPartidas++] = partidaInicio;
            partidaInicio = -1;
        }
    }

    if (numPartidas == 0) {
        printf("\nNo se encontraron partidas para el usuario '%s'.\n", user.nombre);
        for (int i = 0; i < numLineas; i++) {
            free(lineas[i]);
        }
        return;
    }

    // Mostrar partidas filtradas
    int partidaActual = 0;
    int opcion;
    do {
        int inicio = indicesPartidas[partidaActual];
        printf("\n=== Mostrando Partida ===\n\n");

        for (int i = inicio; i < numLineas; i++) {
            printf("%s", lineas[i]);
            if ((i + 1 < numLineas) && strstr(lineas[i + 1], "=== Partida") != NULL) {
                break;
            }
        }

        printf("\n1. Ver siguiente partida\n");
        printf("2. Salir\n");
        printf("Seleccione una opción: ");
        opcion = leer_entero("Selecciona opción: ", 1, MAX_OPC);


        if (opcion == 1) {
            partidaActual++;
            if (partidaActual >= numPartidas) {
                printf("\nNo hay más partidas.\n");
                opcion = 2;
            }
        } else if (opcion != 2) {
            printf("\nOpción inválida.\n");
        }

    } while (opcion != 2);

    for (int i = 0; i < numLineas; i++) {
        free(lineas[i]);
    }
}
int leer_entero(const char *prompt, int min, int max){
    char linea[128];
    int valor;
    while (1) {
        printf("%s", prompt);
        if (!fgets(linea, sizeof(linea), stdin)) exit(1);
        if (sscanf(linea, "%d", &valor)==1 && valor>=min && valor<=max)
            return valor;
        printf("  Entrada inválida. Introduce un número entre %d y %d.\n", min, max);
    }
}
void leer_cadena(const char *prompt, char *buf, size_t len){
    printf("%s", prompt);
    if (fgets(buf, len, stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
    }
}
void mostrarMenu(const char *titulo, const char *ops[], int n){
    printf("\n=== %s ===\n", titulo);
    for (int i = 0; i < n; i++)
        printf("%d) %s\n", i+1, ops[i]);
}

void guardarHistorialNumero(const char *usuario, int secreto, int intentos) {
    if (usuario == NULL || strlen(usuario) == 0) return;

    FILE *hist = fopen("historial.txt", "a");
    if (!hist) {
        perror("Error al abrir historial.txt");
        return;
    }

    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);

    fprintf(hist, "=== Partida de Adivina el número ===\n");
    fprintf(hist, "Usuario: %s\n", usuario);
    fprintf(hist, "Fecha: %02d/%02d/%04d %02d:%02d\n",
            t->tm_mday, t->tm_mon + 1,
            t->tm_year + 1900, t->tm_hour, t->tm_min);
    fprintf(hist, "Número secreto: %d\n", secreto);
    fprintf(hist, "Intentos necesitados: %d\n", intentos);
    fprintf(hist, "Resultado: Victoria\n");
    fprintf(hist, "---------------------------\n\n");

    fclose(hist);
}
