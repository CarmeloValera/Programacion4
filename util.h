#ifndef UTILES_H_
#define UTILES_H_

char* leerProxPalabra(const char* fichero);
void guardarHistorialAhorcado(const char *usuario,const char* palabraSecreta, int aciertos, int intentosRestantes);
void guardarHistorialCodigo(const char *usuario,int codigoSecreto[4], int exito, int intentosUsados);
void mostrarHistorial(Usuario user);

#endif