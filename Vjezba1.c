#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED -1
#include <stdio.h>
#include <stdlib.h>

typedef struct _Student
{
    char ime[50];
    char prezime[50];
    float bodovi;
} stud;

float relativniBodovi(float bodovi, float maxBodovi);
void ispisStudenata(stud* studenti, int n, float maxBodovi);

int main()
{
    FILE* fp;
    fp = fopen("popis.txt", "r");
    if (!fp)
    {
        printf("Greska pri otvaranju datoteke ");
        return -1;
    }

    char buffer[100] = { 0 };
    int brojac = 0;

    while (!feof(fp))
    {
        if (fgets(buffer, sizeof(buffer), fp) != NULL)
            brojac++;
    }

    rewind(fp);

    stud* studenti = NULL;

    studenti = (stud*)malloc(brojac * sizeof(stud));

    if (!studenti) {
        printf("Greska pri alokaciji memorije!");
        fclose(fp);
        return -1;
    }

    for (int i = 0; i < brojac; i++)
    {
        fscanf(fp, "%s %s %f", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }

    fclose(fp);

    float maxBodovi = 20;
    ispisStudenata(studenti, brojac, maxBodovi);

    free(studenti);

    return 0;
}

float relativniBodovi(float bodovi, float maxBodovi)
{
    return (bodovi / maxBodovi * 100);
}

void ispisStudenata(stud* studenti, int n, float maxBodovi)
{
    for (int i = 0; i < n; i++)
    {
        printf("Ime: %s, Prezime: %s, Relativni bodovi: %.2f%%\n",
            studenti[i].ime,
            studenti[i].prezime,
            relativniBodovi(studenti[i].bodovi, maxBodovi));
    }
}