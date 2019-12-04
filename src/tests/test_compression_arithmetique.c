#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <codeur.h>
#include <binaire_formate.h>

// test compression du texte src/tests/test_compression_arithmetique.txt

int main() {
    // Récupération du fichier en chaines de caractères
    FILE * fp;
    long lSize;
    char * fichier_source;

    fp = fopen ("../src/tests/test_compression_arithmetique.txt", "r");
    if (!fp) {
        perror("../src/tests/test_compression_arithmetique.txt");
        exit(-1);
    }
    fseek(fp , 0L , SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    fichier_source = malloc(lSize+1);
    fread(fichier_source, lSize, 1 , fp);
    fclose(fp);

    // Récupération du nombre d'apparitions
    int occ[128] = {0};
    long nb_char = strlen(fichier_source);
    for (int i = 0; i < nb_char; i++) {
        occ[fichier_source[i]]++;
    }

    // Création du dictionnaire (sans utiliser dictionnaire_creer() pour simplifier)
    dictionnaire_t dic;
    dic.nb_symboles = 0;
    dic.symboles = malloc(sizeof(bf_t) * nb_char);
    dic.bornes_basses = malloc(sizeof(double) * nb_char);
    dic.bornes_hautes = malloc(sizeof(double) * nb_char);
    double freq;
    double borne = 0;
    for (int i = 0; i < 128; i++) {
        if (occ[i]) {
            freq = (double)occ[i] / (double)nb_char;
            dic.symboles[dic.nb_symboles] = transformer_donnee_bit(&i, 1);
            dic.bornes_basses[dic.nb_symboles] = borne;
            borne += freq;
            dic.bornes_hautes[dic.nb_symboles] = borne;
            dic.nb_symboles++;
        }
    }
    dic.symboles = realloc(dic.symboles, sizeof(bf_t) * dic.nb_symboles);
    dic.bornes_basses = realloc(dic.bornes_basses, sizeof(double) * dic.nb_symboles);
    dic.bornes_hautes = realloc(dic.bornes_hautes, sizeof(double) * dic.nb_symboles);

    // Transformation du fichier
    bf_t fichier_source_f = transformer_donnee_bit(fichier_source, nb_char);

    // Compression
    msg_code_t code;
    if (!codeur(1, fichier_source_f, &code, dic)) {
        fprintf(stderr, "Erreur codeur\n");
        exit(-1);
    }

    // Decompression
    bf_t fichier_decode_f = decodeur(code);
    if (fichier_decode_f == NULL) {
        fprintf(stderr, "Erreur decodeur\n");
        exit(-1);
    }
    char * fichier_decode = transformer_bit_donnee(fichier_decode_f);

    // !!! LE \0 N'EST NI ENCODE NI DECODE
    fichier_decode = realloc(fichier_decode, nb_char + 1);
    fichier_decode[nb_char] = '\0';

    if (memcmp(fichier_source, fichier_decode, nb_char)) {
        printf("source != decode, vérifier la constante N_PAR_CODE\n");
        assert(0);
    }
    else {
        printf("Dictionnaire généré : \n");
        dictionnaire_afficher(dic);
        printf("\nTaille fichier source : %ld octets\n", nb_char);
        printf("Taille ficher compresse : ~%ld octets + taille dictionnaire\n", (nb_char % N_PAR_CODE == 0 ? nb_char / N_PAR_CODE : nb_char / N_PAR_CODE + 1) * 4);
    }
}
