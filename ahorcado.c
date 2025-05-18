#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ahorcado.h"
#include "util.h"
#include "usuarios.h"


void jugarAhorcado(Usuario user) {

    printf("Elige nivel: 1)Fácil 2)Medio 3)Difícil\n");
    NivelAhorcado nivel = (NivelAhorcado)leer_entero("> ", 1, 3);

    iniciarAhorcadoConNivel(nivel, user);
//     const char* palabraSecreta = leerProxPalabra("palabras.txt");

//     char letras[100] = "";
//     int intentos = 6;
//     int aciertos = 0;
//     int longitud = strlen(palabraSecreta);
//     char letra;
//     int letraYaIngresada;

//     printf("\n=== Juego del Ahorcado ===\n");

//     while (intentos > 0 && aciertos < longitud) {
//         printf("\nPalabra: ");
//         for (int i = 0; i < longitud; i++) {
//             if (strchr(letras, palabraSecreta[i]) != NULL) {
//                 printf("%c ", palabraSecreta[i]);
//             } else {
//                 printf("_ ");
//             }
//         }

//         printf("\nIntentos restantes: %d\n", intentos);
//         printf("Ingrese una letra: ");
//         scanf(" %c", &letra);
//         letra = tolower(letra);

//         letraYaIngresada = strchr(letras, letra) != NULL;
//         if (letraYaIngresada) {
//             printf("Esa letra ya esta puesta. Prueba otra.\n");
//             continue;
//         }

//         strncat(letras, &letra, 1);

//         int letraCorrecta = 0;
//         for (int i = 0; i < longitud; i++) {
//             if (palabraSecreta[i] == letra) {
//                 letraCorrecta = 1;
//                 aciertos++;
//             }
//         }

//         if (letraCorrecta) {
//             printf("¡Correcto! La letra '%c' está en la palabra.\n", letra);
//         } else {
//             printf("Incorrecto. La letra '%c' no esta.\n", letra);
//             intentos--;
//         }
//     }

//     if (aciertos == longitud) {
//         printf("\n¡Felicidades! Adivinaste la palabra: %s\n", palabraSecreta);
//     } else {
//         printf("\nHas perdido. La palabra era: %s\n", palabraSecreta);
//     }
//     guardarHistorialAhorcado(user.nombre,palabraSecreta, aciertos, intentos);
 }

void iniciarAhorcadoConNivel(NivelAhorcado nivel, Usuario user){

    #define MAX_PAL 1000
    #define MAX_L   100

    char easy[MAX_PAL][MAX_L], 
         medium[MAX_PAL][MAX_L], 
         hard[MAX_PAL][MAX_L];
    int nE = 0, nM = 0, nH = 0;

    FILE *f = fopen("palabras.txt", "r");
    if (!f) {
        perror("Error al abrir palabras.txt");
        return;
    }
    char buf[MAX_L];
    while (fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\r\n")] = '\0';

        // tokeniza la línea en palabras separadas por espacios/tab
        char *token = strtok(buf, " \t");
        while (token != NULL) {
            int len = strlen(token);
            if      (len <= 5  && nE < MAX_PAL) strcpy(easy[nE++],   token);
            else if (len == 6  && nM < MAX_PAL) strcpy(medium[nM++], token);
            else if (len >  6  && nH < MAX_PAL) strcpy(hard[nH++],   token);

            token = strtok(NULL, " \t");
        }
    }
    fclose(f);

    char (*lista)[MAX_L];
    int total, intentos;
    const char *nivelStr;
    switch (nivel) {
      case AH_FACIL:
        lista   = easy;  total = nE; intentos = 10; nivelStr = "Fácil";  break;
      case AH_MEDIO:
        lista   = medium;total = nM; intentos = 7;  nivelStr = "Medio";  break;
      case AH_DIFICIL:
        lista   = hard;  total = nH; intentos = 5;  nivelStr = "Difícil";break;
      default:
        printf("Nivel inválido.\n");
        return;
    }
    if (total == 0) {
        printf("No hay palabras para nivel %s.\n", nivelStr);
        return;
    }

    srand((unsigned)time(NULL));
    int idx = rand() % total;
    char palabraSecreta[MAX_L];
    strcpy(palabraSecreta, lista[idx]);
    int longitud = strlen(palabraSecreta);
 
    char letras[MAX_L] = "";  // historial de letras
    int aciertos = 0;
    char letra;

    printf("\n=== Ahorcado (Nivel %s) ===\n", nivelStr);
    while (intentos > 0 && aciertos < longitud) {
        // mostrar estado
        printf("\nPalabra: ");
        for (int i = 0; i < longitud; i++) {
            printf("%c ", strchr(letras, palabraSecreta[i]) ? palabraSecreta[i] : '_');
        }
        printf("\nIntentos restantes: %d\n", intentos);

        // leer intento
        printf("Ingrese una letra: ");
        scanf(" %c", &letra);
        letra = tolower(letra);
        if (strchr(letras, letra)) {
            printf("Ya probaste '%c'.\n", letra);
            continue;
        }
        strncat(letras, &letra, 1);

        // comprobar
        int ok = 0;
        for (int i = 0; i < longitud; i++) {
            if (palabraSecreta[i] == letra) {
                aciertos++;
                ok = 1;
            }
        }
        if (!ok) {
            printf("'%c' no está en la palabra.\n", letra);
            intentos--;
        } else {
            printf("¡Bien! La letra '%c' es correcta.\n", letra);
        }
    }

    if (aciertos == longitud)
        printf("\n¡Ganaste! La palabra era \"%s\".\n", palabraSecreta);
    else
        printf("\nPerdiste. La palabra era \"%s\".\n", palabraSecreta);

    guardarHistorialAhorcado(user.nombre, palabraSecreta, aciertos, intentos);

    #undef MAX_PAL
    #undef MAX_L

}

