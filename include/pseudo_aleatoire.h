#ifndef PSEUDO_ALEATOIRE_H
#define PSEUDO_ALEATOIRE_H

#include "matrice.h"

#define XOR(x, y) x == y ? 0 : 1

matrice_t code_gold(matrice_t seq_initiale1, matrice_t seq_xor1, matrice_t seq_initiale2, matrice_t seq_xor2, int longueur);

matrice_t code_longueur_max(matrice_t seq_initiale, matrice_t seq_xor, int longueur);

#endif
