#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Angajat
{
	char* nume;
	int varsta;
};

struct Nod
{
	Angajat info;
	Nod* next;
	Nod* prev;
};

struct LDI
{
	Nod* prim;
	Nod* ultim;
};

void afisareAngajat(Angajat angajat) {
	printf("\nAngajatul %s are %d ani.", angajat.nume, angajat.varsta);
}

Angajat initializareAngajat(const char* nume, int varsta) {
	Angajat a;
	a.varsta = varsta;
	a.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(a.nume, nume);

	return a;
}

void inserareInceput(Angajat angajat, LDI* lista) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = angajat;
	nou->next = lista->prim;
	nou->prev = NULL;

	if (lista->prim) {
		lista->prim->prev = nou;
		lista->prim = nou;
	}
	else
	{
		lista->prim = lista->ultim=nou;
	}
}

void inserareFinal(Angajat angajat, LDI* lista) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = angajat;
	nou->prev = lista->ultim;
	nou->next = NULL;

	if (lista->ultim) {
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else
	{
		lista->prim = lista->ultim = nou;
	}
}

void traversareLista(LDI lista, int* nrAngajati) {
	while (lista.prim)
	{
		afisareAngajat(lista.prim->info);
		(*nrAngajati)++;
		lista.prim = lista.prim->next;
	}
}

void traversareListaCirculara(LDI lista) {
	if (!lista.prim)return;

	Nod* it = lista.prim;
	do {

		afisareAngajat(lista.prim->info);
		lista.prim = lista.prim->next;
	} while (lista.prim!=it);
}

Angajat angajatCuVarstaMinima(LDI lista) {
	Angajat angajatMin = lista.prim->info;
	Nod* current = lista.prim->next;
	while (current)
	{
		if (current->info.varsta < angajatMin.varsta) {
			angajatMin = current->info;
		}
		current = current->next;
	}
	return angajatMin;
}

Angajat angajatCuVarstaMaxima(LDI lista) {
	Angajat  angajatMax = lista.prim->info;
	Nod* current = lista.prim->next;

	while (current)
	{
		if (current->info.varsta > angajatMax.varsta) {
			angajatMax = current->info;
		}
		current = current->next;
	}
	return angajatMax;
}

void conversieListaLaVector(LDI lista, Angajat** vectorAngajat) {
	int nrAngajati = 0;
	while (lista.prim)
	{
		(*vectorAngajat)[nrAngajati] = initializareAngajat(lista.prim->info.nume, lista.prim->info.varsta);
		nrAngajati++;
		lista.prim = lista.prim->next;
	}
}

float calculVastaMedie(LDI lista) {
	if (lista.prim == NULL) {
		printf("Lista este valida!");
		return 0.0;
	}

	int sumaVarsta = 0;
	int numarAngajati = 0;
	Nod* current = lista.prim;
	while (current)
	{
		sumaVarsta += current->info.varsta;
		numarAngajati++;
		current = current->next;
	}

	return (float)sumaVarsta / numarAngajati;
}

void stergereNodDupaNume(LDI* lista, const char* nume) {
	Nod* current = lista->prim;
	while (current!=NULL)
	{
		if (strcmp(current->info.nume, nume) == 0) {
			Nod* temp = current->next;
			if (temp == NULL) {
				lista->ultim = current->prev;
			}
			else
			{
				temp->prev = current->next;
			}if (current->prev==NULL)
			{
				lista->prim = temp;
			}
			else {
				current->prev->next = temp;
			}
			free(current->info.nume);
			free(current);
			printf("\nNodul cu numele %s a fost sters din lista.\n", nume);
			return;
		}
		current = current->next;
	}
	
}
 
void stergereLista(LDI* lista) {
	while (lista->prim!=NULL)
	{
		Nod* temp = lista->prim;
		lista->prim = lista->prim->next;
		free(temp->info.nume);
		free(temp);
	}
	lista->ultim = NULL;

}
int numarTotalDeAngajati(LDI lista) {
	int numarAngajati = 0;
	Nod* current = lista.prim;
	while (current)
	{
		numarAngajati++;
		current = current->next;
	}
	return numarAngajati;
}

