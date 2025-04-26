#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
