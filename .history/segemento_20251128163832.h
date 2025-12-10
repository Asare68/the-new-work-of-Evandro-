// segment.h
#ifndef SEGMENT_H
#define SEGMENT_H
#include "point.h"
// Opaque type for Segment (Barrier)
typedef void* SegmentoT;
/*
* Creates an oriented Segment (pto_ini, pto_fim) [5].
* The sequence x, pto-ini, pto-fim must be a "left turn" [5].
*/
SegmentoT Segmento_Criar(int id, PontoT pto_ini, PontoT pto_fim,
const char* cor);
/* Getters */
PontoT Segmento_get_ini(SegmentoT s); // pto-ini