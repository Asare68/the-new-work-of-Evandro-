#ifndef LIST_H
#define LIST_H
#include <stddef.h>
typedef void* ListT;
ListT List_Criar(void);
void List_Inserir(ListT lst, void* item);
void* List_Buscar(ListT lst, int id_ou_criterio);
void List_Destruir(ListT lst);
ListT List_ExtrairVertices(ListT segmentos_S);
/* Helpers for vis_alg */
void List_Ordenar(ListT lst, void* ctx, int (*compar)(const void*, const void*, void*));
int List_Tamanho(ListT lst);
void* List_Obter(ListT lst, int idx);
#endif // LIST_H
