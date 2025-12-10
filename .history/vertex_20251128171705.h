#ifndef VERTEX_H
#define VERTEX_H

#include "point.h"
#include "segment.h"

// Vertex Codes
typedef enum { ORIG, ARTF, RE } CodigoT;

// Vertex Types
typedef enum { INICIO, FIM } TipoVerticeT;

// Opaque type
typedef void* VerticeT;

/*
 * Creates a Vertex.
 */
VerticeT Vertice_Criar(TipoVerticeT tipo, SegmentoT pSeg, PontoT ponto, CodigoT codigo);

/* Getters */
TipoVerticeT Vertice_get_tipo(VerticeT v);
SegmentoT    Vertice_get_segmento(VerticeT v);
PontoT       Vertice_get_ponto(VerticeT v);
CodigoT      Vertice_get_codigo(VerticeT v);

/*
 * Comparator for sweep algorithms.
 * PRIORITY:
 *  1) Angle
 *  2) Distance (FARTHER first)
 *  3) Type  (INICIO < FIM)
 */
int Vertice_Comparar(const void* a, const void* b, PontoT x_observador);

/* Destructor */
void Vertice_Destruir(VerticeT v);

#endif // VERTEX_H
