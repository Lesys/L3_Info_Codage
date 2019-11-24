#ifndef ETALEMENT_H
#define ETALEMENT_H

#include "../include/matrice.h"

typedef struct msg_etale_s {
    char * sequences;
    int taille_sequence;
    int nb_sequences;
} msg_etale_t;

void msg_etale_afficher(msg_etale_t m);

msg_etale_t msg_etale_ajouter(msg_etale_t a, msg_etale_t b);

void msg_etale_detruire(msg_etale_t m);

msg_etale_t etalement(char * bits, matrice_t hadamard, int num_utilisateur);

char * desetalement(msg_etale_t m, matrice_t hadamard, int num_utilisateur);

#endif