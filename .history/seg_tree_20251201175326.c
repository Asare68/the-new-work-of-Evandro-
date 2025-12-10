#include "seg_tree.h"
#include "geo_util.h"
#include "point.h"
#include "segment.h"
#include <stdlib.h>
#include <math.h>

/* Simple active set: dynamic array. Simpler to maintain and bug-free.
   Insert / remove are O(n) but correct and deterministic. */

typedef struct {
    SegmentoT* items;
    int size;
    int cap;
    PontoT observer;
} Active_s;

SegsAtvsT SegsAtvs_Criar(PontoT x_observador) {
    Active_s* a = (Active_s*)malloc(sizeof(Active_s));
    if (!a) return NULL;
    a->cap = 16; a->size = 0;
    a->items = (SegmentoT*)malloc(sizeof(SegmentoT) * a->cap);
    a->observer = x_observador;
    return (SegsAtvsT)a;
}

static void ensure_cap(Active_s* a) {
    if (a->size >= a->cap) {
        a->cap *= 2;
        a->items = (SegmentoT*)realloc(a->items, sizeof(SegmentoT) * a->cap);
    }
}

void SegsAtvs_ativaSegmento(SegsAtvsT tree, SegmentoT s) {
    if (!tree || !s) return;
    Active_s* a = (Active_s*)tree;
    ensure_cap(a);
    a->items[a->size++] = s;
}

void SegsAtvs_desativaSegmento(SegsAtvsT tree, SegmentoT s) {
    if (!tree || !s) return;
    Active_s* a = (Active_s*)tree;
    int i;
    for (i = 0; i < a->size; ++i) if (a->items[i] == s) break;
    if (i == a->size) return;
    for (int j = i; j+1 < a->size; ++j) a->items[j] = a->items[j+1];
    a->size--;
}

SegmentoT SegsAtvs_segAtivoMaisProx(SegsAtvsT tree, VerticeT v) {
    if (!tree || !v) return NULL;
    Active_s* a = (Active_s*)tree;
    if (a->size == 0) return NULL;
    double best = INFINITY;
    SegmentoT best_s = NULL;
    for (int i = 0; i < a->size; ++i) {
        PontoT ray_end = raio_criar_fim(a->observer, Vertice_get_ponto(v));
        PontoT inter = interseccao_raio_segmento(a->observer, ray_end, a->items[i]);
        Ponto_Destruir(ray_end);
        if (!inter) continue;
        double d = Ponto_Distancia(a->observer, inter);
        Ponto_Destruir(inter);
        if (d < best) { best = d; best_s = a->items[i]; }
    }
    return best_s;
}

void SegsAtvs_Destruir(SegsAtvsT tree) {
    if (!tree) return;
    Active_s* a = (Active_s*)tree;
    free(a->items);
    free(a);
}
