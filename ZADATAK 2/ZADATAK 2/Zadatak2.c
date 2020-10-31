#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M (256)

struct person;
typedef struct person* Position;
typedef struct person {
	char ime[M];
	char prezime[M];
	int godina;
	Position next;
}Person;

Position noviStudent(char*, char*, int);
void Ispis(Position);
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
Position pronalazak(Position, char*);
Position pronalazakPret(Position, char*);
void brisi(Position, char*);

int main() {
	Position head = NULL, p, n;
	char Ime[M], Prezime[M], prezimen[M];
	int god;
	char s;

	while (1) {

		printf("MENU:\nnovi element na pocetak liste-P\nnovi element na kraj liste-k\npronalazak elementa-n\nbrisati elemnt-b\nkraj programa-l\n");
		scanf(" %c", &s);
		switch (s) {
		case 'p':
			printf("unesite ime:\t");
			scanf(" %s", Ime);

			printf("unesite prezime:\t");
			scanf(" %s", Prezime);

			printf("unesite godinu rodjenja:\t");
			scanf(" %d", &god);

			printf("\n");

			p = noviStudent(Ime, Prezime, god);
			unosPocetak(&head, p);
			Ispis(&head);
			break;
		case 'k':
			printf("unesite ime:\t");
			scanf(" %s", Ime);

			printf("unesite prezime:\t");
			scanf(" %s", Prezime);

			printf("unesite godinu rodjenja:\t");
			scanf(" %d", &god);

			printf("\n");

			p = noviStudent(Ime, Prezime, god);
			unosKraj(&head, p);
			Ispis(&head);
			break;
		case 'n':
			printf("unesite prezime studenta koje zelite naci: ");
			scanf(" %s", prezimen);
			n = pronalazak(&head, prezimen);
			printf("\n%s %s %d\r\n", n->ime, n->prezime, n->godina);
			break;
		case 'b':

			printf("unesite prezime studenta koje zelite izbrisati: ");
			scanf(" %s", prezimen);
			brisi(&head, prezimen);
			Ispis(&head);
			break;
		case 'l':
			return 0;
			break;
		}
	}

	return 0;
}

Position noviStudent(char* Ime, char* Prezime, int god)
{
	Position p;

	p = (Position)malloc(sizeof(struct person));

	p->godina = god;
	strcpy(p->ime, Ime);
	strcpy(p->prezime, Prezime);
	p->next = NULL;

	return p;
}

void Ispis(Position head)
{
	Position p = NULL;

	printf("KONTENT LISTE: \n\n");
	for (p = head->next; p != NULL; p = p->next) {
		printf("\t %s %s %d \n", p->ime, p->prezime,p->godina);
	}
	printf("\r\n");
}

void unosPocetak(Position head, Position p)
{
	p->next = head->next;
	head->next = p;
}

void unosKraj(Position q, Position p)
{
	while (q->next != NULL) {
		q = q->next;
	}
	unosPocetak(q, p);
}

Position pronalazak(Position q, char* prez) {
	while (q->next != NULL && strcmp(q->prezime, prez))
		q = q->next;
	return q;
}

Position pronalazakPret(Position p, char* prezimen) {
	Position pret = p;
	p = p->next;

	while (p->next != NULL && strcmp(p->prezime, prezimen)) {
		pret = p;
		p = p->next;
	}
	if (p == NULL) {					//ode je bilo krivo pisalo je p->next=NULL
		printf("ne postoji!\n");
		return NULL;
	}
	return pret;
}

void brisi(Position p, char* prezimen) {
	Position prev;
	prev = pronalazakPret(p, prezimen);

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}

