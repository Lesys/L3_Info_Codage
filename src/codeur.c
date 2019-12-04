#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include <codeur.h>
#include <binaire_formate.h>

void msg_code_detruire(msg_code_t msg) {
    if (msg.type >= HDBN2 && msg.type <= HDBN4) {
        free(msg.u.hdbn.tab);
    }
}

dictionnaire_t dictionnaire_creer(int nb_symboles, ...) {
    dictionnaire_t dic;
    dic.nb_symboles = nb_symboles;
    dic.symboles = malloc(sizeof(bf_t) * nb_symboles);
    dic.bornes_basses = malloc(sizeof(double) * nb_symboles);
    dic.bornes_hautes = malloc(sizeof(double) * nb_symboles);

    char * symbole;

    va_list valist;
    va_start(valist, nb_symboles);

    for (int i = 0; i < nb_symboles; i++) {
        symbole = va_arg(valist, bf_t);
        dic.symboles[i] = malloc(strlen(symbole) + 1);
        strcpy(dic.symboles[i], symbole);
        dic.bornes_basses[i] = va_arg(valist, double);
        dic.bornes_hautes[i] = va_arg(valist, double);
    }

    va_end(valist);

    return dic;
}

void dictionnaire_afficher(dictionnaire_t dic) {
    for (int i = 0; i < dic.nb_symboles; i++) {
        printf("%s - [%lf;%lf]\n", dic.symboles[i], dic.bornes_basses[i], dic.bornes_hautes[i]);
    }
}

static int n_zeros(bf_t data, int n) {
    int i;
    for (i = 0; i < n && data[i]; i++) {
        if (data[i] == '1') {
            return 0;
        }
    }

    return i == n;
}

static int codeur_hdbn(bf_t data, msg_code_t * res, int n) {
    int last_1 = -1;
    int viol = -1;
    res->type = n;
    res->u.hdbn.taille = strlen(data);
    res->u.hdbn.tab = malloc(res->u.hdbn.taille);
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '1') {
            last_1 *= -1;
            res->u.hdbn.tab[i] = last_1;
        }
        else if (data[i] == '0') {
            if (n_zeros(data + i, n+1)) {
                if ((viol == -1 && last_1 == 1) || (viol == 1 && last_1 == -1)) {
                    res->u.hdbn.tab[i] = 0;
                }
                else {
                    res->u.hdbn.tab[i] = viol * -1;
                    last_1 = res->u.hdbn.tab[i];
                }
                i++;

                for (int j = 0; j < n-1; j++) {
                    res->u.hdbn.tab[i] = 0;
                    i++;
                }

                res->u.hdbn.tab[i] = viol * -1;


                viol *= -1;
            }
            else {
                res->u.hdbn.tab[i] = 0;
            }
        }
        else {
            return 0;
        }
    }

    return 1;
}

static int dictionnaire_chercher(bf_t data, int taille_symbole, dictionnaire_t dic) {
    for (int i = 0; i < dic.nb_symboles; i++) {
        if (!memcmp(data, dic.symboles[i], taille_symbole)) {
            return i;
        }
    }

    return -1;
}

