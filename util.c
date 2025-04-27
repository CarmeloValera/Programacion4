#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

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

void guardarHistorialAhorcado(const char* palabraSecreta, int aciertos, int intentosRestantes) {
    FILE* historial = fopen("historial.txt", "a");
    if (historial == NULL) {
        perror("Error al abrir historial.txt");
        return;
    }

    time_t ahora = time(NULL);
    struct tm* t = localtime(&ahora);

    fprintf(historial, "=== Partida de Ahorcado ===\n");
    fprintf(historial, "Fecha: %02d/%02d/%04d %02d:%02d\n", t->tm_mday, t->tm_mon+1, t->tm_year+1900, t->tm_hour, t->tm_min);
    fprintf(historial, "Palabra secreta: %s\n", palabraSecreta);
    fprintf(historial, "Aciertos: %d\n", aciertos);
    fprintf(historial, "Intentos restantes: %d\n", intentosRestantes);
    fprintf(historial, "Resultado: %s\n", (aciertos == strlen(palabraSecreta)) ? "Victoria" : "Derrota");
    fprintf(historial, "---------------------------\n\n");

    fclose(historial);
}

void guardarHistorialCodigo(int codigoSecreto[4], int exito, int intentosUsados) {
    FILE* historial = fopen("historial.txt", "a");
    if (historial == NULL) {
        perror("Error al abrir historial.txt");
        return;
    }

    time_t ahora = time(NULL);
    struct tm* t = localtime(&ahora);

    fprintf(historial, "=== Partida de Codigo Numerico ===\n");
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
