#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "codigo.h"
#include "util.h" 
#include "usuarios.h"

void generarCodigo(int codigo[4]) {
    for (int i = 0; i < 4; i++) {
        codigo[i] = rand() % 10;
    }
}

void jugarCodigo(Usuario user) {
    int codigoSecreto[4];
    int intento[4];
    char entrada[10];
    int intentosMax = 8;
    int exito = 0;
    int intentosUsados = 0;

    srand(time(NULL));
    generarCodigo(codigoSecreto);

    printf("\n=== Juego de Codigo Numerico ===\n");
    printf("Adivina el codigo de 4 digitos. Tienes %d intentos.\n", intentosMax);
    printf("Pistas: X = número correcto y en su lugar, O = número correcto en lugar incorrecto, - = número incorrecto\n");

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

        char resultado[5] = "";  // Aquí guardamos la secuencia de pistas

        // Primero, buscar aciertos exactos (X)
        for (int i = 0; i < 4; i++) {
            if (intento[i] == codigoSecreto[i]) {
                resultado[i] = 'X';
                usadosCodigo[i] = 1;
                usadosIntento[i] = 1;
                aciertos++;
            } else {
                resultado[i] = '-'; // De momento lo marcamos como -
            }
        }

        // Después, buscar aciertos en posición incorrecta (O)
        for (int i = 0; i < 4; i++) {
            if (resultado[i] == '-') { // Solo intentamos corregir los que son -
                for (int j = 0; j < 4; j++) {
                    if (!usadosCodigo[j] && intento[i] == codigoSecreto[j]) {
                        resultado[i] = 'O';
                        usadosCodigo[j] = 1;
                        break;
                    }
                }
            }
        }

        // Imprimir el resultado
        for (int i = 0; i < 4; i++) {
            printf("%c ", resultado[i]);
        }
        printf("\n");

        if (aciertos == 4) {
            printf("\n🎉 ¡Felicidades! Has adivinado el código correctamente.\n");
            exito = 1;
            intentosUsados = intentoNum;
            guardarHistorialCodigo(user.nombre, codigoSecreto, exito, intentosUsados);
            return;
        }
    }

    printf("\n😢 Lo siento, has agotado tus intentos.\n");
    printf("El código secreto era: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", codigoSecreto[i]);
    }
    printf("\n");

    exito = 0;
    intentosUsados = intentosMax;
    guardarHistorialCodigo(user.nombre, codigoSecreto, exito, intentosUsados);
}
