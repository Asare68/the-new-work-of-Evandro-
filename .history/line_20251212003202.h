#ifndef linha_h
#define linha_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "formas.h"

typedef void* Linha;

/*
    Arquivo .h relacionado a forma de uma linha, com funcoes de get, set e calculo de area
*/

/// @brief Calcula e define o valor hexadecimal da cor complementar da linha l
/// @param l A linha que tera sua cor lida
void setCORCOMPLlinha(Linha l);

/// @brief Cria uma linha com os valores dos parametros especificados
/// @param i O valor do identificador da linha
/// @param x1 O valor da coordenada x do inicio da linha
/// @param y1 O valor da coordenada y do inicio da linha
/// @param x2 O valor da coordenada x do fim da linha
/// @param y2 O valor da coordenada y do fim da linha
/// @param cor O valor haxadecimal da cor da linha
/// @return Retorna um ponteiro para a linha criada
Linha criar_linha(int i, double x1, double y1, double x2, double y2, char* cor);

/// @brief Pega o valor do identificador da linha l
/// @param l A linha que tera seu identificador lido
/// @return Retorna o valor do identificador da linha l
int getIlinha(Linha l);

/// @brief Pega o valor da coordenada x do inicio da linha l
/// @param l A linha que tera sua coordenada x de inicio lida
/// @return Retorna o valor da coordenada x do inicio da linha l
double getX1linha(Linha l);

/// @brief Pega o valor da coordenada y do inicio da linha l
/// @param l A linha que tera sua coordenada y do inicio lida
/// @return Retorna o valor da coordenada y do inicio da linha l
double getY1linha(Linha l);

/// @brief Pega o valor da coordenada x do fim da linha l
/// @param l A linha que tera sua coordenada x do fim lida
/// @return Retorna o valor da coordenada x do fim da linha l
double getX2linha(Linha l);

/// @brief Pega o valor da coordenada y do fim da linha l
/// @param l A linha que tera sua coordenada y do fim lida
/// @return Retorna o valor da coordenada y do fim da linha l
double getY2linha(Linha l);

/// @brief Pega o valor hexadecimal da cor da linha l
/// @param l A linha que tera sua cor lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor da linha l
char* getCORlinha(Linha l);

/// @brief Pega o valor hexadecimal da cor complementar da linha l
/// @param l A linha que tera sua cor lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor complementar da linha
char* getCORCOMPLlinha(Linha l);

/// @brief Define o valor do identificador da linha l
/// @param l A linha que tera seu identificador definido
/// @param i O valor do identificador da linha
void setIlinha(Linha l,int i);

/// @brief Define o valor da coordenada x de inicio da linha l
/// @param l A linha que tera sua coordenada x de incio definida
/// @param x1 O valor da coordenada x de inicio da linha
void setX1linha(Linha l,double x1);

/// @brief Define o valor da coordenada y de inicio da linha l
/// @param l A linha que tera sua coordenada y de inicio lida
/// @param y1 O valor da coordenada y de incio
void setY1linha(Linha l, double y1);

/// @brief Define o valor da coordenada x do fim da linha l
/// @param l A linha que tera sua coordenada x de fim lida
/// @param x2 O valor da coordenada x do fim da linha
void setX2linha(Linha l, double x2);

/// @brief Define o valor da coordenada y do fim da linha l
/// @param l A linha que tera sua coordenada y de fim lida
/// @param y2 O valor da coordenada y de fim da linha
void setY2linha(Linha l, double y2);

/// @brief Deifne o valor da cor hexadecimal da linha
/// @param l A linha que tera sua cor definida
/// @param cor O valor hexadecimal da cor da linha
void setCORlinha(Linha l, char* cor);

/// @brief Calcula e retorna a area da linha l
/// @param l A linha na qual tera sua area calculada
/// @return Retorna a area da linha
double calcula_area_linha(Linha l);

/// @brief Libera a memoria da cor de borda da linha
/// @param l A linha
void freeCorbLinha(Linha l);

/// @brief Libera a memoria da cor de preenchimento da linha
/// @param l A linha
void freeCorpLinha(Linha l);

#endif
