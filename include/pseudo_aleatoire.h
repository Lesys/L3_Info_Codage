#include "matrice.h"

#ifndef PSEUDO_ALEATOIRE_H
#define PSEUDO_ALEATOIRE_H

#define XOR(x, y) x == y ? 0 : 1

matrice_t code_longueur_max(matrice_t seq_initiale, matrice_t seq_xor, int longueur);

#endif