

/* Headers das formas específicas */
#include "rect.h"
#include "circle.h"
#include "segment.h"
#include "point.h"
#include "geo_parser.h"

/* O nosso novo "Envelope" Genérico */
#include "shape.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int GeoParser_Ler(const char* caminho_geo, ListT formas) {
    if (!caminho_geo || !formas) return -1;

    FILE* f = fopen(caminho_geo, "r");
    if (!f) return -1;

    char cmd[32];
    while (fscanf(f, "%31s", cmd) == 1) {
        

        if (strcmp(cmd, "r") == 0) {
            int id; 
            double x, y, w, h; 
            char corb[32], corp[32];
        
            if (fscanf(f, "%d %lf %lf %lf %lf %31s %31s", &id, &x, &y, &w, &h, corb, corp) == 7) {
            
                PontoT ancora = Ponto_Criar(x, y);
                RetanguloT r = Retangulo_Criar(id, ancora, w, h, corb, corp);
               
                FormaT forma = Forma_Criar(id, TIPO_RETANGULO, r);
          
                List_Inserir(formas, forma);
            }
        } 
   
        else if (strcmp(cmd, "c") == 0) {
            int id; 
            double x, y, raio; 
            char corb[32], corp[32];
            
            if (fscanf(f, "%d %lf %lf %lf %31s %31s", &id, &x, &y, &raio, corb, corp) == 6) {
                // 1. Cria o centro e o objeto Círculo
                PontoT centro = Ponto_Criar(x, y);
                CirculoT c = Circulo_Criar(id, centro, raio, corb, corp);
                
                // 2. Embrulha no envelope Genérico
                FormaT forma = Forma_Criar(id, TIPO_CIRCULO, c);
                
                // 3. Guarda na lista
                List_Inserir(formas, forma);
            }
        }
      
        else if (strcmp(cmd, "l") == 0) { 
             int id;
             double x1, y1, x2, y2;
             char cor[32];
             
             if (fscanf(f, "%d %lf %lf %lf %lf %31s", &id, &x1, &y1, &x2, &y2, cor) == 6) {
                 PontoT p1 = Ponto_Criar(x1, y1);
                 PontoT p2 = Ponto_Criar(x2, y2);
                 
                 SegmentoT s = Segmento_Criar(id, p1, p2, cor);
                 FormaT forma = Forma_Criar(id, TIPO_LINHA, s);
                 
                 List_Inserir(formas, forma);
             }
        }
     
        else {
            // Consome o resto da linha para não quebrar o parser
            char buffer[256]; 
            fgets(buffer, sizeof(buffer), f);
        }
    }

    fclose(f);
    return 0;
}