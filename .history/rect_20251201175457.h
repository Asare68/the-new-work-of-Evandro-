#ifndef RECT_H
#define RECT_H
#include "point.h"
#include "list.h"
typedef void* RetanguloT;
RetanguloT Retangulo_Criar(int i, PontoT ancora, double w, double h, const char* corb, const char* corp);
ListT Retangulo_Transformar_Anteparos(RetanguloT r);
void Retangulo_Destruir(RetanguloT r);
#endif // RECT_H