void inserareNodLaPozitie(Angajat angajat, int pozitie, LDI* lista) {
	if (pozitie < 0) {
		printf("Pozitia trebuie sa fie un numar pozitiv sau zero!\n");
		return;
	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	if (nou == NULL) {
		printf("Eroare la alocare memorie!\n");
		exit(EXIT_FAILURE);
	}
	nou->info = angajat;

	if (pozitie == 0) { // Inserare la inceputul listei
		nou->prev = NULL;
		nou->next = lista->prim;
		if (lista->prim) {
			lista->prim->prev = nou;
		}
		else {
			lista->ultim = nou; // Lista era vida, deci acesta este și ultimul element acum
		}
		lista->prim = nou;
	}
	else {
		Nod* current = lista->prim;
		int index = 0;
		while (current && index < pozitie - 1) { // Ne poziționăm la nodul de dinaintea poziției de inserare
			current = current->next;
			index++;
		}
		if (current == NULL && pozitie > 0) { // Dacă am ajuns la sfârșitul listei și poziția este mai mare decât numărul de noduri
			printf("Pozitia depaseste lungimea listei!\n");
			free(nou);
			return;
		}
		nou->prev = current;
		nou->next = current->next;
		if (current->next) { // Dacă inserăm între noduri
			current->next->prev = nou;
		}
		else { // Dacă inserăm la sfârșitul listei
			lista->ultim = nou;
		}
		current->next = nou;
	}
	printf("Angajatul %s a fost inserat in lista pe pozitia %d.\n", angajat.nume, pozitie);
}

void citireAngajati(const char* numeFisier, LDI* lista) {
	FILE* fisier = fopen(numeFisier, "r");
	if (fisier == NULL) {
		printf("Eroare la deschiderea fisierului!\n");
		return;
	}

	char linie[100];
	while (fgets(linie, sizeof(linie), fisier)) {
		char* nume = strtok(linie, ",");
		int varsta = atoi(strtok(NULL, ","));
		inserareFinal(initializareAngajat(nume, varsta), lista);
	}

	fclose(fisier);
}


void dezalocare(LDI* lista) {
	Nod* copie = lista->prim;
	while (copie)
	{
		free(copie->info.nume);
		copie = copie->next;
		if (copie) {
			free(copie->prev);
		}
	}
	free(lista->ultim);
	lista->prim = lista->ultim = NULL;
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	citireAngajati("angajati.txt", &lista);

	inserareInceput(initializareAngajat("Matei", 28), &lista);
	inserareInceput(initializareAngajat("Anca", 29), &lista);
	inserareInceput(initializareAngajat("Maria", 25), &lista);
	inserareInceput(initializareAngajat("Catalin", 28), &lista);


	inserareFinal(initializareAngajat("Andrei", 30), &lista);

	int nrAngajati = 0;
	traversareLista(lista, &nrAngajati);

	Angajat angajatMin = angajatCuVarstaMinima(lista);
	printf("\nAngajatul cu varsta cea mai mica este: %s cu varsta %d ani.\n", angajatMin.nume, angajatMin.varsta);

	Angajat angajatMax = angajatCuVarstaMaxima(lista);
	printf("\Angajatul cu cea mai mare varsta este: %s cu varsta %d ani.\n", angajatMax.nume, angajatMax.varsta);

	printf("\nVarsta medie a angajatilor este : %.2f ani", calculVastaMedie(lista));


	Angajat* vectorAngajati = (Angajat*)malloc(sizeof(Angajat) * nrAngajati);
	conversieListaLaVector(lista, &vectorAngajati);
	printf("\n Afisare angajati din vectorul de angajati:");
	for (int i = 0; i < nrAngajati; i++) {
		afisareAngajat(vectorAngajati[i]);
		free(vectorAngajati[i].nume);
	}
	free(vectorAngajati);



	stergereNodDupaNume(&lista, "Anca");
	printf("\nDupa stregere Ancai: ");
	traversareLista(lista, &nrAngajati);

	inserareNodLaPozitie(initializareAngajat("Ioana", 27), 2, &lista);
	printf("\nDupa inserarea lui Ioana la pozitia 2:");
	traversareLista(lista, &nrAngajati);



	lista.prim->prev = lista.ultim;
	lista.ultim->next = lista.prim;

	printf("\n\nLista circulara:\n");
	traversareListaCirculara(lista);

	/*stergereLista(&lista);
	dezalocare(&lista);*/
}