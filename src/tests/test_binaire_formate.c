#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <binaire_formate.h>

int main() {
	char * str = "abcdefg";
	bf_t bf = transformer_donnee_bit(str, strlen(str));
	char * str_r = transformer_bit_donnee(bf);
	assert(!strcmp(str, str_r));
	free(str_r);
	free(bf);

	int int_tab[7] = {1, 2, 3, 4, 150, 845236, 5};
	bf = transformer_donnee_bit(int_tab, sizeof(int) * 7);
	int * int_tab_r = transformer_bit_donnee(bf);
	assert(!memcmp(int_tab, int_tab_r, sizeof(int) * 7));
	free(int_tab_r);
	free(bf);
}
