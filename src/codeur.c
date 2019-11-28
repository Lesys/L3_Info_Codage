#include <stdio.h>
#include <stdlib.h>

static int codeur_hdbn(char * data, char * res, int n) {
    printf("%d\n", n);
}

static int codeur_arithmetique() {

}

int codeur(int encoder_type, char * data, char * res) {
    switch (encoder_type) {
        case 1:
            return codeur_arithmetique();
            break;
        case 2:
        case 3:
        case 4:
            codeur_hdbn(data, res, encoder_type);
            break;
        default:
            return 0;
            break;
    }
}
