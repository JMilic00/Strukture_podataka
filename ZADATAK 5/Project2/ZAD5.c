#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define M (256)

struct polinom;
typedef struct polinom* Position;
typedef struct polinom {
	int koef;
	Position next;
}Polinom;

void Ispis(Position);
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
void sortUnos(Position, int);
void ispisi_listu1(Position);
void ispisi_listu2(Position);
Position noviPolinom(int);
Polinom nadiPresjek(Position, Position);
void izbrisiSusjeda(Position);
Polinom mnozenje(Position, Position);

int main() {
	Polinom head1;
	Polinom head2;
	Polinom p;
	Polinom e;
	e.next = NULL;
	head1.next = NULL;
	head2.next = NULL;
	ispisi_listu1(&head1);
	ispisi_listu2(&head2);
	p = nadiPresjek(&head1, &head2, &e);
	printf("lista 1:\n");
	Ispis(&head1);
	printf("lista 2:\n");
	Ispis(&head2);
	printf("presjek lista:\n");
	Ispis(&p);
	printf("domena liste:\n");
	Ispis(&e);

	system("pause");
	return 0;
}
void izbrisiSusjeda(Position a)
{
	Position prev = a;
	a = a->next;
	while (a->next != NULL) {
		if (a->koef == a->next->koef) {
			prev->next = a->next;
			free(a);
			a = prev->next;
		}
		else
		{
			a = a->next;
		}
		prev = prev->next;
	}
}


Position noviPolinom(int koef1)
{
	Position p;

	p = (Position)malloc(sizeof(struct polinom));

	p->koef = koef1;
	p->next = NULL;

	return p;
}

void Ispis(Position head)
{
	head = head->next;
	for (head; head != NULL; head = head->next) {
		printf("%d ", head->koef);
	}
	printf("\r\n\n");
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

void sortUnos(Position head, int x)
{
	Position q;
	while (head->next != NULL && head->next->koef < x)
		head = head->next;
	q = (Position)malloc(sizeof(struct polinom));
	q->koef = x;

	unosPocetak(head, q);
}
void ispisi_listu1(Position head)
{
	Position p = NULL;
	int koef1, exp1;
	FILE *fp;
	fp = fopen("lista.txt", "r");
	if (fp == NULL)
		printf("alo ej!!!");
	while (!feof(fp)) {
		fscanf(fp, "%d ", &koef1);
		sortUnos(head, koef1);
		izbrisiSusjeda(head);
	}
	fclose(fp);
}
void ispisi_listu2(Position head)
{
	Position p = NULL;

	int koef1, exp1;
	FILE *fp;
	fp = fopen("lista1.txt", "r");
	if (fp == NULL)
		printf("alo ej!!!");
	while (!feof(fp)) {
		fscanf(fp, " %d ", &koef1);
		sortUnos(head, koef1);
		izbrisiSusjeda(head);
	}
	fclose(fp);
}
Polinom nadiPresjek(Position a, Position b, Position e) {
	Position d = NULL;
	Polinom c;
	c.next = NULL;
	a = a->next;
	b = b->next;
	while (a != NULL && b != NULL) {
		if (a->koef == b->koef) {
			d = noviPolinom(a->koef);
			unosKraj(&c, d);
			d = noviPolinom(a->koef);
			unosKraj(e, d);
			a = a->next;
			b = b->next;
		}
		else if (a->koef < b->koef) {
			d = noviPolinom(a->koef);
			a = a->next;
			unosKraj(e, d);
		}
		else if (a->koef > b->koef) {
			d = noviPolinom(b->koef);
			b = b->next;
			unosKraj(e, d);
		}
	}
	if (a == NULL) {
		while (b != NULL) {
			d = noviPolinom(b->koef);
			unosKraj(e, d);
			b = b->next;
		}
	}
	else if (b == NULL) {
		while (a != NULL) {
			d = noviPolinom(a->koef);
			unosKraj(e, d);
			a = a->next;
		}
	}
	return c;
}