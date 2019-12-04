#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <codeur.h>
#include <binaire_formate.h>

// Test codage arithmétique avec exemple provenant de https://fr.wikipedia.org/wiki/Codage_arithm%C3%A9tique

int main() {
    // Création du dictionnaire
    printf("Dictionnaire :\n");
    bf_t w = transformer_donnee_bit("w", 1);
    bf_t i = transformer_donnee_bit("i", 1);
    bf_t k = transformer_donnee_bit("k", 1);
    dictionnaire_t dic = dictionnaire_creer(3, 10, w, 0.0, 0.25, i, 0.25, 0.75, k, 0.75, 1.0);
    free(w), free(i), free(k);
    dictionnaire_afficher(dic);

    // Encodage
    printf("\nChaine à coder : %s\n", "wiki");
    msg_code_t code;
    bf_t data = transformer_donnee_bit("wiki", 4);
    if (!codeur(1, data, &code, dic)) {
        fprintf(stderr, "Erreur codeur\n");
        exit(-1);
    }
    free(data);
    printf("Valeur codée : %lf\n", code.u.artm.codes[0]);

    // Decodage
    bf_t data_decode = decodeur(code);
    if (data_decode == NULL) {
        fprintf(stderr, "Erreur decodeur\n");
        exit(-1);
    }
    char * str = transformer_bit_donnee(data_decode);
    msg_code_detruire(code);
    free(data_decode);
    dictionnaire_detruire(dic);
    // !!! LE \0 N'EST NI ENCODE NI DECODE
    str = realloc(str, 5);
    str[4] = '\0';
    printf("Chaine décodé : %s\n", str);
    assert(!strcmp("wiki", str));

    free(str);
}
