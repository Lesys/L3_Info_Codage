#ifndef BINAIRE_FORMATE_H
#define BINAIRE_FORMATE_H

typedef char * bf_t;

bf_t transformer_donnee_bit(void * donnee, int taille);

void * transformer_bit_donnee(bf_t bin);

#endif