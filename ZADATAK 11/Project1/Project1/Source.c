#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define TABLICA (11)
#define MAX (256)

struct lista;

typedef struct lista* Position;

typedef struct lista {
	char ime[MAX];
	char prezime[MAX];
	int broj;
	Position next;
}Lista;

int preslikavanje(char*);
void dodaj(Position, Position);
void find(Position, char*,char*);
void ispis(Position);

int main()
{
	Position hash[TABLICA];
	
	int i;
	for (i = 0; i < TABLICA; i++) {
		hash[i] = NULL;
		hash[i] = malloc(sizeof(Lista));
		hash[i]->next = NULL;
	}

	char c;
	char prezime[MAX];
	char ime[MAX];

	printf("dodat studenta u tablicu-d\nispisat tablicu-i\ntrazit studenta-t\nizac iz programa-p\n");

	while (1) {
		int kljuc=0,b;
		char i[MAX], p[MAX];

		Position d = malloc(sizeof(Lista));
		d->next = NULL;

		scanf(" %c", &c);

		switch (c) {
		case'd':
			printf("unesite ime: ");
			scanf("%s", i);
			strcpy(d->ime, i);

			printf("\nunesite prezime: ");
			scanf("%s", p);
			strcpy(d->prezime, p);

			kljuc = preslikavanje(d->prezime);

			printf("\nmaticni broj: ");
			scanf("%d", &b);
			d->broj = b;

			dodaj(hash[kljuc],d);
			break;
		case'i':
			ispis(hash);
			break;
		case't':
			printf("kojeg studenta zelite naci(upisite ime i prezime): ");
			scanf("%s %s",ime, prezime);
			kljuc = preslikavanje(prezime);
			find(hash[kljuc],prezime,ime);
			break;
		case'p':
			return EXIT_SUCCESS;
			break;
		}
	}
	return EXIT_SUCCESS;
}

int preslikavanje(char *prezime)
{
	int i = 0,hashV = 0;
	while (prezime[i] != '\0')
	{
		hashV += prezime[i];
		i += 1;
		if (i == 5) break;
	}
	return (hashV % (TABLICA-1));
}

void dodaj(Position hash,Position d)
{
	Position prev=hash;

	if (hash->next == NULL) {
		d->next = hash->next;
		hash->next = d;
		return;
	}

	while (hash->next != NULL) {
		hash = hash->next;
		if (hash->broj==d->broj) {
			puts("student vec postoji!");
			return;
		}
		else if (strcmp(d->prezime, hash->prezime) < 0) {
			d->next = prev->next;
			prev->next = d;
			return;
		}
		else if (!strcmp(d->prezime, hash->prezime)) {
			if (!strcmp(d->ime, hash->ime)) {
				puts("student vec postoji");
				return;
			}
			else if (strcmp(d->ime, hash->ime) < 0) {
				d->next = prev->next;
				prev->next = d;
				return;
			}
			else{
				prev = prev->next;
				d->next = prev->next;
				prev->next = d;
			}
		}
		prev = prev->next;
	}
}


void find(Position hash, char* p,char* i)
{
	hash = hash->next;
	while (hash != NULL) {
		if (!strcmp(p, hash->prezime))
			if (!strcmp(i, hash->ime)) break;
		hash = hash->next;
	}

	if (hash!= NULL)	
		printf("maticni broj osobe %s %s je %d\n", hash->ime, hash->prezime, hash->broj);
	else  
		printf("student ne postoji");
}

void ispis(Position head[])
{
	int i = 0;
	Position temp = malloc(sizeof(Lista));
	temp->next = NULL;
	printf("\t ime\t prezime \tmaticni broj\n");

	for (i; i < 11; i++) {
			temp = head[i]->next;
			while (temp != NULL) {
				printf("%s\t %s \t%d  -", temp->ime,temp->prezime, temp->broj);
				temp = temp->next;
		}

			printf(" -----\n");
	}
}