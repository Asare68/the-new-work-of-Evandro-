#include "svg_writer.h"
#include "shape.h"
#include "rect.h"
#include "circle.h"
#include "segment.h"
#include "point.h"
#include <stdio.h>

int SvgWriter_Gerar(const char* caminho_svg, ListT formas) {
    if (!caminho_svg || !formas) return -1;
    FILE* f = fopen(caminho_svg, "w");
    if (!f) return -1;

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    int n = List_Tamanho(formas);
    for (int i = 0; i < n; ++i) {
        FormaT forma = (FormaT) List_Obter(formas, i);
        TipoFormaT tipo = Forma_GetTipo(forma);
        void* objeto = Forma_GetFigura(forma);

        switch(tipo) {
            case TIPO_RETANGULO: {
                RetanguloT r = (RetanguloT) objeto;
                PontoT ancora = Retangulo_GetAncora(r);
                // Desenha Retângulo: x, y, width, height, stroke (borda), fill (preenchimento)
                fprintf(f, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" "
                           "stroke=\"%s\" fill=\"%s\" opacity=\"0.8\" />\n",
                        Ponto_get_x(ancora),
                        Ponto_get_y(ancora),
                        Retangulo_GetW(r),
                        Retangulo_GetH(r),
                        Retangulo_GetCorB(r),
                        Retangulo_GetCorP(r));
                break;
            }

            case TIPO_CIRCULO: {
                CirculoT c = (CirculoT) objeto;
                PontoT centro = Circulo_GetCentro(c);
                // Desenha Círculo: cx, cy, r, stroke, fill
                fprintf(f, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" "
                           "stroke=\"%s\" fill=\"%s\" opacity=\"0.8\" />\n",
                        Ponto_get_x(centro),
                        Ponto_get_y(centro),
                        Circulo_GetRaio(c),
                        Circulo_GetCorB(c),
                        Circulo_GetCorP(c));
                break;
            }

            case TIPO_LINHA: {
                SegmentoT s = (SegmentoT) objeto;
                PontoT p1 = Segmento_get_ini(s);
                PontoT p2 = Segmento_get_fim(s);
                fprintf(f, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n",
                        Ponto_get_x(p1), Ponto_get_y(p1), 
                        Ponto_get_x(p2), Ponto_get_y(p2), 
                        Segmento_get_cor(s));
                break;
            }
            
            case TIPO_TEXTO:
    
                break;
        }
    }

    fprintf(f, "</svg>\n");
    fclose(f);
    return 0;
}