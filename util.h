#ifndef UTILES_H_
#define UTILES_H_
#include "usuarios.h" 

char* leerProxPalabra(const char* fichero);
void guardarHistorialAhorcado(const char *usuario,const char* palabraSecreta, int aciertos, int intentosRestantes);
void guardarHistorialCodigo(const char *usuario,int codigoSecreto[4], int exito, int intentosUsados);
void mostrarHistorial(Usuario user);
int leer_entero(const char *prompt, int min, int max);
void leer_cadena(const char *prompt, char *buf, size_t len);
void mostrarMenu(const char *titulo, const char *ops[], int n);

#endif