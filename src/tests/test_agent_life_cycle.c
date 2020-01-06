#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#include <binaire_formate.h>
#include <etalement.h>
#include <hadamard.h>
#include <agent_life_cycle.h>
#include <codeur.h>



pthread_t pid[3];

typedef struct io_emetteur_etalement_s {
	int entree_canal;
	int num_utilisateur;
} io_emetteur_etalement_t;

typedef struct io_recepteur_etalement_s {
	int sortie_canal;
	int num_utilisateur;
} io_recepteur_etalement_t;

typedef struct io_canal_etalement_s {
	int entrees[4];
	int sorties[4];
} io_canal_etalement_t;

typedef struct io_emetteur_hdbn_s {
	int entree_canal;
} io_emetteur_hdbn_t;

typedef struct io_recepteur_hdbn_s {
	int sortie_canal;
} io_recepteur_hdbn_t;

typedef struct io_canal_hdbn_s {
	int entree;
	int sortie;
} io_canal_hdbn_t;

void * emetteur_etalement(void * args) {
	wait2(pthread_self());

	io_emetteur_etalement_t * io = args;
	int taille;
	char buffer[11];
	bf_t data;
	msg_etale_t data_etale;

	matrice_t hadamard;
	hadamard_matrice(2, &hadamard);

	while (1) {
		taille = rand() % 10 + 1;
		for (int i = 0; i < taille; i++) {
			buffer[i] = rand()%26 + 'a';
		}
		buffer[taille] = '\0';
		printf("Emetteur %d : %s\n", io->num_utilisateur + 1, buffer);
		data = transformer_donnee_bit(buffer, taille);
		data_etale = etalement(data, hadamard, io->num_utilisateur);
		write(io->entree_canal, &data_etale.nb_sequences, sizeof(int));
		write(io->entree_canal, data_etale.sequences, data_etale.nb_sequences * data_etale.taille_sequence);
		msg_etale_detruire(&data_etale);
		free(data);
		sleep(rand()%2+1);
	}
}

void * canal_etalement(void * args) {
	wait2(pthread_self());

	io_canal_etalement_t * io = args;
	msg_etale_t m[4];
	msg_etale_t tmp, res;
	int taille;

	tmp.sequences = NULL;
	res.sequences = NULL;

	while (1) {
		sleep(1);
		for (int i = 0; i < 4; i++) {
			m[i].sequences = NULL;
			m[i].taille_sequence = 4;
			m[i].nb_sequences = 0;
		}
		// Récupération des différents messages
		for (int i = 0; i < 4; i++) {
			if (read(io->entrees[i], &(m[i].nb_sequences), sizeof(int)) > 0) {
				taille = m[i].nb_sequences * m[i].taille_sequence;
				m[i].sequences = malloc(taille);
				read(io->entrees[i], m[i].sequences, taille);
			}
		}

		// Addition
		res = m[0];
		for (int i = 1; i < 4; i++) {
			tmp = msg_etale_ajouter(res, m[i]);
			msg_etale_detruire(&res);
			msg_etale_detruire(&m[i]);
			res = tmp;
		}

		for (int i = 0; i < 4; i++) {
			write(io->sorties[i], &res.nb_sequences, sizeof(int));
			write(io->sorties[i], res.sequences, res.nb_sequences * res.taille_sequence);
		}

		msg_etale_detruire(&res);
	}
}


void * recepteur_etalement(void * args) {
	wait2(pthread_self());

	io_recepteur_etalement_t * io = args;
	msg_etale_t m;
	m.taille_sequence = 4;
	char * buffer;
	bf_t data;

	matrice_t hadamard;
	hadamard_matrice(2, &hadamard);

	while (1) {
		if (read(io->sortie_canal, &(m.nb_sequences), sizeof(int)) > 0) {
			int taille = m.nb_sequences * m.taille_sequence;
			if (taille) {
				m.sequences = malloc(taille);
				read(io->sortie_canal, m.sequences, taille);
				data = desetalement(m, hadamard, io->num_utilisateur);
				buffer = transformer_bit_donnee(data);
				if (*buffer != '\0') {
					printf("Recepteur %d : %s\n", io->num_utilisateur + 1, buffer);
					msg_etale_detruire(&m);
				}
				free(data);
				free(buffer);
			}
		}
	}
}

