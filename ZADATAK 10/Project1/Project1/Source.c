#define _CRT_SECURE_NO_WARNINGS


/*Napisati program koji omoguæava rad s binarnim stablom pretraživanja.Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cvor;
struct stog;

typedef struct cvorstabla* Stablo;
typedef struct stog* Position;

typedef struct cvorstabla {
	char el;
	Stablo L;
	Stablo D;
}Cvor;

typedef struct stog {
	Stablo cvorel;
	Position next;
}Stog;

void push(Position,Position);
int pop(Position);
void postorder(Stablo);
void inorderFile(Stablo, FILE*);
void inorder(Stablo);

int main()
{
	Stablo c;
	Position s;

	c = NULL;
	c = malloc(sizeof(Cvor));
	c->D = c->L = NULL;

	s = NULL;
	s = malloc(sizeof(Cvor));
	s->next = s->cvorel = NULL;

	int velicina,br,val = 0;
	char* buffer = NULL;
	int pivot = 0, pivot2 = 0;
	buffer = malloc(1000 * sizeof(char));

	FILE* p;
	FILE* i;
	p = fopen("postfix.txt", "r");
	i = fopen("infix.txt", "w");

	if (p == NULL || i == NULL) {
		printf("File did not open\n"); return 0;
	}

	while (!feof(p)) {
		fgets(buffer, 1000, p);
	}

	velicina = strlen(buffer);
	while (pivot < velicina) {

		char ch;

		Stablo novi = NULL;

		novi = malloc(sizeof(Cvor));
		novi->el = malloc(sizeof(char));


		pivot2 = sscanf(buffer, "%d %n", &br, &val);
		sscanf(buffer, "%c %n", &ch, &val);
		novi->D = novi->L = NULL;
		novi->el = ch;

		if (pivot2 != 0 && pivot2 != EOF) {
			push(s, novi);
		}
		else {
			novi->D = pop(s);
			novi->L = pop(s);
			push(s, novi);
		}
		buffer += val;
		pivot += val;
	}
	fclose(p);

	c = pop(s);

	puts("inorder\n");
	inorder(c->L);
	printf("%c ", c->el);
	inorder(c->D);
	puts("\nPostorder\n");
	postorder(c);
	inorderFile(c->L, i);
	fprintf(i, "%c ", c->el);
	inorderFile(c->D, i);
	fclose(i);
	return EXIT_SUCCESS;
}

int pop(Position S)
{
	Stablo novi;
	Position temp;
	if (S->next != NULL) {
		temp = S->next;
		novi = temp->cvorel;
		S->next = temp->next;
		free(temp);
		return novi;
	}
	return -1;
}

void push(Position S, Stablo p)
{
	Position novi;
	novi = malloc(sizeof(Stog));

	novi->cvorel = p;
	novi->next = S->next;
	S->next = novi;
}

void postorder(Stablo c)
{
	if (c == NULL) return;
	if (c != NULL) {
		postorder(c->L);
		postorder(c->D);
		printf( "%c ", c->el);
	}
}
void inorder(Stablo c)
{
	if (c == NULL) return;

	if (c != NULL) {
		if (!isdigit(c->el)) {
			printf("(");
		}
		inorder(c->L);
		printf( "%c ", c->el);
		inorder(c->D);
		if (!isdigit(c->el)) {
			printf(")");
		}
	}
}

void inorderFile(Stablo c, FILE* f)
{
	if (c == NULL) return;
	if (c != NULL) {
		if (!isdigit(c->el)) {
			fprintf(f,"(");
		}
		inorderFile(c->L,f);
		fprintf(f,"%c ", c->el);
		inorderFile(c->D,f);
		if (!isdigit(c->el)) {
			fprintf(f,")");
		}
	}
}