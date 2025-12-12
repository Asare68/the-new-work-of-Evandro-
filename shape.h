#ifndef SHAPE_H
#define SHAPE_H

typedef enum {
    TIPO_RETANGULO,
    TIPO_CIRCULO,
    TIPO_LINHA,
    TIPO_TEXTO
} TipoFormaT;
typedef void* FormaT;


FormaT Forma_Criar(int id, TipoFormaT tipo, void* figura);

int Forma_GetId(FormaT f);

TipoFormaT Forma_GetTipo(FormaT f);

void* Forma_GetFigura(FormaT f);

void Forma_Destruir(FormaT f);

#endif