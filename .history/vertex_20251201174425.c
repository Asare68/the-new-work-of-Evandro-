#include "../include/vertex.h"
#include "../include/point.h"
#include <stdlib.h>
#include <math.h>

typedef struct {
    TipoVerticeT tipo;
    SegmentoT pSeg;
    PontoT ponto;
    CodigoT codigo;
} Vertice_s;

VerticeT Vertice_Criar(TipoVerticeT tipo, SegmentoT pSeg, PontoT ponto, CodigoT codigo) {
    Vertice_s* v = (Vertice_s*)malloc(sizeof(Vertice_s));
    if (!v) return NULL;
    v->tipo = tipo; v->pSeg = pSeg; v->ponto = ponto; v->codigo = codigo;
    return (VerticeT)v;
}
TipoVerticeT Vertice_get_tipo(VerticeT v){ return ((Vertice_s*)v)->tipo; }
SegmentoT Vertice_get_segmento(VerticeT v){ return ((Vertice_s*)v)->pSeg; }
PontoT Vertice_get_ponto(VerticeT v){ return ((Vertice_s*)v)->ponto; }
CodigoT Vertice_get_codigo(VerticeT v){ return ((Vertice_s*)v)->codigo; }
void Vertice_Destruir(VerticeT v){ if(v) free(v); }

static double ang(PontoT obs, PontoT p) {
    double dx = Ponto_get_x(p) - Ponto_get_x(obs);
    double dy = Ponto_get_y(p) - Ponto_get_y(obs);
    double a = atan2(dy, dx);
    return a < 0 ? a + 2.0*M_PI : a;
}
static double dist2(PontoT a, PontoT b) {
    double dx = Ponto_get_x(a) - Ponto_get_x(b);
    double dy = Ponto_get_y(a) - Ponto_get_y(b);
    return dx*dx + dy*dy;
}

/* comparator for sorting vertices in angular order around observer
   Input pointers are pointers to elements stored in the list (void*),
   but List_Ordenar passes pointers to elements, so we receive
   pointer-to-item pointers here: const void* a -> &item */
int Vertice_Comparar(const void* A, const void* B, void* obs) {
    const Vertice_s* va = *(const Vertice_s**)A;
    const Vertice_s* vb = *(const Vertice_s**)B;
    PontoT o = (PontoT)obs;
    double angA = ang(o, va->ponto);
    double angB = ang(o, vb->ponto);
    if (angA < angB) return -1;
    if (angA > angB) return 1;
    double dA = dist2(o, va->ponto);
    double dB = dist2(o, vb->ponto);
    if (dA > dB) return -1; // farther first
    if (dA < dB) return 1;
    if (va->tipo == INICIO && vb->tipo == FIM) return -1;
    if (va->tipo == FIM && vb->tipo == INICIO) return 1;
    return 0;
}
