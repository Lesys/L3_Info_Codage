#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/codeur.h"
#include "../include/binaire_formate.h"

int main() {
    bf_t w = transformer_donnee_bit("w", 1);
    bf_t i = transformer_donnee_bit("i", 1);
    bf_t k = transformer_donnee_bit("k", 1);
    dictionnaire_t dic = dictionnaire_creer(3, w, 0.0, 0.25, i, 0.25, 0.75, k, 0.75, 1.0);
    msg_code_t code;
    bf_t data = transformer_donnee_bit("wiki", 4);
    if (!codeur(1, data, &code, dic)) {
        fprintf(stderr, "Erreur codeur\n");
        exit(-1);
    }
    dictionnaire_afficher(code.u.artm.dic);
    bf_t data_decode = decodeur(code);
    if (data_decode == NULL) {
        fprintf(stderr, "Erreur decodeur\n");
        exit(-1);
    }
    char * str = transformer_bit_donnee(data_decode);
    // !!! LE \0 N'EST NI ENCODE NI DECODE
    str = realloc(str, 5);
    str[4] = '\0';
    printf("%s\n", str);
}