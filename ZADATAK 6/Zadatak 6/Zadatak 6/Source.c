#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

#define Min 10
#define Max 100

struct stog;
typedef struct stog* Position;
typedef struct stog {
	int el;
	Position next;
}Stog;

int pop(Position);
Position noviclan(void);
void Ispis(Position);
void push(Position, Position);
int random(int, int);
Position pushR(Position, Position,Position);
int popR(Position, Position);
void IspisR(Position);

int main() {
	Stog S, R;
	Position d,last=&R;
	srand((unsigned)time(NULL));
	char c;
	int broj;
	S.next = NULL, R.next = NULL;
	while (1) {
		printf("pushStog-(u) popStog-(p) pushRed-(r) popRed-(t) ispisStog-(i) ispisRed(O) clear-(c) izadji-(e)\n");
		scanf(" %c", &c);
		switch (c) {
		case 'u':
			d = noviclan();
			push(&S, d);
			Ispis(&S);
			break;
		case 'p':
			broj = pop(&S);
			printf("popani broj je %d \n", broj);
			Ispis(&S);
			break;
		case 'r':
			d = noviclan();
			last = pushR(&R, d, last);
			IspisR(&R);
			break;
		case 't':
			broj = popR(&R, last);
			printf("popani broj je %d \n", broj);
			IspisR(&R);
			break;
		case 'i':
			Ispis(&S);
			break;
		case 'o':
			IspisR(&R);
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

	p = (Position)malloc(sizeof(struct stog));
	p->el = el;
	p->next = NULL;

	return p;
}

void Ispis(Position S)
{
	printf("elementi stoga : ");
	S = S->next;
	for (S; S != NULL; S = S->next) {
		printf("%d ", S->el);
	}
	printf("\r\n\n");
}

void IspisR(Position S)
{
	printf("elementi Reda : ");
	S = S->next;
	for (S; S != NULL; S = S->next) {
		printf("%d ", S->el);
	}
	printf("\r\n\n");
}

void push(Position S, Position p)
{
	p->next = S->next;
	S->next = p;
}

Position pushR(Position S, Position p, Position last)
{
	if (S->next == NULL) last = S;
		p->next = last->next;
		last->next = p;
		last = p;
		return last;
}

int pop(Position S)
{
	int x;
	Position temp;
	if (S->next != NULL) {
		x = S->next->el;
		temp = S->next;
		S->next = temp->next;
		free(temp);
		return x;
	}
	return -1;
}

int popR(Position S, Position last)
{
	int x;
	Position temp;
	if (S->next != NULL) {
		x = S->next->el;
		temp = S->next;
		S->next = temp->next;
		free(temp);
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