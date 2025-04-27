#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "codigo.h"
#include "util.h"  // 🔥 Añadido para poder guardar el historial

void generarCodigo(int codigo[4]) {
    for (int i = 0; i < 4; i++) {
        codigo[i] = rand() % 10;
    }
}

void jugarCodigo() {
    int codigoSecreto[4];
    int intento[4];
    char entrada[10];
    int intentosMax = 8;
    int exito = 0;           // 🔥 Nuevo: Para saber si el jugador ganó
    int intentosUsados = 0;   // 🔥 Nuevo: Para guardar los intentos usados

    srand(time(NULL));
    generarCodigo(codigoSecreto);

    printf("\n=== Juego de Codigo Numerico ===\n");
    printf("Adivina el codigo de 4 digitos. Tienes %d intentos.\n", intentosMax);
    printf("Pistas: X = numero correcto y en su lugar, O = numero correcto pero en lugar incorrecto\n");

    for (int intentoNum = 1; intentoNum <= intentosMax; intentoNum++) {
        printf("\nIntento %d: ", intentoNum);
        scanf("%s", entrada);

        if (strlen(entrada) != 4) {
            printf("Debes ingresar exactamente 4 dígitos.\n");
            intentoNum--;
            continue;
        }

        for (int i = 0; i < 4; i++) {
            intento[i] = entrada[i] - '0';
        }

        int aciertos = 0;
        int usadosCodigo[4] = {0};
        int usadosIntento[4] = {0};

        for (int i = 0; i < 4; i++) {
            if (intento[i] == codigoSecreto[i]) {
                printf("X ");
                usadosCodigo[i] = 1;
                usadosIntento[i] = 1;
                aciertos++;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (usadosIntento[i]) continue;
            for (int j = 0; j < 4; j++) {
                if (!usadosCodigo[j] && intento[i] == codigoSecreto[j]) {
                    printf("O ");
                    usadosCodigo[j] = 1;
                    break;
                }
            }
        }

        if (aciertos == 4) {
            printf("\n🎉 ¡Felicidades! Has adivinado el codigo correctamente.\n");
            exito = 1;
            intentosUsados = intentoNum;
            guardarHistorialCodigo(codigoSecreto, exito, intentosUsados);  // 🔥 Guardar victoria
            return;
        }
    }

    printf("\n😢 Lo siento, has agotado tus intentos.\n");
    printf("El codigo secreto era: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", codigoSecreto[i]);
    }
    printf("\n");

    exito = 0;
    intentosUsados = intentosMax;
    guardarHistorialCodigo(codigoSecreto, exito, intentosUsados);  // 🔥 Guardar derrota
}
