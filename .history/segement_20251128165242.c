// segment.c
#include <stdlib.h>
#include <string.h>
#include "segment.h"
// Struct definition
typedef struct {
 int id;
 PontoT pto_ini;
 PontoT pto_fim;
 char cor[18]; // Assuming SVG color string storage
} Segmento_s;
SegmentoT Segmento_Criar(int id, PontoT pto_ini, PontoT pto_fim,
const char* cor) {
 Segmento_s* s = (Segmento_s*)malloc(sizeof(Segmento_s));
 if (s == NULL) return NULL;

 s->id = id;
 s->pto_ini = pto_ini;
 s->pto_fim = pto_fim;
 strncpy(s->cor, cor, 49);

 return (SegmentoT)s;
}
// ... Implementation of Getters and Destructor ...