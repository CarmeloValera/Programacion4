#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "adivina.h"

void jugarAdivinaNumero(const char *usuario) {
    srand((unsigned)time(NULL));
    int secreto = rand() % 100 + 1, intento, cont = 0;
    printf("=== Adivina el número (1-100) ===\n");
    do {
        intento = leer_entero("Tu intento: ", 1, 100);
        cont++;
        if (intento < secreto) printf("  Más alto\n");
        else if (intento > secreto) printf("  Más bajo\n");
    } while (intento != secreto);
    printf("¡Acertaste en %d intentos!\n", cont);
    guardarHistorialNumero(usuario, secreto, cont);
}
