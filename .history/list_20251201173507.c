#include "list.h"
#include "segment.h"
#include "vertex.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    void** data;
    int size;
    int cap;
} List_s;

ListT List_Criar(void) {
    List_s* l = (List_s*)malloc(sizeof(List_s));
    if (!l) return NULL;
    l->cap = 16; l->size = 0;
    l->data = (void**)malloc(sizeof(void*) * l->cap);
    return (ListT)l;
}

void List_Inserir(ListT lst, void* item) {
    if (!lst) return;
    List_s* l = (List_s*)lst;
    if (l->size == l->cap) {
        l->cap *= 2;
        l->data = (void**)realloc(l->data, sizeof(void*) * l->cap);
    }
    l->data[l->size++] = item;
}

/* Linear search by segment id; returns first match */
void* List_Buscar(ListT lst, int id_ou_criterio) {
    if (!lst) return NULL;
    List_s* l = (List_s*)lst;
    for (int i = 0; i < l->size; ++i) {
        SegmentoT s = (SegmentoT)l->data[i];
        if (s && Segmento_get_id(s) == id_ou_criterio) return l->data[i];
    }
    return NULL;
}

void List_Destruir(ListT lst) {
    if (!lst) return;
    List_s* l = (List_s*)lst;
    free(l->data);
    free(l);
}

/* --- helpers used by vis_alg --- */

int List_Tamanho(ListT lst) {
    if (!lst) return 0;
    return ((List_s*)lst)->size;
}

void* List_Obter(ListT lst, int idx) {
    if (!lst) return NULL;
    List_s* l = (List_s*)lst;
    if (idx < 0 || idx >= l->size) return NULL;
    return l->data[idx];
}

/* Simple stable insertion sort using provided comparator (comparator expects: (A, B, ctx)).
   The list stores pointers to items; comparator compares pointers to elements (not arrays). */
static int compare_wrapper(void* a, void* b, void* ctx, int (*cmp)(const void*, const void*, void*)) {
    return cmp(a, b, ctx);
}

void List_Ordenar(ListT lst, void* ctx, int (*compar)(const void*, const void*, void*)) {
    if (!lst || !compar) return;
    List_s* l = (List_s*)lst;
    for (int i = 1; i < l->size; ++i) {
        void* key = l->data[i];
        int j = i - 1;
        while (j >= 0 && compar(&l->data[j], &key, ctx) > 0) {
            l->data[j + 1] = l->data[j];
            j--;
        }
        l->data[j + 1] = key;
    }
}

/* Build vertices list from list of segments: each segment produces two VerticeT */
ListT List_ExtrairVertices(ListT segmentos_S) {
    if (!segmentos_S) return NULL;
    List_s* segs = (List_s*)segmentos_S;
    ListT verts = List_Criar();
    for (int i = 0; i < segs->size; ++i) {
        SegmentoT seg = (SegmentoT)segs->data[i];
        if (!seg) continue;
        PontoT a = Segmento_get_ini(seg);
        PontoT b = Segmento_get_fim(seg);
        VerticeT va = Vertice_Criar(INICIO, seg, a, ORIG);
        VerticeT vb = Vertice_Criar(FIM, seg, b, ORIG);
        List_Inserir(verts, va);
        List_Inserir(verts, vb);
    }
    return verts;
}