void * emetteur_hdbn(void * args) {
	wait2(pthread_self());

	io_emetteur_hdbn_t * io = args;

	int taille;
	char buffer[11];
	bf_t data;
//	msg_code_t data_code;

	while (1) {
		taille = rand() % 10 + 1;
		for (int i = 0; i < taille; i++) {
			buffer[i] = rand()%26 + 'a';
		}
		buffer[taille] = '\0';
		printf("Emetteur hdbn : %s\n", buffer);
		data = transformer_donnee_bit(buffer, taille);
		msg_code_t data_code;
		codeur(HDBN4, data, &data_code);
		write(io->entree_canal, &(data_code.u.hdbn.taille), sizeof(int));
		write(io->entree_canal, data_code.u.hdbn.tab, data_code.u.hdbn.taille);
		msg_code_detruire(data_code);
		free(data);
		sleep(rand()%2+1);
	}
}

void * canal_hdbn(void * args) {
	wait2(pthread_self());

	io_canal_hdbn_t * io = args;

	int taille;
	char * tab;

	while (1) {
		read(io->entree, &taille, sizeof(int));
		tab = malloc(taille);
		read(io->entree, tab, taille);
		write(io->sortie, &taille, sizeof(int));
		write(io->sortie, tab, taille);
		free(tab);
	}
}


void * recepteur_hdbn(void * args) {
	wait2(pthread_self());

	io_recepteur_hdbn_t * io = args;

	bf_t bf;
	char * buffer;
	msg_code_t m;
	m.type = HDBN4;

	while (1) {
		read(io->sortie_canal, &(m.u.hdbn.taille), sizeof(int));
		m.u.hdbn.tab = malloc(m.u.hdbn.taille);
		read(io->sortie_canal, m.u.hdbn.tab, m.u.hdbn.taille);
		bf = decodeur(m);
		buffer = transformer_bit_donnee(bf);
		printf("Recepteur hdbn: %s\n", buffer);
		free(bf);
		free(buffer);
		msg_code_detruire(m);
	}
}

int main() {
	signal(SIGUSR1, stop_handler);
	signal(SIGUSR2, continue_handler);

	srand(time(NULL));

	pthread_t tab_thread_rec[4], tab_thread_emt[4];

	int p[10][2];

	for (int i = 0; i < 10; i++) {
		pipe(p[i]);
		// Non bloquant pour les communications entre les agents faisant de l'étalement
		if (i < 8)
			fcntl(p[i][0], F_SETFL, fcntl(p[i][0], F_GETFL) | O_NONBLOCK);
	}

	// Etalement

	io_emetteur_etalement_t io_emetteur_etalement[4];
	io_recepteur_etalement_t io_recepteur_etalement[4];
	io_canal_etalement_t io_canal_etalement;

	for (int i = 0; i < 4; i++) {
		io_emetteur_etalement[i].entree_canal = p[i][1];
		io_emetteur_etalement[i].num_utilisateur = i;

		tab_thread_emt[i] = create(emetteur_etalement, io_emetteur_etalement + i);
		invoke(tab_thread_emt[i]);

		io_recepteur_etalement[i].sortie_canal = p[i+4][0];
		io_recepteur_etalement[i].num_utilisateur = i;

		tab_thread_rec[i] = create(recepteur_etalement, io_recepteur_etalement + i);
		invoke(tab_thread_rec[i]);

		io_canal_etalement.entrees[i] = p[i][0];
		io_canal_etalement.sorties[i] = p[i+4][1];
	}

	pthread_t canal_e = create(canal_etalement, &io_canal_etalement);
	invoke(canal_e);

	// HDBN

	io_emetteur_hdbn_t io_emetteur_hdbn = { .entree_canal = p[8][1] };
	io_canal_hdbn_t io_canal_hdbn = { .entree = p[8][0], .sortie = p[9][1] };
	io_recepteur_hdbn_t io_recepteur_hdbn = { .sortie_canal = p[9][0] };

	pthread_t em_h = create(emetteur_hdbn, &io_emetteur_hdbn);
	pthread_t canal_h = create(canal_hdbn, &io_canal_hdbn);
	pthread_t rec_h = create(recepteur_hdbn, &io_recepteur_hdbn);
	invoke(em_h); invoke(canal_h); invoke(rec_h);

	sleep(1);

	suspend(canal_h);
	fprintf(stderr, "On bloque le canal hdbn\n");
	sleep(3);
	resume(canal_h);
	fprintf(stderr, "On relance le canal hdbn\n");

	suspend(canal_e);
	fprintf(stderr, "On bloque le canal d'etalement\n");
	sleep(3);
	resume(canal_e);
	fprintf(stderr, "On relance le canal d'etalement\n");

	sleep(5);
}
