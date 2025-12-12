#include "rect.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int id;
    PontoT ancora; 
    double w;
    double h;
    char corb[32];
    char corp[32];
} RetanguloImpl;

RetanguloT Retangulo_Criar(int id, PontoT ancora, double w, double h, const char* corb, const char* corp) {
    RetanguloImpl* r = (RetanguloImpl*) malloc(sizeof(RetanguloImpl));
    if (!r) return NULL;

    r->id = id;
    r->ancora = ancora; 

    r->w = w;
    r->h = h;
    
    if (corb) strncpy(r->corb, corb, 31); else r->corb[0] = '\0';
    r->corb[31] = '\0';
    
    if (corp) strncpy(r->corp, corp, 31); else r->corp[0] = '\0';
    r->corp[31] = '\0';

    return (RetanguloT) r;
}

void Retangulo_Destruir(RetanguloT r) {
    if (r) {
        RetanguloImpl* impl = (RetanguloImpl*) r;
        if (impl->ancora) Ponto_Destruir(impl->ancora);
        free(impl);
    }
}


int Retangulo_GetId(RetanguloT r) {
    return ((RetanguloImpl*)r)->id;
}

PontoT Retangulo_GetAncora(RetanguloT r) {
    return ((RetanguloImpl*)r)->ancora;
}

double Retangulo_GetW(RetanguloT r) {
    return ((RetanguloImpl*)r)->w;
}

double Retangulo_GetH(RetanguloT r) {
    return ((RetanguloImpl*)r)->h;
}

const char* Retangulo_GetCorB(RetanguloT r) {
    return ((RetanguloImpl*)r)->corb;
}

const char* Retangulo_GetCorP(RetanguloT r) {
    return ((RetanguloImpl*)r)->corp;
}

/* Lógica crucial para o trabalho: 
   Converte o retângulo em 4 linhas (segmentos) para o cálculo de visibilidade.
*/
ListT Retangulo_Transformar_Anteparos(RetanguloT r) {
    RetanguloImpl* rect = (RetanguloImpl*) r;
    ListT lista_seg = List_Criar(); 

    double x = Ponto_get_x(rect->ancora);
    double y = Ponto_get_y(rect->ancora);
    double w = rect->w;
    double h = rect->h;

    // Criar os 4 vértices
    PontoT p1 = Ponto_Criar(x, y);        
    PontoT p2 = Ponto_Criar(x + w, y);    
    PontoT p3 = Ponto_Criar(x + w, y + h); // Superior Direito
    PontoT p4 = Ponto_Criar(x, y + h);     // Superior Esquerdo

    // Criar os 4 segmentos (anteparos)
    // ID do segmento geralmente é derivado do ID do retângulo ou novo. 
    // Aqui usamos o ID do retângulo para manter o rastreio.
    SegmentoT s1 = Segmento_Criar(rect->id, p1, p2, rect->corb); // Base
    SegmentoT s2 = Segmento_Criar(rect->id, p2, p3, rect->corb); // Direita
    SegmentoT s3 = Segmento_Criar(rect->id, p3, p4, rect->corb); // Topo
    SegmentoT s4 = Segmento_Criar(rect->id, p4, p1, rect->corb); // Esquerda

    List_Inserir(lista_seg, s1);
    List_Inserir(lista_seg, s2);
    List_Inserir(lista_seg, s3);
    List_Inserir(lista_seg, s4);

    return lista_seg;
}