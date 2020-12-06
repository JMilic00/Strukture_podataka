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
	int exp;
	Position next;
}Polinom;

void Ispis(Position);
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
void sortUnos(Position, int, int);
void ispisi_listu1(Position);
void ispisi_listu2(Position);
Position noviPolinom(int, int);
Polinom Zbroji(Position, Position);
void ZbrojiSusjeda(Position);
void brisi(Position, int);
Position pronalazakPret(Position, int);
Polinom mnozenje(Position, Position);

int main() {
	Polinom head1;
	Polinom head2;
	Polinom p;
	 head1.next = NULL;
	 head2.next = NULL;
	ispisi_listu1(&head1);
	ispisi_listu2(&head2);
	//ZbrojiSusjeda(&head1);
	ZbrojiSusjeda(&head2);
	p = Zbroji(&head1, &head2);
	Ispis(&p);
	//Ispis(&p);

	return 0;
}
void ZbrojiSusjeda(Position a)
{
	Position prev = a;
	a = a -> next;
	while (a->next != NULL) {
		if (a->exp == a->next->exp) {
			a->next->koef += a->koef;
				prev->next = a->next;
				free(a);
				a = prev->next;
			}
		prev = prev->next;
		a = a->next;
		}
}


Position noviPolinom(int koef1, int exp1)
{
	Position p;

	p = (Position)malloc(sizeof(struct polinom));

	p->koef = koef1;
	p->exp = exp1;
	p->next = NULL;

	return p;
}

void Ispis(Position head)
{
	head = head->next;
	for (head; head != NULL; head = head->next) {
		printf("%dX^%d +", head->koef, head->exp);
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

Position pronalazakPret(Position p, int exp) {
	Position pret = p;
	p = p->next;

	while (p->next != NULL && exp==p->exp) {
		pret = p;
		p = p->next;
	}
	if (p == NULL) {					//ode je bilo krivo pisalo je p->next=NULL
		printf("ne postoji!\n");
		return NULL;
	}
	return pret;
}

void brisi(Position p, int exp) {
	Position prev;
	prev = pronalazakPret(p, exp);

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}

void sortUnos(Position head, int y, int x)
{
	Position q;
	while (head->next != NULL && head->next->exp < x)
		head = head->next;
	q = (Position)malloc(sizeof(struct polinom));
	q->exp = x;
	q->koef = y;

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
		fscanf(fp, " %d %d", &koef1, &exp1);
		sortUnos(head, koef1, exp1);
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
		fscanf(fp, " %d %d", &koef1, &exp1);
		sortUnos(head, koef1, exp1);
	}
	fclose(fp);
}
Polinom Zbroji(Position a, Position b) {
	Position d=NULL;
	Polinom c;
	c.next = NULL;
	int eks, koj;
	a = a->next;
	b = b->next;
	while (a != NULL && b != NULL) {
		if (a->exp == b->exp) {
			eks = a->exp;
			koj = a->koef + b->koef;
			d = noviPolinom(koj, eks);
			unosKraj(&c, d);
			a = a->next;
			b = b->next
		}
		else if (a->exp < b->exp) {
			unosKraj(&c, a);
			a = a -> next;
		}
		else if (a->exp > b->exp) {
			unosKraj(&c, b);
			b = b->next;
		}
	}
	if (a == NULL) {
		while (b != NULL) {
			unosKraj(&c, b);
			b = b->next;
		}
	}else if (b == NULL) {
		while (a != NULL) {
			unosKraj(&c, a);
			a = a->next;
		}
		}
	return c;
	}
/*Polinom mnozenje(Position a, Position b)
{
	Position c = NULL,p = NULL;
	p = malloc(sizeof(Polinom));
	p->next = NULL;

	Position i;	
	Position j;

	for (i = a->next; i != NULL; i = i->next)
		for (j = b->next; j != NULL; j = j->next)
		{
			p = noivPolinom((i->eoef*j->eoef), (i->exp + j->exp));
			sortUnos(c, p);
			zbrojisusjeda(c);
		}
	return c;
}*/
