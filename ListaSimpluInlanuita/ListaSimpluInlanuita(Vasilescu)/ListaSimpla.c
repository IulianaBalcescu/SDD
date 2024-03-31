#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;

struct Angajat
{
	char* nume;
	int varsta;
};

struct Nod
{
	Angajat info;
	Nod* next;
};

void afisareAngajat(Angajat angajat) {
	printf("\n Angajatul %s are %d ani.", angajat.nume, angajat.varsta);
}

Angajat initializareAngajat(const char* nume, int varsta) {
	Angajat angajat;
	angajat.varsta = varsta;
	angajat.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(angajat.nume, nume);

	return angajat;
}

void parcurgereLista(Nod* cap) {
	while(cap) {
		afisareAngajat(cap->info);
		cap = cap->next;
	}
}

void inserareInceput(Nod** cap, Angajat info) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = info;
	nou->next = *cap;
	*cap = nou;
}

void inserareLaFinal(Nod** cap, Angajat info) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = info;
	nou->next = NULL;

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else
	{
		Nod* temp = *cap;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void dezalocare(Nod** cap) {
	while ((*cap)!=NULL)
	{
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.nume);
		free(temp);
	}
}
// Funcția pentru calculul numărului de apariții a unui nume în listă

int suma(Nod* cap, const char* nume) {
	int suma = 0;

	while (cap)
	{
		if (strcmp(cap->info.nume, nume) == 0)
			suma++;
		cap = cap->next;
	}
	return suma;
}

float calculVarstaMedie(Nod* cap) {
	int contor = 0;
	float medie = 0.0;
	while (cap)
	{
		medie += cap->info.varsta;
		contor++;
		cap = cap->next;
	}
	if (contor == 0) {
		return 0;

	}
	return medie / contor;
}

// Funcția pentru citirea angajaților dintr-un fișier text
void citireFisierAngajati(const char* numeFisier, Nod** cap) {
	FILE* fisier = fopen(numeFisier, "r");
	if (fisier == NULL) {
		printf("Eroare la deschiderea fisierului!!");
		exit(1);
	}
	char nume[20];//buffer pt citirea numelui
	int  varsta; //variabila pt citirea varstei

	while (fscanf(fisier, "%s %d", nume, &varsta) != EOF)
	{
		inserareLaFinal(cap, initializareAngajat(nume, varsta));
	}
	fclose(fisier);
}

// Functie pentru gasirea angajatului cu varsta cea mai mare
Angajat angajatCuVarstaMaxima(Nod* cap) {
	Angajat angajatMaxim = cap->info;
	while (cap)
	{
		if (cap->info.varsta > angajatMaxim.varsta) {
			angajatMaxim = cap->info;
		}
		cap = cap->next;
	}
	return angajatMaxim;
}
// Functie pentru gasirea angajatului cu varsta cea mai mica
Angajat angajatCuVarstaMinima(Nod* cap) {
	Angajat angajatMinim = cap->info;
	while (cap)
	{
		if (cap->info.varsta < angajatMinim.varsta) {
			angajatMinim = cap->info;
		}
		cap = cap->next;
	}
	return angajatMinim;
}
// Functie pentru stergerea unui element de pe o pozitie specificata
void stergereElementPozitie(Nod** cap, int pozitie) {
	if (*cap == NULL) {
		return;
	}

	Nod* temp = *cap;
	if (pozitie == 0) {
		*cap = temp->next;
		free(temp->info.nume);
		free(temp);
		return;
	}

	for (int i = 0; i != NULL && i < pozitie - 1; i++) {
		temp = temp->next;
	}

	if (temp == NULL || temp->next == NULL) {
		return;
	}

	Nod* urmator = temp->next->next;
	free(temp->next->info.nume);
	free(temp->next);
	temp->next = urmator;
}

// Functie pentru inserarea unui element la o anumita pozitie
void inserarePePozitie(Nod** cap, Angajat info, int pozitie) {
	if (pozitie < 0) {
		printf("Pozitie invalida!");
			return;
	}

	if (pozitie == 0) {
		inserareInceput(cap, info);
		return;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	if (nou == NULL) {
		printf("Eroare la alocarea memoriei!");
		exit(1);
	}
	nou->info = info;

	Nod* temp = *cap;
	for (int i = 0; i < pozitie - 1 && temp != NULL; i++) {
		temp = temp->next;
	}

	if (temp == NULL) {
		printf("Pozitie depasita!");
		return;
	}
	nou->next = temp->next;
	temp->next = nou;
}

// Functie pentru conversia listei la vector
Angajat* conversieListaLaVector(Nod* cap, int* dimensiune) {
	int lungime = 0;
	Nod* temp = cap;
	while (temp!=NULL)
	{
		lungime++;
		temp = temp->next;
	}
	*dimensiune = lungime;
	Angajat* vector = (Angajat*)malloc(lungime * sizeof(Angajat));

	int index = 0;
	while (cap!= NULL)
	{
		vector[index++] = cap->info;
		cap = cap->next;
	}
	return vector;
}
void main() {
	Nod* cap = NULL;

	citireFisierAngajati("angajati.txt", &cap);

	printf("------------CIRIRE DE LA TASTATURA-------------");

	inserareInceput(&cap, initializareAngajat("Mihai", 30));
	inserareInceput(&cap, initializareAngajat("Andrei", 28));
	inserareInceput(&cap, initializareAngajat("Ana", 29));
	inserareInceput(&cap, initializareAngajat("Ana", 29));
	inserareInceput(&cap, initializareAngajat("Rebeca", 29));

	inserareLaFinal(&cap, initializareAngajat("Crina", 25));

	parcurgereLista(cap);

	printf("\n\n Numele \"Ana\" apare de %d ori.\n",suma( cap, "Ana"));

	printf("\n\nMedia varstei angajatilor este %f", calculVarstaMedie(cap));

	printf("\n\n");
	Angajat angajatMax = angajatCuVarstaMaxima(cap);
	printf("\n\n Angajatul cu varsta cea mai mare este : %s cu varsta %d ani.", angajatMax.nume, angajatMax.varsta);

	stergereElementPozitie(&cap, 2);
	printf("\n\n Lista dupa stergere: ");
	parcurgereLista(cap);

	Angajat angajatMin=	angajatCuVarstaMinima(cap);
	printf("\n\n Angajatul cu varsta minima este : %s cu varsta %d ani.", angajatMin.nume, angajatMin.varsta);

	inserarePePozitie(&cap, initializareAngajat("Nou", 22), 3);
	printf("\n\nLista dupa inserare ");
	parcurgereLista(cap);

	int dimensiuneVector;
	Angajat* vectorAngajat = conversieListaLaVector(cap, &dimensiuneVector);
	printf("\n\n Vectorul de angajati: ");
	for (int i = 0; i < dimensiuneVector; i++) {
		printf("\n%s %d", vectorAngajat[i].nume, vectorAngajat[i].varsta);
	}
	dezalocare(&cap);
	free(vectorAngajat);
}