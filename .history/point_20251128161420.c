#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "point.h"

// Internal struct (hidden)
typedef struct {
    double x;
    double y;
} Ponto_s;

PontoT Ponto_Criar(double x, double y) {
    Ponto_s* p = (Ponto_s*)malloc(sizeof(Ponto_s));
    if (p == NULL) return NULL;
    p->x = x;
    p->y = y;
    return (PontoT)p;
}

double Ponto_get_x(PontoT p) {
    if (p == NULL) return 0.0;
    return ((Ponto_s*)p)->x;
}

double Ponto_get_y(PontoT p) {
    if (p == NULL) return 0.0;
    return ((Ponto_s*)p)->y;
}

double Ponto_Distancia(PontoT p1, PontoT p2) {
    if (p1 == NULL || p2 == NULL) return -1.0;

    Ponto_s* a = (Ponto_s*)p1;
    Ponto_s* b = (Ponto_s*)p2;

    double dx = a->x - b->x;
    double dy = a->y - b->y;

    return sqrt(dx * dx + dy * dy);
}

bool Ponto_Igual(PontoT p1, PontoT p2) {
    if (p1 == NULL || p2 == NULL) return false;

    Ponto_s* a = (Ponto_s*)p1;
    Ponto_s* b = (Ponto_s*)p2;

    return (a->x == b->x && a->y == b->y);
}

void Ponto_Destruir(PontoT p) {
    if (p != NULL) {
        free((Ponto_s*)p);
    }
}
