#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/codeur.h"

void msg_code_detruire(msg_code_t msg) {
    if (msg.tab) {
        free(msg.tab);
    }
}

static int n_zeros(char * data, int n) {
    int i;
    for (i = 0; i < n && data[i]; i++) {
        if (data[i] == '1') {
            return 0;
        }
    }

    return i == n;
}

static int codeur_hdbn(char * data, msg_code_t * res, int n) {
    int last_1 = -1;
    int viol = -1;
    res->type = n;
    res->taille = strlen(data);
    res->tab = malloc(res->taille);
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '1') {
            last_1 *= -1;
            res->tab[i] = last_1;
        }
        else if (data[i] == '0') {
            if (n_zeros(data + i, n+1)) {
                if ((viol == -1 && last_1 == 1) || (viol == 1 && last_1 == -1)) {
                    res->tab[i] = 0;
                }
                else {
                    res->tab[i] = viol * -1;
                    last_1 = res->tab[i];
                }
                i++;

                for (int j = 0; j < n-1; j++) {
                    res->tab[i] = 0;
                    i++;
                }

                res->tab[i] = viol * -1;


                viol *= -1;
            }
            else {
                res->tab[i] = 0;
            }
        }
        else {
            return 0;
        }
    }

    return 1;
}

static int codeur_arithmetique() {
    return 1;
}

int codeur(int encoder_type, char * data, msg_code_t * res) {
    switch (encoder_type) {
        case 1:
            return codeur_arithmetique();
            break;
        case 2:
        case 3:
        case 4:
            codeur_hdbn(data, res, encoder_type);
            break;
    }

    return 0;
}

static char * decodeur_hdbn(msg_code_t data) {
    char * res = malloc(data.taille + 1);

    int last_1 = -1;

    for (int i = 0; i < data.taille; i++) {
        if (data.tab[i] == 0) {
            res[i] = '0';
        }
        else {
            if (data.tab[i] == last_1) {
                for (int j = 0; j <= data.type; j++) {
                    res[i - j] = '0';
                }
            }
            else {
                res[i] = '1';
            }
            last_1 = data.tab[i];
        }
    }
    res[data.taille] = '\0';
    return res;
}

static char * decodeur_arithmetique() {
    return NULL;
}

char * decodeur(msg_code_t data) {
    switch (data.type) {
        case 1:
            return decodeur_arithmetique();
            break;
        case 2:
        case 3:
        case 4:
            return decodeur_hdbn(data);
            break;
    }

    return NULL;
}
