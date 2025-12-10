#ifndef VERTEX_H
#define VERTEX_H

#include "point.h"
#include "segment.h"

/* Enumerations for vertex codes and types */
typedef enum { ORIG, ARTF, RE } CodigoT;
typedef enum { INICIO, FIM } TipoVerticeT;

/* Opaque vertex type */
typedef void* VerticeT;

/* Vertex creation and destruction */
VerticeT Vertice_Criar(TipoVerticeT tipo, SegmentoT pSeg, PontoT ponto, CodigoT codigo);
void Vertice_Destruir(VerticeT v);

/* Getters */
TipoVerticeT Vertice_get_tipo(VerticeT v);
SegmentoT    Vertice_get_segmento(VerticeT v);
PontoT       Vertice_get_ponto(VerticeT v);
CodigoT      Vertice_get_codigo(VerticeT v);

/* Comparator: arguments are pointers to list elements; ctx is PontoT observer */
int Vertice_Comparar(const void* a, const void* b, void* x_observador);

/* Angle function: computes angle between observer and another point */
double ang(PontoT x, PontoT v);

#endif // VERTEX_H
