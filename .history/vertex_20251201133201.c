#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vertex.h"
#include "point.h"
#include "segment.h"

typedef struct {
    TipoVerticeT tipo;     // INICIO or FIM
    SegmentoT pSeg;        // Segment pointer
    PontoT ponto;          // Coordinates
    CodigoT codigo;        // ORIG, ARTF, RE
} Vertice_s;

/* ============================================================
   🔹 Constructor
   ============================================================ */
VerticeT Vertice_Criar(TipoVerticeT tipo, SegmentoT pSeg, PontoT ponto, CodigoT codigo) {
    Vertice_s* v = (Vertice_s*) malloc(sizeof(Vertice_s));
    if (v == NULL) return NULL;

    v->tipo = tipo;
    v->pSeg = pSeg;
    v->ponto = ponto;
    v->codigo = codigo;

    return (VerticeT) v;
}

/* ============================================================
   🔹 Getters
   ============================================================ */
TipoVerticeT Vertice_get_tipo(VerticeT v) {
    return ((Vertice_s*)v)->tipo;
}

SegmentoT Vertice_get_segmento(VerticeT v) {
    return ((Vertice_s*)v)->pSeg;
}

SegmentoT Vertice_get_pseg(VerticeT v) {
    return ((Vertice_s*)v)->pSeg;
}

PontoT Vertice_get_ponto(VerticeT v) {
    return ((Vertice_s*)v)->ponto;
}

CodigoT Vertice_get_codigo(VerticeT v) {
    return ((Vertice_s*)v)->codigo;
}

/* ============================================================
   🔹 Helper functions for the comparator
   ============================================================ */
static double calcula_angulo(PontoT p, PontoT x) {
    double dx = Ponto_get_x(p) - Ponto_get_x(x);
    double dy = Ponto_get_y(p) - Ponto_get_y(x);
    double ang = atan2(dy, dx);  // range [-π, π]
    return ang < 0 ? ang + 2*M_PI : ang;
}

static double calcula_distancia(PontoT p, PontoT x) {
    double dx = Ponto_get_x(p) - Ponto_get_x(x);
    double dy = Ponto_get_y(p) - Ponto_get_y(x);
    return sqrt(dx*dx + dy*dy);
}

/* ============================================================
   🔹 Comparator
   ============================================================ */
int Vertice_Comparar(const void* a, const void* b, PontoT x_observador) {

    Vertice_s* vA = (Vertice_s*) a;
    Vertice_s* vB = (Vertice_s*) b;

    PontoT pA = vA->ponto;
    PontoT pB = vB->ponto;

    double angA = calcula_angulo(pA, x_observador);
    double angB = calcula_angulo(pB, x_observador);

    /* 1. Compare angle */
    if (angA < angB) return -1;
    if (angA > angB) return 1;

    /* 2. Compare distance — segments farther away are processed first */
    double distA = calcula_distancia(pA, x_observador);
    double distB = calcula_distancia(pB, x_observador);

    if (distA > distB) return -1;
    if (distA < distB) return 1;

    /* 3. Compare type */
    if (vA->tipo == INICIO && vB->tipo == FIM) return -1;
    if (vA->tipo == FIM && vB->tipo == INICIO) return 1;

    return 0;
}

/* ============================================================
   🔹 Destructor
   ============================================================ */
void Vertice_Destruir(VerticeT v) {
    if (v != NULL)
        free(v);
}
