#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Term* Position;
typedef struct Term {
    int koef;
    int exp;
    Position next;
} Term;
void printPoly(Position first) {
    Position temp = first;
    while (temp != NULL) {
        printf("%dx^%d ", temp->koef, temp->exp);
        temp = temp->next;

    }
    printf("\n");
}
int insertSorted(Position head, int koef, int exp) {
    Position prev = head;
    while (prev->next != NULL && prev->next->exp > exp) {
        prev = prev->next;
    }

    if (prev->next != NULL && prev->next->exp == exp) {
        prev->next->koef += koef;

        if (prev->next->koef == 0) {
            Position toDelete = prev->next;
            prev->next = prev->next->next;
            free(toDelete);
        }
        return 0;
    }

    Position n = (Position)malloc(sizeof(Term));
    if (n == NULL) {
        return -1;
    }
    n->koef = koef;
    n->exp = exp;
    n->next = prev->next;
    prev->next = n;
    return 0;
}
int readPoly(FILE* f, Position head) {
    char line[256];
    if (fgets(line, sizeof(line), f) == NULL) {
        return -1;
    }
    char* p = line;
    int koef, exp, n;
    while (sscanf(p, "%d %d%n", &koef, &exp, &n) == 2) {
        insertSorted(head, koef, exp);
        p += n;
    }
    return 0;




}
int addPoly(Position p1, Position p2, Position result) {
    Position temp = p1;
    while (temp != NULL) {
        if (insertSorted(result, temp->koef, temp->exp) != 0) {
            return -1;
        }
        temp = temp->next;

    }
    temp = p2;
    while (temp != NULL) {
        if (insertSorted(result, temp->koef, temp->exp) != 0) {
            return -1;
        }
        temp = temp->next;

    }
    return 0;
}

int multyplyPoly(Position p1, Position p2, Position result) {
    Position a = p1;
    while (a != NULL) {
        Position b = p2;
        while (b != NULL) {
            int koef = a->koef * b->koef;
            int exp = a->exp + b->exp;

            if (insertSorted(result, koef, exp) != 0) {
                return -1;
            }
            b = b->next;
        }
        a = a->next;
    }
    return 0;
}
void freePoly(Position head) {
    Position temp = head->next;
    while (temp != NULL) {
        Position nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    head->next = NULL;
}

int main() {
    FILE* f = fopen("poly.txt", "r");
    if (f == NULL) {
        printf("nema datoteke\n");
        return -1;
    }

    Term p1 = { 0, 0, NULL };
    Term p2 = { 0, 0, NULL };

    readPoly(f, &p1);
    readPoly(f, &p2);
    fclose(f);

    printPoly(p1.next);   /* 3x^2 -1x^1 5x^0 */
    printPoly(p2.next);   /* 2x^3 1x^1 4x^0 */
    Term sum = { 0, 0, NULL };
    addPoly(p1.next, p2.next, &sum);
    printPoly(sum.next);
    Term prod = { 0, 0, NULL };
    multyplyPoly(p1.next, p2.next, &prod);
    printPoly(prod.next);
    freePoly(&p1);
    freePoly(&p2);
    freePoly(&sum);
    freePoly(&prod);
    return 0;
}