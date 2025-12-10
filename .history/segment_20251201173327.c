#include "../include/segment.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    PontoT ini;
    PontoT fim;
    char cor[32];
} Segmento_s;

SegmentoT Segmento_Criar(int id, PontoT pto_ini, PontoT pto_fim, const char* cor) {
    Segmento_s* s = (Segmento_s*)malloc(sizeof(Segmento_s));
    if (!s) return NULL;
    s->id = id;
    s->ini = pto_ini;
    s->fim = pto_fim;
    strncpy(s->cor, cor ? cor : "black", sizeof(s->cor)-1);
    s->cor[sizeof(s->cor)-1] = '\0';
    return (SegmentoT)s;
}

PontoT Segmento_get_ini(SegmentoT s){ return s?((Segmento_s*)s)->ini:NULL; }
PontoT Segmento_get_fim(SegmentoT s){ return s?((Segmento_s*)s)->fim:NULL; }
int Segmento_get_id(SegmentoT s){ return s?((Segmento_s*)s)->id:-1; }
const char* Segmento_get_cor(SegmentoT s){ return s?((Segmento_s*)s)->cor:NULL; }

void Segmento_Destruir(SegmentoT s){
    if (!s) return;
    Segmento_s* ss = (Segmento_s*)s;
    /* ownership policy: points are not freed here - they may be shared */
    free(ss);
}

SegmentoT Segmento_Clone(SegmentoT s) {
    if (!s) return NULL;
    Segmento_s* ss = (Segmento_s*)s;
    return Segmento_Criar(ss->id, ss->ini, ss->fim, ss->cor);
}
