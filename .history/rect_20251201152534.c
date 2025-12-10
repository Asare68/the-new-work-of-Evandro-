#include <stdlib.h>
#include <string.h>
#include "rect.h"
#include "segment.h"
#include "point.h"
#include "list.h"

// -----------------------------------------
// Internal struct definition
// -----------------------------------------
typedef struct {
    int id;
    PontoT ancora;     // (x, y) lower-left corner
    double w, h;       // width, height
    char cor_borda[32];
    char cor_preench[32];
} Retangulo_s;

// -----------------------------------------
// Constructor
// -----------------------------------------
RetanguloT Retangulo_Criar(int i, PontoT ancora, double w, double h,
                           const char* corb, const char* corp)
{
    Retangulo_s* r = malloc(sizeof(Retangulo_s));
    if (!r) return NULL;

    r->id = i;
    r->ancora = ancora;
    r->w = w;
    r->h = h;

    strncpy(r->cor_borda, corb, sizeof(r->cor_borda) - 1);
    r->cor_borda[sizeof(r->cor_borda) - 1] = '\0';

    strncpy(r->cor_preench, corp, sizeof(r->cor_preench) - 1);
    r->cor_preench[sizeof(r->cor_preench) - 1] = '\0';

    return (RetanguloT)r;
}

// -----------------------------------------
// Transform rectangle into 4 barrier segments
// -----------------------------------------
// Generates segments:
//  - bottom    →  (x, y) → (x+w, y)
//  - right     →  (x+w, y) → (x+w, y+h)
//  - top       →  (x, y+h) → (x+w, y+h)
//  - left      →  (x, y) → (x, y+h)
ListT Retangulo_Transformar_Anteparos(RetanguloT r)
{
    Retangulo_s* rect = (Retangulo_s*)r;
    ListT lst = List_Criar();
    if (!lst || !rect) return lst;

    double x = Ponto_get_x(rect->ancora);
    double y = Ponto_get_y(rect->ancora);

    PontoT p1, p2;
    SegmentoT s;

    // Bottom edge
    p1 = Ponto_Criar(x, y);
    p2 = Ponto_Criar(x + rect->w, y);
    s = Segmento_Criar(rect->id, p1, p2, rect->cor_borda);
    List_Inserir(lst, s);

    // Right edge
    p1 = Ponto_Criar(x + rect->w, y);
    p2 = Ponto_Criar(x + rect->w, y + rect->h);
    s = Segmento_Criar(rect->id, p1, p2, rect->cor_borda);
    List_Inserir(lst, s);

    // Top edge
    p1 = Ponto_Criar(x, y + rect->h);
    p2 = Ponto_Criar(x + rect->w, y + rect->h);
    s = Segmento_Criar(rect->id, p1, p2, rect->cor_borda);
    List_Inserir(lst, s);

    // Left edge
    p1 = Ponto_Criar(x, y);
    p2 = Ponto_Criar(x, y + rect->h);
    s = Segmento_Criar(rect->id, p1, p2, rect->cor_borda);
    List_Inserir(lst, s);

    return lst;
}

// -----------------------------------------
// Destructor
// -----------------------------------------
void Retangulo_Destruir(RetanguloT r)
{
    Retangulo_s* rect = (Retangulo_s*)r;
    free(rect);
}
