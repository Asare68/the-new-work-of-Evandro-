#include <stdlib.h>
#include <string.h>
#include "segment.h"

// Internal struct (hidden from the user)
typedef struct {
    int id;
    PontoT pto_ini;
    PontoT pto_fim;
    char cor[18];   // up to 17 characters + NULL terminator
} Segmento_s;

SegmentoT Segmento_Criar(int id, PontoT pto_ini, PontoT pto_fim, const char* cor) {
    if (!pto_ini || !pto_fim || !cor) return NULL;

    Segmento_s* s = (Segmento_s*)malloc(sizeof(Segmento_s));
    if (s == NULL) return NULL;

    s->id = id;
    s->pto_ini = pto_ini;
    s->pto_fim = pto_fim;

    // Safe copy of the color (max 17 chars)
    strncpy(s->cor, cor, sizeof(s->cor) - 1);
    s->cor[sizeof(s->cor) - 1] = '\0';

    return (SegmentoT)s;
}

PontoT Segmento_get_ini(SegmentoT s) {
    if (!s) return NULL;
    return ((Segmento_s*)s)->pto_ini;
}

PontoT Segmento_get_fim(SegmentoT s) {
    if (!s) return NULL;
    return ((Segmento_s*)s)->pto_fim;
}

int Segmento_get_id(SegmentoT s) {
    if (!s) return -1;
    return ((Segmento_s*)s)->id;
}

const char* Segmento_get_cor(SegmentoT s) {
    if (!s) return NULL;
    return ((Segmento_s*)s)->cor;
}

void Segmento_Destruir(SegmentoT s) {
    if (s != NULL) {
        free((Segmento_s*)s);
    }
}
