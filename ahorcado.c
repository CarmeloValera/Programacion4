#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ahorcado.h"
#include "util.h"

void jugarAhorcado() {
    
    const char* palabraSecreta = leerProxPalabra("palabras.txt");

    char letras[100] = "";
    int intentos = 6;
    int aciertos = 0;
    int longitud = strlen(palabraSecreta);
    char letra;
    int letraYaIngresada;

    printf("\n=== Juego del Ahorcado ===\n");

    while (intentos > 0 && aciertos < longitud) {
        printf("\nPalabra: ");
        for (int i = 0; i < longitud; i++) {
            if (strchr(letras, palabraSecreta[i]) != NULL) {
                printf("%c ", palabraSecreta[i]);
            } else {
                printf("_ ");
            }
        }

        printf("\nIntentos restantes: %d\n", intentos);
        printf("Ingrese una letra: ");
        scanf(" %c", &letra);
        letra = tolower(letra);

        letraYaIngresada = strchr(letras, letra) != NULL;
        if (letraYaIngresada) {
            printf("Esa letra ya esta puesta. Prueba otra.\n");
            continue;
        }

        strncat(letras, &letra, 1);

        int letraCorrecta = 0;
        for (int i = 0; i < longitud; i++) {
            if (palabraSecreta[i] == letra) {
                letraCorrecta = 1;
                aciertos++;
            }
        }

        if (letraCorrecta) {
            printf("¡Correcto! La letra '%c' está en la palabra.\n", letra);
        } else {
            printf("Incorrecto. La letra '%c' no esta.\n", letra);
            intentos--;
        }
    }

    if (aciertos == longitud) {
        printf("\n¡Felicidades! Adivinaste la palabra: %s\n", palabraSecreta);
    } else {
        printf("\nHas perdido. La palabra era: %s\n", palabraSecreta);
    }
    guardarHistorialAhorcado(palabraSecreta, aciertos, intentos);
}
