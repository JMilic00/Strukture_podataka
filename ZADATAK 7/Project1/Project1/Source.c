#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista;
typedef struct lista* Position;
typedef struct lista {
	int el;
	Position next;
}Lista;


int pop(Position);
void push(Position, int);
int racunaj(char, int, int);

int main() {
	FILE* f;
	Lista head;
	int n = 0;
	head.next = NULL;
	char* buffer = NULL;
	char c;
	int x = 0, y = 0, r = 0,broj, provjera,velicina,velicinabuffera=0;
	

	f = fopen("postfix.txt", "r");
	buffer = (char *)malloc(1000 * sizeof(char));

	if (f==NULL) {
		puts("Greška pri otvaranju!\n");
		return 0;
	}

	while (!feof(f)) {
		fgets(buffer, 1000, f);
	}

	velicina = strlen(buffer);

	while (velicinabuffera < velicina) {

			provjera = sscanf(buffer, "%d %n", &broj, &n);

		if (provjera != 0 && provjera != EOF) {

			push(&head, broj);

		}else{

			provjera = sscanf(buffer, "%c %n", &c, &n);
			x=pop(&head);
			y=pop(&head);
			r = racunaj(c, x, y);
			push(&head, r);

		}

		buffer += n;
		velicinabuffera += n;

	}
	printf("Rezultat je: %d", head.next->el);

	fclose(f);
	system("pause");
	return 0;
}


void push(Position S, int c)
{
	Position p;

	p = (Position)malloc(sizeof(struct lista));
	
		p->el = c;
		p->next = S->next;
		S->next = p;

}

int pop(Position head)
{
	Position temp;
	int x;

	if (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		x = temp->el;
		free(temp);
	}
	return x;
}

int racunaj(char op, int x, int y)
{
	int r = 0;
	switch (op)
	{
	case '+':
		r = x + y;
		break;
	case '-':
		r = x - y;
		break;
	case '*':
		r = x * y;
		break;
	case '/':
		if (y > 0)
			r = x / y;
		break;
	default:
		printf("Greska");
	}
	return r;
}