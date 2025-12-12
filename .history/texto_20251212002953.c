#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"

typedef struct{
    char *family;
    char *weight;
    char *size;
}estilo;

typedef struct{
    int i;
    double x, y;
    char *corb, *corp, *txto;
    char a;
    estilo estiloTexto;
}texto;

Estilo criar_estilo(char* family, char* weight, char* size){
    estilo *ts = malloc(sizeof(estilo));
    ts->family = (char*)malloc(strlen(family)+1);
    if(ts->family==NULL){
        printf("Erro ao alocar memoria para a familia");
        exit(1);
    }
    strcpy(ts->family, family);

    ts->weight = (char*)malloc(strlen(weight)+1);
    if (ts->weight==NULL){
        printf("Erro ao alocar memoria para o weight");
        exit(1);
    }
    strcpy(ts->weight, weight);

    ts->size = (char*)malloc(strlen(size)+1);
    if(ts->size==NULL){
        printf("Erro ao alocr memoria para o tamanho");
        exit(1);
    }
    strcpy(ts->size,size);

    return ((estilo*)ts);
}

char* getFAMILY(Estilo ts){
    return ((estilo*)ts)->family;
}

char* getWEIGHT(Estilo ts){
    return ((estilo*)ts)->weight;
}

char* getSIZE (Estilo ts){
    return((estilo*)ts)->size;
}

void setFAMILY(Estilo ts, char* family){
    estilo* var = (estilo*) ts;
    strcpy(var->family, family);
}

void setWEIGHT(Estilo ts, char* weight){
    estilo* var = (estilo*) ts;
    strcpy(var->weight, weight);
}

void setSIZE(Estilo ts, char* size){
    estilo* var = (estilo*) ts;
    strcpy(var->size, size);
}

void freeEstilo(Estilo ts){
    estilo* var = (estilo*)ts;
    free(var->family);
    free(var->size);
    free(var->weight);
    free(var);
}

Texto criar_texto(int i, double x, double y, char* corb, char* corp, char a, char* txto){
    texto *t = malloc(sizeof(texto));
    t->i = i;
    t->x = x;
    t->y = y;
    t->a = a;

    t->corb = (char*)malloc(strlen(corb)+1);
    if(t->corb == NULL){
        printf("Erro ao alocar memoria para a cor do texto");
        exit(1);
    }
    strcpy(t->corb, corb);

    t->corp = (char*)malloc(strlen(corp)+1);
    if(t->corp == NULL){
        printf("Erro ao alocar memoria para a cor complementar do texto");
        exit(1);
    }
    strcpy(t->corp, corp);

    t->txto = (char*)malloc(strlen(txto)+1);
    if(t->txto==NULL){
        printf("Erro ao alocar memoria para o texto do texto");
        exit(1);
    }
    strcpy(t->txto,txto);

    return ((texto*)t);
}

int getItexto(Texto t){
    return ((texto*)t)->i;
}

double getXtexto(Texto t){
    return ((texto*)t)->x;
}

double getYtexto(Texto t){
    return ((texto*)t)->y;
}

char* getCORBtexto(Texto t){
    return ((texto*)t)->corb;
}

char* getCORPtexto(Texto t){
    return ((texto*)t)->corp;
}

char getAtexto(Texto t){
    return ((texto*)t)->a;
}

char* getTXTOtexto(Texto t){
    return ((texto*)t)->txto;
}

void setItexto(Texto t, int i){
    ((texto*)t)->i = i;
}

void setXtexto(Texto t, double x){
    ((texto*)t)->x = x;
}

void setYtexto(Texto t, double y){
    ((texto*)t)->y = y;
}

void setCORBtexto(Texto t, char* corb){
    strcpy(((texto*)t)->corb, corb);
}

void setCORPtexto(Texto t, char* corp){
    strcpy(((texto*)t)->corp, corp);
}

void setAtexto(Texto t, char a){
    ((texto*)t)->a = a;
}

void setTXTOtexto(Texto t, char* txto){
    strcpy(((texto*)t)->txto, txto);
}

double calcula_area_texto(Texto t){
    return (20 * strlen(((texto*)t)->txto));
}

void freeCorbTexto(Texto t){
    texto* var = (texto*)t;
    free(var->corb);
}

void freeCorpTexto(Texto t){
    texto* var = (texto*)t;
    free(var->corp);
}

void freeTXTOtexto(Texto t){
    texto* var = (texto*) t;
    free(var->txto);
}