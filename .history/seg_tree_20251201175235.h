#ifndef SEG_TREE_H
#define SEG_TREE_H
#include "point.h"
#include "segment.h"
#include "vertex.h"
typedef void* SegsAtvsT;
SegsAtvsT SegsAtvs_Criar(PontoT x_observador);
void SegsAtvs_ativaSegmento(SegsAtvsT tree, SegmentoT s);
void SegsAtvs_desativaSegmento(SegsAtvsT tree, SegmentoT s);
SegmentoT SegsAtvs_segAtivoMaisProx(SegsAtvsT tree, VerticeT v);
void SegsAtvs_Destruir(SegsAtvsT tree);
#endif // SEG_TREE_H
