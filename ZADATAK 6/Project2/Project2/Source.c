#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#define Min 10
#define Max 100 

struct red;
typedef struct red* Position;
typedef struct red {
	int el;
	Position next;
}Red;

int izvadi(Position);
Position noviclan(void);
void Ispis(Position);
void postavi(Position, Position);
int random(int, int);
int main() {
	Red R;
	Position d;
	srand((unsigned)time(NULL));
	char c;
	int broj;
	R.next = NULL;
	while (1) {
		printf("postavi-(u) izvadi-(p) ispis-(i) clear-(c) izadji-(e)\n");
		scanf(" %c", &c);
		switch (c) {
		case 'u':
			d = noviclan();
			postavi(&R, d);
			Ispis(&R);
			break;
		case 'p':
			broj = izvadi(&R);
			printf("izvadili smo broj %d \n", broj);
			Ispis(&R);
			break;
		case 'i':
			Ispis(&R);
			break;
		case 'c':
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			break;
		case 'e':
			return 0;
		}
	}
	system("pause");
	return 0;
}


Position noviclan(void)
{
	Position p;
	int el;

	el = random(Min, Max);

	p = (Position)malloc(sizeof(struct red));
	p->el = el;
	p->next = NULL;

	return p;
}

void Ispis(Position R)
{
	printf("elementi stoga : ");
	R = R->next;
	for (R; R != NULL; R = R->next) {
		printf("%d ", R->el);
	}
	printf("\r\n\n");
}

void postavi(Position R, Position p)
{
	p->next = R->next;
	R->next = p;
}

int izvadi(Position R)
{
	int x;
	Position temp;
	if (R->next != NULL) {
		Position pret=R;
		R = R->next;
		while (R->next != NULL) { R = R->next; pret = pret->next; }
		x = R->el;
		R = pret->next;
		pret->next = R->next;
		free(R);
		return x;
	}
	return -1;
}

int random(int min, int max)
{
	int bm = max - min + 1;
	int gr = RAND_MAX - (RAND_MAX % bm);
	int rnd = rand();
	while (rnd > gr) rnd = rand();
	return (rnd % bm) + min;
}