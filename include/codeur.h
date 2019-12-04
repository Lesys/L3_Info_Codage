#ifndef CODEUR_H
#define CODEUR_H

#include "../include/binaire_formate.h"

// Nombre de symboles par code (codage arithmétique)
#define N_PAR_CODE 7

#define ARITHMETIQUE 1
#define HDBN2 2
#define HDBN3 3
#define HDBN4 4

typedef struct dictionnaire_s {
    int nb_symboles;
    char ** symboles;
    double * bornes_basses;
    double * bornes_hautes;
} dictionnaire_t;

typedef struct msg_code_s {
    int type;
    union {
        struct {
            char * tab;
            int taille;
        } hdbn;
        struct {
            dictionnaire_t dic;
            double * codes;
            int nb_codes;
            int nb_sym_dernier_code;
        } artm;
    } u;
} msg_code_t;

void msg_code_detruire(msg_code_t msg);

dictionnaire_t dictionnaire_creer(int nb_symboles, ...);

void dictionnaire_afficher(dictionnaire_t dic);

int codeur(int encoder_type, bf_t data, msg_code_t * res, ...);

bf_t decodeur(msg_code_t data);

#endif
