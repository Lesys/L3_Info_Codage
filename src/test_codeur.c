#include <stdio.h>
#include <stdlib.h>

#include "../include/codeur.h"

int main() {
    msg_code_t code;
    char * decode;
    printf("10010100000011000011100\n");
    codeur(2, "10010100000011000011100", &code);
    for (int i = 0; i < code.taille; i++) {
        printf(" %3d ", code.tab[i]);
    }
    printf("\n");
    decode = decodeur(code);
    printf("%s\n", decode);
}
