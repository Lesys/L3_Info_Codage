#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "../include/codeur.h"
#include "../include/binaire_formate.h"

int main() {
    bf_t msg = malloc(51);
    msg[50] = '\0';
    msg_code_t code;
    bf_t decode;

    srand(time(NULL));

    for (int i = 0; i < 100000;  i++) {

        // Génération message aléatoire
        for (int j = 0; j < 50; j++) {
            msg[j] = rand() % 2 + '0';
        }

        // Test hdb2
        codeur(2, msg, &code);
        decode = decodeur(code);
        assert(strcmp(msg, decode) == 0);
        free(decode);
        msg_code_detruire(code);

        // Test hdb3
        codeur(3, msg, &code);
        decode = decodeur(code);
        assert(strcmp(msg, decode) == 0);
        free(decode);
        msg_code_detruire(code);

        // Test hdb4
        codeur(4, msg, &code);
        decode = decodeur(code);
        assert(strcmp(msg, decode) == 0);
        free(decode);
        msg_code_detruire(code);
    }
}
