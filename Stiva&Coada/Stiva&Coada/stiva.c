#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;

//coada si stiva seamana cu lista simpla ca si structura
struct Angajat
{
	long id;
	char* nume;
	int varsta;
};

struct Nod
{
	Angajat info;
	Nod* next;
};

void afiasreAngajat(Angajat angajat) {
	printf("\nAngajatul cu id ul %ld se numeste %s si are %d ani.", angajat.id, angajat.nume, angajat.varsta);
}

Angajat initializareAngajat(long id, const char* nume, int varsta) {
	Angajat angajat;
	angajat.id = id;
	angajat.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(angajat.nume, nume);
	angajat.varsta = varsta;

	return angajat;
}

void push(Nod** cap, Angajat info) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = info;
	nou->next = *cap;
	*cap = nou;
}

Angajat pop(Nod** varf) {
	Angajat angajat;
	angajat.id = -1;
	angajat.varsta = -1;
	angajat.nume = NULL;

	if (*varf) {
		angajat = (*varf)->info;
		Nod* copie = *varf;
		(*varf) = (*varf)->next;
		free(copie);
	}
	return angajat;
}

Angajat cautaDupaId(Nod** stiva, long id) {
	Angajat angajat;
	angajat.id = -1;
	angajat.varsta = -1;
	angajat.nume = NULL;
	Nod* stivaAuxiliara = NULL;

	while ((*stiva)!=NULL && id!=(*stiva)->info.id)
	{
		push(&stivaAuxiliara, pop(stiva));
	}
	if (*stiva) {
		angajat = pop(stiva);
	}

	while (stivaAuxiliara)
	{
		push(stiva, pop(&stivaAuxiliara));
	}

	return angajat;
}
Angajat* stivaToVector(Nod* stiva, int* dimensiune) {
	*dimensiune = 0;
	Nod* temp = stiva;

	while (temp) {
		(*dimensiune)++;
		temp = temp->next;
	}

	Angajat* vector = (Angajat*)malloc(sizeof(Angajat) * (*dimensiune));

	for (int i = 0; i < *dimensiune; i++) {
		vector[i] = pop(&stiva);
	}

	return vector;
}

void citireDinFisier(const char* numeFisier, Nod** stiva) {
	FILE* fisier = fopen(numeFisier, "r");
	if (!fisier) {
		printf("Eroare la deschiderea fisierului!");
		return;
	}

	long id;
	char nume[50];
	int varsta;

	while (fscanf(fisier, "%ld %s %d", &id, nume, &varsta) != EOF) {
		push(stiva, initializareAngajat(id, nume, varsta));
	}

	fclose(fisier);
}

int main() {
	Nod* stiva = NULL;
	Angajat angajat;
	int dimensiune;

	citireDinFisier("angajati.txt", &stiva);

	Angajat angajatCautat = cautaDupaId(&stiva, 5);
	afiasreAngajat(angajatCautat);
	free(angajatCautat.nume);

	printf("\nStiva:\n");
	while (stiva) {
		angajat = pop(&stiva);
		afiasreAngajat(angajat);
		free(angajat.nume);
	}

	push(&stiva, initializareAngajat(1, "Mihai", 30));
	push(&stiva, initializareAngajat(2, "Andrei", 28));
	push(&stiva, initializareAngajat(3, "Ana", 29));
	push(&stiva, initializareAngajat(4, "Ana", 29));
	// Conversia stivei în vector
	Angajat* vector = stivaToVector(stiva, &dimensiune);
	printf("\nVector:\n");
	for (int i = 0; i < dimensiune; i++) {
		afiasreAngajat(vector[i]);
		free(vector[i].nume);
	}
	free(vector);

	return 0;
}