static int codeur_arithmetique(bf_t data, msg_code_t * res, dictionnaire_t dic) {
    res->type = 1;
    res->u.artm.dic = dic;
    int taille_symbole = strlen(dic.symboles[0]);
    int taille_data = strlen(data);
    int nb_symboles = taille_data / taille_symbole;
    res->u.artm.nb_codes = (nb_symboles % N_PAR_CODE == 0 ? nb_symboles / N_PAR_CODE : nb_symboles / N_PAR_CODE + 1);
    res->u.artm.codes = malloc(sizeof(double) * res->u.artm.nb_codes);

    int n_code = 0;
    int ind = 0;
    int ind_sym;

    double borne_sup = 1;
    double borne_inf = 0;
    double bb;

    for (int i = 0; i < nb_symboles; i++) {
        if (n_code == N_PAR_CODE) {
            res->u.artm.codes[ind] = borne_inf + (borne_sup - borne_inf)/2;
            n_code = 0;
            ind++;
            borne_sup = 1;
            borne_inf = 0;
        }

        ind_sym = dictionnaire_chercher(data + (i * taille_symbole), taille_symbole, dic);
        if (ind_sym == -1) {
            return 0;
        }

        bb = borne_sup - borne_inf;
        borne_sup = borne_inf + (bb * dic.bornes_hautes[ind_sym]);
        borne_inf = borne_inf + (bb * dic.bornes_basses[ind_sym]);

        n_code++;
    }

    if (n_code != N_PAR_CODE) {
        res->u.artm.codes[ind] = borne_inf + (borne_sup - borne_inf)/2;
        res->u.artm.nb_sym_dernier_code = n_code;
    }
    else {
        res->u.artm.nb_sym_dernier_code = 0;
    }

    printf("%d\n", res->u.artm.nb_sym_dernier_code);

    return 1;
}

int codeur(int encoder_type, bf_t data, msg_code_t * res, ...) {
    va_list valist;
    switch (encoder_type) {
        case 1:
            va_start(valist, res);
            return codeur_arithmetique(data, res, va_arg(valist, dictionnaire_t));
            va_end(valist);
            break;
        case 2:
        case 3:
        case 4:
            codeur_hdbn(data, res, encoder_type);
            break;
    }

    return 0;
}

static bf_t decodeur_hdbn(msg_code_t data) {
    bf_t res = malloc(data.u.hdbn.taille + 1);

    int last_1 = -1;

    for (int i = 0; i < data.u.hdbn.taille; i++) {
        if (data.u.hdbn.tab[i] == 0) {
            res[i] = '0';
        }
        else {
            if (data.u.hdbn.tab[i] == last_1) {
                for (int j = 0; j <= data.type; j++) {
                    res[i - j] = '0';
                }
            }
            else {
                res[i] = '1';
            }
            last_1 = data.u.hdbn.tab[i];
        }
    }
    res[data.u.hdbn.taille] = '\0';
    return res;
}

static int dictionnaire_chercher_valeur(double val, dictionnaire_t dic) {
    for (int i = 0; i < dic.nb_symboles; i++) {
        if (val >= dic.bornes_basses[i] && val < dic.bornes_hautes[i]) {
            return i;
        }
    }

    return -1;
}

static bf_t decodeur_arithmetique(msg_code_t data) {
    dictionnaire_t dic = data.u.artm.dic;
    int taille_symbole = strlen(dic.symboles[0]);
    int nb_symboles = (data.u.artm.nb_codes - (data.u.artm.nb_sym_dernier_code == 0 ? 0 : 1)) * N_PAR_CODE + data.u.artm.nb_sym_dernier_code;
    bf_t res = malloc(nb_symboles * taille_symbole + 1);

    int n_decode = 0;
    int ind = 0;
    int ind_sym;
    
    for (int i = 0; i < nb_symboles; i++) {
        if (n_decode == N_PAR_CODE) {
            n_decode = 0;
            ind++;
        }

        ind_sym = dictionnaire_chercher_valeur(data.u.artm.codes[ind], dic);
        if (ind_sym == -1) {
            free(res);
            return NULL;
        }
        strcpy(res + (i * taille_symbole), dic.symboles[ind_sym]);
        data.u.artm.codes[ind] = (data.u.artm.codes[ind] - dic.bornes_basses[ind_sym]) / (dic.bornes_hautes[ind_sym] - dic.bornes_basses[ind_sym]);
    }

    res[nb_symboles * taille_symbole] = '\0';

    return res;
}

bf_t decodeur(msg_code_t data) {
    switch (data.type) {
        case 1:
            return decodeur_arithmetique(data);
            break;
        case 2:
        case 3:
        case 4:
            return decodeur_hdbn(data);
            break;
    }

    return NULL;
}
