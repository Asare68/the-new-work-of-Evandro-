#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circle.h"
#include "point.h"
#include "segment.h"

// -----------------------------------------------------
// Internal structure
// -----------------------------------------------------
typedef struct {
    int id;
    PontoT centro;
    double raio;
    char cor_borda[32];
    char cor_preench[32];
} Circulo_s;

// -----------------------------------------------------
// Constructor
// -----------------------------------------------------
CirculoT Circulo_Criar(int i, PontoT centro, double r, 
                       const char* corb, const char* corp) {
    Circulo_s* c = (Circulo_s*) malloc(sizeof(Circulo_s));
    if (!c) {
        fprintf(stderr, "Erro: Falha ao alocar Circulo.\n");
        exit(1);
    }

    c->id = i;
    c->centro = centro;
    c->raio = r;

    strncpy(c->cor_borda, corb, sizeof(c->cor_borda) - 1);
    strncpy(c->cor_preench, corp, sizeof(c->cor_preench) - 1);

    return c;
}

// -----------------------------------------------------
// Paint Bomb — setter
// -----------------------------------------------------
void Circulo_set_cor(CirculoT c, const char* nova_cor) {
    Circulo_s* circ = (Circulo_s*) c;
    strncpy(circ->cor_borda, nova_cor, sizeof(circ->cor_borda) - 1);
    strncpy(circ->cor_preench, nova_cor, sizeof(circ->cor_preench) - 1);
}

// -----------------------------------------------------
// Transformação em Anteparo (horiz / vert)
// -----------------------------------------------------
SegmentoT Circulo_Transformar_Anteparo(CirculoT c, char orientacao) {
    Circulo_s* circulo = (Circulo_s*) c;

    double cx = Ponto_get_x(circulo->centro);
    double cy = Ponto_get_y(circulo->centro);
    double r  = circulo->raio;

    PontoT p1, p2;

    if (orientacao == 'h') {
        // Horizontal segment on diameter
        p1 = Ponto_Criar(cx - r, cy);
        p2 = Ponto_Criar(cx + r, cy);

        return Segmento_Criar(circulo->id, p1, p2, circulo->cor_borda);

    } else if (orientacao == 'v') {
        // Vertical segment on diameter
        p1 = Ponto_Criar(cx, cy - r);
        p2 = Ponto_Criar(cx, cy + r);

        return Segmento_Criar(circulo->id, p1, p2, circulo->cor_borda);

    } else {
        fprintf(stderr, "Erro: orientacao invalida '%c'. Use 'h' ou 'v'.\n", orientacao);
        return NULL;
    }
}

// -----------------------------------------------------
// Destructor
// -----------------------------------------------------
void Circulo_Destruir(CirculoT c) {
    Circulo_s* circ = (Circulo_s*) c;
    free(circ);
}
