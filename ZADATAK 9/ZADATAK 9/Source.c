#define _CRT_SECURE_NO_WARNINGS


/*Napisati program koji omoguæava rad s binarnim stablom pretraživanja.Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cvorstabla;
typedef struct cvorstabla* Stablo;
typedef struct cvorstabla* Position;
typedef struct cvorstabla {
	int el;
	Stablo L;
	Stablo D;
}Cvor;

Stablo stvoriprazno(Stablo S);
Position trazimin(Stablo S);
Position trazi(Stablo S, int x);
Stablo dodaj(Stablo S, int x);
Stablo brisi(Stablo S, int x);
void ispis(Stablo S);

int main() {

	char c;
	int a;

	Stablo root = NULL;
	Stablo nadjeno;

	printf("MENU:\nd-dodaj element\nb-brisi element\nt-trazi element\ni-ispisi stablo\nz-izbrisi sve\nk-kraj\n");

	while (1) {
		scanf(" %c", &c);
		switch (c) {
		case'd':
			scanf(" %d", &a);
			root = dodaj(root, a);
			printf("\n");
			break;
		case'b':
			scanf("%d", &a);
			root = brisi(root, a);
			printf("\n");
			break;
		case't':
			scanf("%d", &a);
			nadjeno = trazi(root, a);
			if (nadjeno != NULL) printf("broj %d pronadjen!!\n", nadjeno->el);
			else
				puts("taj broj ne postoji, probaj ponovno!\n");
			break;
		case'i':
			ispis(root);
			printf("\n");
			break;
		case'z':
			root=stvoriprazno(root);
			printf("\n");
			break;
		case'k':
			return 0;
		default:
			puts("ta naredba ne postoji\n");
		}
	}
	return 0;
}


Stablo stvoriprazno(Stablo S)
{
	if (S != NULL) {
		S->L = stvoriprazno(S->L);
		S->D = stvoriprazno(S->D);
		free(S);
	}
	return NULL;
}
Position trazimin(Stablo S)
{
	if (S == NULL)
		return NULL;

	else if (S->L == NULL)
		return S;

	return trazimin(S->L);

}

Position trazi(Stablo S, int x)
{
	if (S == NULL)
		return NULL;

	else if (x > S->el)
		return trazi(S->D, x);

	else if (x < S->el)
		return trazi(S->L, x);

	return S;
}
Stablo dodaj(Stablo S, int x)
{
	if (S == NULL) {
		S = (Stablo)malloc(sizeof(Cvor));
		S->el = x;
		S->D = NULL;
		S->L = NULL;
	}
	else if (x < S->el)
		S->L = dodaj(S->L, x);

	else if (x > S->el)
		S->D = dodaj(S->D, x);

	return S;
}
Stablo brisi(Stablo S, int x)
{
	if (S == NULL) printf("nema toga broja!!");
	
	else if (x < S->el) 
		S->L = brisi(S->L, x);
	
	else if (x > S->el)
		S->D = brisi(S->D, x);
	
	else if (S->D && S->L != NULL)
	{
		Stablo temp = trazimin(S->D);
		S->el = temp->el;
		S->D = brisi(S->D, S->el);
	}
	else
	{
		Stablo temp = S;
		if (S->L == NULL)  S = S->D;
		else S = S->L;
		free(temp);
	}
	return S;
}
void ispis(Stablo S)
{
	if (S == NULL)return NULL;
	ispis(S->L);
	printf("%d ",S->el);
	ispis(S->D);
}