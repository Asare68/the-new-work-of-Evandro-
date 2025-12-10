#include "rect.h"
#include "segment.h"
#include "point.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    PontoT ancora;
    double w, h;
    char corb[32];
    char corp[32];
} Retangulo_s;

RetanguloT Retangulo_Criar(int i, PontoT ancora, double w, double h, const char* corb, const char* corp) {
    Retangulo_s* r = (Retangulo_s*)malloc(sizeof(Retangulo_s));
    if (!r) return NULL;
    r->id = i; r->ancora = ancora; r->w = w; r->h = h;
    strncpy(r->corb, corb?corb:"black", sizeof(r->corb)-1); r->corb[31] = '\0';
    strncpy(r->corp, corp?corp:"white", sizeof(r->corp)-1); r->corp[31] = '\0';
    return (RetanguloT)r;
}

ListT Retangulo_Transformar_Anteparos(RetanguloT r0) {
    if (!r0) return NULL;
    Retangulo_s* r = (Retangulo_s*)r0;
    ListT lst = List_Criar();
    double x = Ponto_get_x(r->ancora);
    double y = Ponto_get_y(r->ancora);

    PontoT p1 = Ponto_Criar(x, y);
    PontoT p2 = Ponto_Criar(x + r->w, y);
    PontoT p3 = Ponto_Criar(x + r->w, y + r->h);
    PontoT p4 = Ponto_Criar(x, y + r->h);

    List_Inserir(lst, Segmento_Criar(r->id, p1, p2, r->corb));
    List_Inserir(lst, Segmento_Criar(r->id, p2, p3, r->corb));
    List_Inserir(lst, Segmento_Criar(r->id, p4, p3, r->corb));
    List_Inserir(lst, Segmento_Criar(r->id, p1, p4, r->corb));
    return lst;
}

void Retangulo_Destruir(RetanguloT r) { if (r) free((Retangulo_s*)r); }
