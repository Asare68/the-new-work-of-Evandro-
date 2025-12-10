#ifndef VERTEX_H
#define VERTEX_H
#include "point.h"
#include "segment.h"
typedef enum { ORIG, ARTF, RE } CodigoT;
typedef enum { INICIO, FIM } TipoVerticeT;
typedef void* VerticeT;
VerticeT Vertice_Criar(TipoVerticeT tipo, SegmentoT pSeg, PontoT ponto, CodigoT codigo);
TipoVerticeT Vertice_get_tipo(VerticeT v);
SegmentoT Vertice_get_segmento(VerticeT v);
PontoT Vertice_get_ponto(VerticeT v);
CodigoT Vertice_get_codigo(VerticeT v);
/* comparator: arguments are pointers to list elements; ctx is PontoT observer */
int Vertice_Comparar(const void* a, const void* b, void* x_observador);
void Vertice_Destruir(VerticeT v);
#endif // VERTEX_H
