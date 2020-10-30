#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define B 256
typedef struct {
	char ime[B];
	char prezime[B];
	int bodovi;
}lista;

int nadi(FILE*);
float relativanBroj(int);
void ispis(int, lista*);

int main()
{
	int brojStudenta;
	FILE* fp;
	fp = fopen("src.txt", "r");
	lista* stud = NULL;

	if (fp == NULL) printf("NEMA TXT DATOTEKE!!!");
	
	brojStudenta = nadi(fp);

	stud = (lista*)malloc(brojStudenta * sizeof(lista));

	rewind(fp);
	brojStudenta = 0;

	while (!feof(fp)) {
		fscanf(fp, " %s %s %d", stud[brojStudenta].ime, stud[brojStudenta].prezime, &(stud[brojStudenta].bodovi));
		brojStudenta++;
	}

	ispis(brojStudenta, stud);

	fclose(fp);

	system("pause");
	return 0;
}
float relativanBroj(int i)
{
	float maxbroj = 40;
	return ((float)i / maxbroj) * 100;
}

void ispis(int brojStud, lista* stud)
{
	int i;
	printf("IME    PREZIME        BODOVI(APSOLUTNI)    BODOVI(RELATIVNI)\n");

	for (i = 0; i < brojStud; i++) {
		printf("%s    %s    %d    %.2f\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, relativanBroj(stud[i].bodovi));
	}
	return;
}

int nadi(FILE* fp)
{
	int brojStudenta=0;
	while (!feof(fp)) {
		if (fgetc(fp) == '\n')brojStudenta++;
	}
	return brojStudenta;
}