#ifndef CODEUR_H
#define CODEUR_H

typedef struct msg_code_s {
    int type;
    char * tab;
    int taille;
} msg_code_t;

/*
typedef struct msg_code_hdbn_s {
    char * tab;
    int taille;
}

typedef struct msg_code_arithmetique_s {
    long probas[256];
    double code;
}

typedef struct msg_code_s {
    int type;
    char * tab;
    int taille;
} msg_code_t;
*/

int codeur(int encoder_type, char * data, msg_code_t * res);

char * decodeur(msg_code_t data);

#endif
