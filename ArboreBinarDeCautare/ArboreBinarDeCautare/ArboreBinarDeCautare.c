#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Brutarie Brutarie;
typedef struct Nod Nod;

struct Brutarie
{
	char* nume;
	int id;
	int nrAngajati;
};

struct Nod
{
	Brutarie info;
	Nod* stanga;
	Nod* dreapta;
};

Brutarie initializareBrutarie(const char* nume, int id, int nrAngajati) {
	Brutarie b;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.id = id;
	b.nrAngajati = nrAngajati;

	return b;
}

void inserareNod(Brutarie b, Nod** radacina) {
	if (*radacina) {
		if ((*radacina)->info.id > b.id) {
			inserareNod(b, &(*radacina)->stanga);
		}
		else
		{
			inserareNod(b, &(*radacina)->dreapta);
		}
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = b;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
}

void afisareBrutarie(Brutarie b) {
	printf("\nBrutaria cu numele %s are id ul %d si %d angajati.",b.nume,b.id,b.nrAngajati);
}

void afisarePreordine(Nod* radacina) {
	if (radacina) {
		afisareBrutarie(radacina->info);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);
	}
}
afisareInOrdine(Nod* radacina) {
	if (radacina) {
		afisareInOrdine(radacina->stanga);
		afisareBrutarie(radacina->info);
		afisarePreordine(radacina->dreapta);
	}
}

int determinareInaltime(Nod* radacina) {
	if (radacina) {
		int stangaH = determinareInaltime(radacina->stanga);
		int dreaptaH = determinareInaltime(radacina->dreapta);
		return 1 + (stangaH > dreaptaH ? stangaH : dreaptaH);
	}
	else
	{
		return 0;
	}
}

void stergereArbore(Nod** radacina) {
	if (*radacina) {
		stergereArbore(&(*radacina)->stanga);
		stergereArbore(&(*radacina)->dreapta);
		free((*radacina)->info.nume);
		free(*radacina);
		*radacina = NULL;
	}
}

Brutarie cautareBrutarie(Nod* radacina, int id) {
	if (radacina) {
		if (id < radacina->info.id) {
			return cautareBrutarie(radacina->stanga, id);
		}
		else
		{
			if (id > radacina->info.id) {
				return cautareBrutarie(radacina->dreapta, id);
			}
			else
			{
				return initializareBrutarie(radacina->info.nume, radacina->info.id, radacina->info.nrAngajati);
			}
		}
	}
	else
	{
		return initializareBrutarie("", 0, 0);
	}
}

int calculNrTotalAngajati(Nod* radacina) {
	if (radacina) {
		return radacina->info.nrAngajati
			+ calculNrTotalAngajati(radacina->stanga)
			+ calculNrTotalAngajati(radacina->dreapta);
	}
	else
	{
		return 0;
	}
}

void citireDateDinFisier(const char* numeFisier, Nod** radacina) {
	FILE* fisier = fopen(numeFisier, "r");
	if (!fisier) {
		printf("Eroare la deschiderea fisierului!\n");
		return;
	}

	char nume[50];
	int id, nrAngajati;

	while (fscanf(fisier, "%s %d %d", nume, &id, &nrAngajati) == 3) {
		Brutarie b = initializareBrutarie(nume, id, nrAngajati);
		inserareNod(b, radacina);
	}

	fclose(fisier);
}

void main(){

	Nod* radacina = NULL;

		//inserareNod(initializareBrutarie("LaCostel", 6, 15), &radacina);
		//inserareNod(initializareBrutarie("LaMarcel", 2, 4), &radacina);
		//inserareNod(initializareBrutarie("LaFlorica", 8, 3), &radacina);
		//inserareNod(initializareBrutarie("LaAlex", 4, 9), &radacina);
		//inserareNod(initializareBrutarie("LaSilviu", 7, 7), &radacina);
		//inserareNod(initializareBrutarie("LaMaria", 9, 12), &radacina);
		//inserareNod(initializareBrutarie("LaMama", 10, 7), &radacina);
		//inserareNod(initializareBrutarie("LaCrina", 11, 12), &radacina);

	citireDateDinFisier("date.txt",&radacina);

		afisareInOrdine(radacina);
		printf("\n====================================\n");
		afisarePreordine(radacina);

		Brutarie cautare = cautareBrutarie(radacina, 4);
		printf("\n");
		afisareBrutarie(cautare);

		int sumaTotala = calculNrTotalAngajati(radacina);

		printf("\nNumarul total de angajati este: %d ", sumaTotala);

		printf("\nInaltimea este: %d\n", determinareInaltime(radacina));

		stergereArbore(&radacina);
		free(cautare.nume);
}