#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h> 

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

int main() {
	Stog S;
	Position d;
	srand((unsigned)time(NULL));
	char c;
	int broj;
	S.next = NULL;
	

	system("pause");
	return 0;
}


Position noviclan(void)
{
	Position p;
	int el;

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

void push(Position S, Position p)
{
	p->next = S->next;
	S->next = p;
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

void ubaci(Position head)
{
	Position p = NULL;
	char el;
	int br = 0, result = 1;
	FILE *f;
	f = fopen("lista.txt", "r");
	while (fscanf(f, " %c " , el) != EOF)
	{
		p = noviStudent(el);
		
			push(head, p);
		
		printf("\r\nList loaded\n");
		Ispis(head);
		fclose(f);
	}
}