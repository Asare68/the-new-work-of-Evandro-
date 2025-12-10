#include "../include/circle.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    PontoT centro;
    double raio;
    char corb[32];
    char corp[32];
} Circulo_s;

CirculoT Circulo_Criar(int i, PontoT centro, double r, const char* corb, const char* corp) {
    Circulo_s* c = (Circulo_s*)malloc(sizeof(Circulo_s));
    if (!c) return NULL;
    c->id = i;
    c->centro = centro;
    c->raio = r;
    strncpy(c->corb, corb?corb:"black", sizeof(c->corb)-1); c->corb[31] = '\0';
    strncpy(c->corp, corp?corp:"white", sizeof(c->corp)-1); c->corp[31] = '\0';
    return (CirculoT)c;
}

SegmentoT Circulo_Transformar_Anteparo(CirculoT c, char orientacao) {
    if (!c) return NULL;
    Circulo_s* circ = (Circulo_s*)c;
    double cx = Ponto_get_x(circ->centro);
    double cy = Ponto_get_y(circ->centro);
    double r = circ->raio;
    PontoT p1, p2;
    if (orientacao == 'h') {
        p1 = Ponto_Criar(cx - r, cy);
        p2 = Ponto_Criar(cx + r, cy);
    } else {
        p1 = Ponto_Criar(cx, cy - r);
        p2 = Ponto_Criar(cx, cy + r);
    }
    return Segmento_Criar(circ->id, p1, p2, circ->corb);
}

void Circulo_set_cor(CirculoT c, const char* nova_cor) {
    if (!c) return;
    Circulo_s* circ = (Circulo_s*)c;
    strncpy(circ->corp, nova_cor?nova_cor:"", sizeof(circ->corp)-1);
    circ->corp[31] = '\0';
}

void Circulo_Destruir(CirculoT c) {
    if (!c) return;
    free((Circulo_s*)c);
}
