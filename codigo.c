#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "codigo.h"
#include "util.h" 
#include "usuarios.h"

void generarCodigo(int codigo[CODE_LENGTH]) {
    for (int i = 0; i < CODE_LENGTH; i++) {
        codigo[i] = rand() % 10;
    }
}

void jugarCodigo(Usuario user) {
    int codigoSecreto[CODE_LENGTH];
    int intento[CODE_LENGTH];
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
        leer_cadena("Introduce nombre: ", entrada, sizeof entrada);

        if (strlen(entrada) != CODE_LENGTH) {
            printf("Debes ingresar exactamente 4 dígitos.\n");
            intentoNum--;
            continue;
        }

        for (int i = 0; i < CODE_LENGTH; i++) {
            intento[i] = entrada[i] - '0';
        }

        int aciertos = 0;
        int usadosCodigo[CODE_LENGTH] = {0};
        int usadosIntento[CODE_LENGTH] = {0};

        char resultado[5] = "";  

        // Primero, buscar aciertos exactos (X)
        for (int i = 0; i < CODE_LENGTH; i++) {
            if (intento[i] == codigoSecreto[i]) {
                resultado[i] = 'X';
                usadosCodigo[i] = 1;
                usadosIntento[i] = 1;
                aciertos++;
            } else {
                resultado[i] = '-'; 
            }
        }

        // Después, buscar aciertos en posición incorrecta (O)
        for (int i = 0; i < CODE_LENGTH; i++) {
            if (resultado[i] == '-') { 
                for (int j = 0; j < CODE_LENGTH; j++) {
                    if (!usadosCodigo[j] && intento[i] == codigoSecreto[j]) {
                        resultado[i] = 'O';
                        usadosCodigo[j] = 1;
                        break;
                    }
                }
            }
        }

        
        for (int i = 0; i < CODE_LENGTH; i++) {
            printf("%c ", resultado[i]);
        }
        printf("\n");

        if (aciertos == CODE_LENGTH) {
            printf("\n🎉 ¡Felicidades! Has adivinado el código correctamente.\n");
            exito = 1;
            intentosUsados = intentoNum;
            guardarHistorialCodigo(user.nombre, codigoSecreto, exito, intentosUsados);
            return;
        }
    }

    printf("\n😢 Lo siento, has agotado tus intentos.\n");
    printf("El código secreto era: ");
    for (int i = 0; i < CODE_LENGTH; i++) {
        printf("%d", codigoSecreto[i]);
    }
    printf("\n");

    exito = 0;
    intentosUsados = intentosMax;
    guardarHistorialCodigo(user.nombre, codigoSecreto, exito, intentosUsados);
}
