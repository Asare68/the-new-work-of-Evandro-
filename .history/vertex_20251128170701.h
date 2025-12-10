// vertex.h
#ifndef VERTEX_H
#define VERTEX_H
#include "point.h"
#include "segment.h"
// Vertex Codes (codigo) [5]
typedef enum { ORIG, ARTF, RE } CodigoT; // ORIGINAL, ARTIFICIAL,
ENCLOSING RECTANGLE
// Vertex Types (tipo) [19]
typedef enum { INICIO, FIM } TipoVerticeT; // START, END
// Opaque type for Vertex (vertice)
typedef void* VerticeT;
/*
* Creates a Vertex object.
* tipo: start or end [19]
* pSeg: pointer to the segment it belongs to [19]
* ponto: coordinates (x, y) [19]
* codigo: ORIG, ARTF, or RE [5]
*/
VerticeT Vertice_Criar(TipoVerticeT tipo, SegmentoT pSeg, PontoT
ponto, CodigoT codigo);
/* Getters */
TipoVerticeT Vertice_get_tipo(VerticeT v);
SegmentoT Vertice_get_segmento(VerticeT v);