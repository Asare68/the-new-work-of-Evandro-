#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

// Opaque type for Segment (Barrier)
typedef void* SegmentoT;

/*
 * Creates an oriented Segment (pto_ini → pto_fim).
 * 'id' : segment identifier
 * 'cor': SVG color string (max 17 chars + '\0')
 */
SegmentoT Segmento_Criar(int id, PontoT pto_ini, PontoT pto_fim, const char* cor);

/* Getters */
PontoT Segmento_get_ini(SegmentoT s);
PontoT Segmento_get_fim(SegmentoT s);
int   Segmento_get_id(SegmentoT s);
const char* Segmento_get_cor(SegmentoT s);

/* Destructor */
void Segmento_Destruir(SegmentoT s);

#endif // SEGMENT_H
