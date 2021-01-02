#define _CRT_SECURE_NO_WARNINGS


/*Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.Toènije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/


#include<stdio.h>
#include<stdlib.h> 
#include<malloc.h>
#define MAX (256)

struct dir;
struct stog;
typedef struct dir* Position;
typedef struct stog* stack_Position;

typedef struct dir {
	char name[MAX];
	Position sibling;
	Position child;
}Dir;

typedef struct stog {
	Position data;
	stack_Position next;
}Stog;


void removee(Position);
void md(Position, char*);
Position cd_dir(Position,stack_Position,char* );
Position cd_(stack_Position, Position);
void dir(Position);

int main()
{
	Position current = (Position)malloc(sizeof(Dir));
	stack_Position currentS = (stack_Position)malloc(sizeof(Stog));
	current->child = current->sibling = NULL;
	currentS->data = currentS->next = NULL;
	strcpy(current->name, " ");

	stack_Position stog = (stack_Position)malloc(sizeof(Stog));
	stog->data = current;

	stog->next =currentS->next;
	currentS->next = stog;

	printf("what do you wana to do:\n");

	while (1) {
		char name[MAX], c[MAX];
		int a;
		scanf("%s", &c);
		if (!strcmp(c, "md")) {
			scanf("%s", name);
			md(current, name);
		}
		else if (!strcmp(c, "cd")) {
			scanf("%s", name);
			current = cd_dir(current, currentS, name);
		}
		else if (!strcmp(c, "cd..")) {
			current = cd_(currentS, current);
		}
		else if (!strcmp(c, "dir")) {
			dir(current);
		}
		else if (!strcmp(c, "exit")) {
			while (currentS->next->next != NULL) current = cd_(currentS, current);
			free(currentS->next);
			free(currentS);
			removee(current);
			current->child = NULL;
			current->sibling = NULL;
			return 0;
		}
		else {
			puts("command does not exist");
		}
	}
	return 0;
}

void md(Position current, char* name)
{
	if (current->child == NULL) {	
		Position new = malloc(sizeof(Dir));
		strcpy(new->name, name);
		new->child = new->sibling = NULL;
		current->child = new;
	}

	else if (!strcmp(current->child->name, name))
		puts("Directory already exists");

	else if (strcmp(current->child->name, name) > 0) {
		Position new = malloc(sizeof(Dir));
		strcpy(new->name, name);
		new->child = NULL;
		new->sibling = current->child;
		current->child = new;
	}

	else {
		Position prev = current->child;
		Position pivot = current->child->sibling;
		while (pivot != NULL) {
			if (strcmp(pivot->name, name) > 0)
				break;
			prev = prev->sibling;
			pivot = pivot->sibling;
		}
		Position new = malloc(sizeof(Dir));
		strcpy(new->name, name);
		new->sibling = prev->sibling;
		prev->sibling = new;
		new->child = NULL;

	}
}

Position cd_dir(Position current, stack_Position S, char* name)
{
	Position temp = current->child;
	while (temp != NULL)
	{
		if (strcmp(temp->name, name)==0) {
			stack_Position new = malloc(sizeof(Stog));
			new->data = temp;
			new->next = S->next;
			S->next = new;
			return temp;
		}
		temp = temp->sibling;
	}
	puts("directory not found");
	return current;
}

Position cd_(stack_Position S, Position current)
{
	if (strcmp(S->next->data->name, " ") != 0){
				stack_Position temp = S->next;
				Position dir = temp->next->data;
				S->next = temp->next;
				free(temp);
				return dir;
	}
	else return current;
}
void dir(Position current)
{
	Position count = NULL;
	count = current->child;
	while (count != NULL) {
		printf("\t%s\n", count->name);
		count = count->sibling;
	}
}

void removee(Position current)
{
	if (current == NULL) return;
	removee(current->sibling);
	removee(current->child);
	free(current);
}