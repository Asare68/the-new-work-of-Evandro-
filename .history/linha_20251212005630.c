#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linha.h"
#include "formas.h"

typedef struct{
    int i;
    double x1, y1, x2, y2;
    char *cor, *corcompl;
}linha;

void setCORCOMPLlinha(Linha l){
    int r, g, b;
    int Rcompl, Gcompl, Bcompl;
    char extra[2];
    char* p = ((linha*)l)->cor;
    sscanf(p, "%1s%2x%2x%2x",extra, &r, &g, &b);
    Rcompl = 255 - r;
    Gcompl = 255 - g;
    Bcompl = 255 - b;
    sprintf(((linha*)l)->corcompl, "#%X%X%X", Rcompl, Gcompl, Bcompl);
}

Linha criar_linha(int i, double x1, double y1, double  x2, double y2, char* cor){
    linha *l = malloc(sizeof(linha));
    l->i = i;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;

    l->cor = (char*)malloc(strlen(cor)+1);
    if (l->cor==NULL){
        printf("Erro ao alocar memoria para a cor da linha");
        exit(1);
    }
    strcpy(l->cor,cor);

    l->corcompl = (char*) malloc(strlen(cor)+1);
    if(l->corcompl == NULL){
        printf("Erro ao alocar memoria para a cor complementar da linha");
        exit(1);
    }
    setCORCOMPLlinha(l);

    return ((Linha*)l);
}

int getIlinha(Linha l){
    return ((linha*)l)->i;
}

double getX1linha(Linha l){
    return ((linha*)l)->x1;
}

double getY1linha(Linha l){
    return ((linha*)l)->y1;
}

double getX2linha(Linha l){
    return ((linha*)l)->x2;
}

double getY2linha(Linha l){
    return ((linha*)l)->y2;
}

char* getCORlinha(Linha l){
    return ((linha*)l)->cor;
}

char* getCORCOMPLlinha(Linha l){
    return ((linha*)l)->corcompl;
}

void setIlinha(Linha l, int i){
    ((linha*)l)->i =i;
}

void setX1linha(Linha l, double x1){
    ((linha*)l)->x1 = x1;
}

void setY1linha(Linha l, double y1){
    ((linha*)l)->y1 = y1;
}

void setX2linha(Linha l, double x2){
    ((linha*)l)->x2 = x2;
}

void setY2linha(Linha l, double y2){
    ((linha*)l)->y2 = y2;
}

void setCORlinha(Linha l, char* cor){
    strcpy(((linha*)l)->cor, cor);
}

double calcula_area_linha(Linha l){
    return (2 * sqrt(pow(((linha*)l)->x1 - ((linha*)l)->x2,2) + pow(((linha*)l)->y1 - ((linha*)l)->y2,2)));
}

void freeCorbLinha(Linha l){
    linha* var = (linha*)l;
    free(var->cor);
}

void freeCorpLinha(Linha l){
    linha* var = (linha*)l;
    free(var->corcompl);
}