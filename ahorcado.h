#ifndef AHORCADO_H
#define AHORCADO_H
#include "usuarios.h"
void jugarAhorcado(Usuario user);
typedef enum { AH_FACIL = 1, AH_MEDIO, AH_DIFICIL } NivelAhorcado;
void iniciarAhorcadoConNivel(NivelAhorcado nivel, Usuario user);

#endif
