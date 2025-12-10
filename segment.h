#ifndef SEGMENT_H
#define SEGMENT_H
#include "point.h"
typedef void* SegmentoT;
SegmentoT Segmento_Criar(int id, PontoT pto_ini, PontoT pto_fim, const char* cor);
PontoT Segmento_get_ini(SegmentoT s);
PontoT Segmento_get_fim(SegmentoT s);
int Segmento_get_id(SegmentoT s);
const char* Segmento_get_cor(SegmentoT s);
void Segmento_Destruir(SegmentoT s);
SegmentoT Segmento_Clone(SegmentoT s);
#endif // SEGMENT_H
