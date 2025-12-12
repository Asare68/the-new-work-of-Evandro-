#include "circle.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int id;
    PontoT centro;
    double r;
    char corb[32];
    char corp[32];
} CirculoImpl;

CirculoT Circulo_Criar(int id, PontoT centro, double r, const char* corb, const char* corp) {
    CirculoImpl* c = (CirculoImpl*) malloc(sizeof(CirculoImpl));
    if (!c) return NULL;
    
    c->id = id;
    c->centro = centro; // Assume posse do ponteiro
    c->r = r;
    
    strncpy(c->corb, corb ? corb : "", 31);
    c->corb[31] = '\0';
    strncpy(c->corp, corp ? corp : "", 31);
    c->corp[31] = '\0';
    
    return (CirculoT) c;
}

void Circulo_Destruir(CirculoT c) {
    if (c) {
        CirculoImpl* impl = (CirculoImpl*) c;
        if (impl->centro) Ponto_Destruir(impl->centro);
        free(impl);
    }
}

// --- Getters necessários para o SVG Writer ---

int Circulo_GetId(CirculoT c) {
    return ((CirculoImpl*)c)->id;
}

PontoT Circulo_GetCentro(CirculoT c) {
    return ((CirculoImpl*)c)->centro;
}

double Circulo_GetRaio(CirculoT c) {
    return ((CirculoImpl*)c)->r;
}

const char* Circulo_GetCorB(CirculoT c) {
    return ((CirculoImpl*)c)->corb;
}

const char* Circulo_GetCorP(CirculoT c) {
    return ((CirculoImpl*)c)->corp;
}

SegmentoT Circulo_Transformar_Anteparo(CirculoT c, char orientacao) {
    (void)c;           // Fixa warning unused parameter
    (void)orientacao;  // Fixa warning unused parameter
    
    // Implementação futura: transforma círculo em segmento anteparo
    // Para visibilidade, círculo pode virar segmento tangente ou diâmetro
    return NULL;
}
