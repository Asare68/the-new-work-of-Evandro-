#include "point.h"
#include <stdlib.h>
#include <math.h>

typedef struct { double x, y; } Ponto_s;

PontoT Ponto_Criar(double x, double y) {
    Ponto_s* p = (Ponto_s*)malloc(sizeof(Ponto_s));
    if (!p) return NULL;
    p->x = x; p->y = y;
    return (PontoT)p;
}
double Ponto_get_x(PontoT p){ return p?((Ponto_s*)p)->x:0.0; }
double Ponto_get_y(PontoT p){ return p?((Ponto_s*)p)->y:0.0; }

double Ponto_Distancia(PontoT p1, PontoT p2) {
    if (!p1 || !p2) return -1.0;
    double dx = Ponto_get_x(p1) - Ponto_get_x(p2);
    double dy = Ponto_get_y(p1) - Ponto_get_y(p2);
    return sqrt(dx*dx + dy*dy);
}

bool Ponto_Igual(PontoT p1, PontoT p2) {
    if (!p1 || !p2) return false;
    return (Ponto_get_x(p1) == Ponto_get_x(p2) && Ponto_get_y(p1) == Ponto_get_y(p2));
}

void Ponto_Destruir(PontoT p) { if (p) free(p); }

typedef struct {
    double x;
    double y;
} PontoT;

