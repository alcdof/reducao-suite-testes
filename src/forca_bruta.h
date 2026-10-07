#ifndef FORCA_BRUTA_H
#define FORCA_BRUTA_H

#include "tipos.h"

int verifica_possibilidade(const Matriz *mat);
int forca_bruta(const Matriz *mat, int escolhidos[]);

#endif