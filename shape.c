#include "shape.h"
#include <stdlib.h>

typedef struct {
    int id;
    TipoFormaT tipo;
    void* figura; 
} FormaImpl;

FormaT Forma_Criar(int id, TipoFormaT tipo, void* figura) {
    FormaImpl* f = (FormaImpl*) malloc(sizeof(FormaImpl));
    f->id = id;
    f->tipo = tipo;
    f->figura = figura;
    return (FormaT) f;
}

int Forma_GetId(FormaT f) {
    return ((FormaImpl*)f)->id;
}

TipoFormaT Forma_GetTipo(FormaT f) {
    return ((FormaImpl*)f)->tipo;
}

void* Forma_GetFigura(FormaT f) {
    return ((FormaImpl*)f)->figura;
}

void Forma_Destruir(FormaT f) {
    if (f) free(f);
}