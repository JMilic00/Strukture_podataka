#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

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
void unosiza(Position, Position, char*);
void unosispred(Position, Position, char*);
Position pronalazak(Position, char*);
Position pronalazakPret(Position, char*);
void brisi(Position, char*);
void sort(Position, Position);
void izbaci(Position);
void ubaci(Position);

int main() {
	Position head = NULL, p, n, k, t;
	char Ime[M], Prezime[M], prezimen[M];
	int r;
	int god;
	char s;

	while (1) {

		printf("MENU:\nnovi element na pocetak liste-P\nnovi element na kraj liste-k\npronalazak elementa-n\nbrisati elemnt-b\nkraj programa-l\nako zelis zada unit -z\nako zelis ispred unit -i\nako zelis sortirat-s\nako zelis upisat u datoteku-m\nako zelis ispisat datoteku-g\n");
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
		case 'z':
			printf("unesite prezime studenta iza kojeg cete upisati: ");
			scanf(" %s", prezimen);

			printf("unesite ime:\t");
			scanf(" %s", Ime);

			printf("unesite prezime:\t");
			scanf(" %s", Prezime);

			printf("unesite godinu rodjenja:\t");
			scanf(" %d", &god);

			printf("\n");

			p = noviStudent(Ime, Prezime, god);
			unosiza(&head, p, prezimen);
			Ispis(&head);
			break;
		case 'i':
			printf("unesite prezime studenta ispred kojeg cete upisati: ");
			scanf(" %s", prezimen);

			printf("unesite ime:\t");
			scanf(" %s", Ime);

			printf("unesite prezime:\t");
			scanf(" %s", Prezime);

			printf("unesite godinu rodjenja:\t");
			scanf(" %d", &god);

			printf("\n");

			p = noviStudent(Ime, Prezime, god);
			unosispred(&head, p, prezimen);
			Ispis(&head);
			break;
		case 's':
			k = &head;
			while (k->next != NULL) {
				t = &head;
				while (t->next != NULL) {
					r = strcmp(t->prezime, t->next->prezime);
					if (r > 0)	sort(t, t->next);
					t = t->next;
				}
				k = k->next;
			}
			Ispis(&head);
			break;
		case 'm':
			ubaci(&head);
			break;
		case 'g':
			izbaci(&head);
			break;
		default:
			return 0;
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
		printf("\t %s %s %d \n", p->ime, p->prezime, p->godina);
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
	if (q->next == NULL) {
		printf("ne postoji!\n");
		return NULL;
	}
	return q;
}

Position pronalazakPret(Position q, char* prezimen) {
	Position pret = q;
	q = q->next;

	while (q->next != NULL && strcmp(q->prezime, prezimen)) {
		pret = q;
		q = q->next;
	}
	if (q == NULL) {
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
void unosiza(Position p, Position q, char* prezimen)
{
	Position k;
	k = pronalazak(p, prezimen);
	if (k == NULL) {
		printf("ne postoji!\n");
		return NULL;
	}
	else unosPocetak(k, q);
}
void unosispred(Position p, Position q, char* prezimen)
{
	Position k;
	k = pronalazakPret(p, prezimen);
	if (k == NULL) {
		printf("ne postoji!\n ");
		return NULL;
	}
	else unosPocetak(k, q);
}
void sort(Position p, Position q)
{
	p->next = q->next;
	q->next = p->next->next;
	p->next->next = q;
	return;
}
void ubaci(Position head)
{
	FILE *f;
	f = fopen("lista.txt", "w");
	if (f == NULL)printf("nesto nije dobro \n");
	while (head != NULL) {
		printf("sta ima");
		fprintf(f, " %s %s %d\n", head->ime, head->prezime, head->godina);
		head = head->next;
	}
	printf("dobro je sve\n");
	fclose(f);
}
void izbaci(Position head)
{
	Position p = NULL, q = NULL;
	char ime[M], prezime[M];
	int godina;
	int br = 0, result = 1;
	FILE *f;
	f = fopen("lista.txt", "r");
	while (fscanf(f, " %s %s %d", ime, prezime, &godina) != EOF)
	{
		p = noviStudent(ime, prezime, godina);
		for (q = head->next; q != NULL; q = q->next)
		{
			unosKraj(head, p);
		}
		printf("\r\nList loaded\n");
		Ispis(head);
		fclose(f);
	}
}