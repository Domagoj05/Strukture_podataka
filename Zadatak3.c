#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba* Position;
typedef struct osoba
{
	char name[50];
	char lastN[50];
	int year;
	Position next;

}osoba;


int insertBegin(Position head, char* name, char* lastN, int year);
int ispis(Position head);
int insertEnd(Position head, char* name, char* lastN, int year);
Position findLastname(Position head, char* trazeno);
int delete(Position head, char* prezime);

// treci zadatak:

int insertAfter(Position head, char* targetlastN, char* name, char* lastN, int year);
int insertBefore(Position head, char* name, char* targetlastN, char* lastN, int yar);
int sortList(Position head);
int writeToFile(Position head, char* fileame);
int readFile(Position head, char* filename);

int main()
{

	Position head = NULL;
	head = (Position)malloc(sizeof(osoba));
	if (head == NULL)
	{
		printf("Greska pri alokaciji head memorije\n");
		return-1;
	}
	head->next = NULL;
	insertEnd(head, "Domagoj", "Zovko", 2005);
	insertEnd(head, "Leon", "Nola", 2006);
	insertBegin(head, "Luka", "Soldic", 2006);
	insertBegin(head, "Filip", "Sarlija", 2006);
	ispis(head);
	Position pronadjena = findLastname(head, "Zovko");
	printf("Pronadjena osoba je:%s %s %d \n", pronadjena->name, pronadjena->lastN, pronadjena->year);

	printf("\nBRISANJE OSOBE\n");
	delete(head, "Sarlija");
	printf("Stanje nakon brisanja:\n");
	ispis(head);

	// treci zadatak:

	printf("\ndodavanje iza i ispred:\n");
	insertAfter(head, "Zovko", "Leon", "Nola", 2006);
	insertBefore(head, "Soldic", "Ivan", "Ivic", 1999);
	printf("\n");
	ispis(head);

	printf("\nSoritiranje:\n");
	sortList(head);
	ispis(head);

	printf("\nSpremanje u dadoteku:\n");
	writeToFile(head, "studenti.txt");
	head->next = NULL;

	printf("\nCitanje iz dadoteke: \n");
	readFile(head, "studenti.txt");
	ispis(head);

	return 0;



}

int insertBegin(Position head, char* name, char* lastN, int year)
{
	Position q = NULL;
	q = (Position)malloc(sizeof(osoba));
	if (q == NULL)
	{
		printf("Greska pri alokaciji q memorije\n");
		return-1;
	}

	q->year = year;
	strcpy(q->name, name);
	strcpy(q->lastN, lastN);

	q->next = head->next;
	head->next = q;

	return 0;
}
int ispis(Position head)
{
	Position temp = head->next;


	while (temp != NULL)
	{

		printf("%s %s %d\n", temp->name, temp->lastN, temp->year);
		temp = temp->next;
	}

	return 0;
}

insertEnd(Position head, char* name, char* lastN, int year)
{
	Position p = NULL;
	p = (Position)malloc(sizeof(osoba));
	if (p == NULL)
	{
		printf("Greska pri alkocaiji p memorije\n");
		return-1;
	}

	p->year = year;
	strcpy(p->name, name);
	strcpy(p->lastN, lastN);

	p->next = NULL;
	Position temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	temp->next = p;
	return 0;
}

Position findLastname(Position head, char* trazeno)
{
	Position temp = head->next;

	while (temp != NULL)
	{
		if (strcmp(temp->lastN, trazeno) == 0)
		{
			return temp;
		}

		temp = temp->next;
	}


	return NULL;
}

int delete(Position head, char* prezime)
{
	Position prev = head;
	Position temp = head->next;

	while (temp != NULL)
	{
		if (strcmp(temp->lastN, prezime) == 0)
		{
			prev->next = temp->next;
			free(temp);
			printf("Osoba s prezimenom %s je izbrisana\n", prezime);
			return 0;
		}
		prev = temp;
		temp = temp->next;
	}

	printf("Osoba s prezimenom %s nije na listi\n", prezime);
	return-1;
}
//treci zadatak.

int insertAfter(Position head, char* targetlastN, char* name, char* lastN, int year)
{

	Position target = findLastname(head, targetlastN);
	if (target == NULL)
	{
		printf("Prezime %s ne postoji!\n", targetlastN);
		return-1;
	}
	Position q = NULL;
	q = (Position)malloc(sizeof(osoba));
	if (q == NULL)
	{
		printf("Greska pri alokaciji q2 memorije");
		return-1;
	}
	strcpy(q->name, name);
	strcpy(q->lastN, lastN);
	q->year = year;

	q->next = target->next;
	target->next = q;

	return 0;

}

int insertBefore(Position head, char* targetlastN, char* name, char* lastN, int year)
{
	Position prev = head;
	Position temp = head->next;

	while (temp != NULL)
	{
		if (strcmp(temp->lastN, targetlastN) == 0)
		{
			Position q = NULL;
			q = (Position)malloc(sizeof(osoba));
			strcpy(q->name, name);
			strcpy(q->lastN, lastN);
			q->year = year;

			q->next = temp;
			prev->next = q;
			return 0;
		}

		prev = temp;
		temp = temp->next;
	}

	printf("Osoba %s nije pronadjena!\n", targetlastN);
	return-1;

}
int sortList(Position head)
{
	Position j, prev_j, temp, end = NULL;

	if (head->next == NULL)
	{
		return 0;
	}

	while (head->next != end)
	{
		prev_j = head;
		j = head->next;

		while (j->next != end)
		{

			if (strcmp(j->lastN, j->next->lastN) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}
	return 0;
}

int writeToFile(Position head, char* filename)
{

	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Greska pri kreiranju dadoteke!\n");
		return-1;
	}
	Position temp = head->next;

	while (temp != NULL)
	{
		fprintf(fp, "%s %s %d\n", temp->name, temp->lastN, temp->year);
		temp = temp->next;
	}
	fclose(fp);
	return 0;
}

int readFile(Position head, char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju dadoteke");
		return -1;
	}

	char name[50];
	char lastN[50];
	int year;

	while (fscanf(fp, "%s %s %d", name, lastN, &year) == 3)
	{
		insertEnd(head, name, lastN, year);
	}
	fclose(fp);
	return 0;

}