#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "list.h"
#include "point.h"
#include "geo_parser.h"
#include "qry_processor.h"
#include "svg_writer.h"

typedef struct {
    char *bed;
    char *arq_geo;
    char *bsd;
    char *arq_qry;
    char *tipo_ord;
    int n_insercao;
} ConfigT;

void parse_args(int argc, char **argv, ConfigT *config);
void init_config(ConfigT *config);
char *concat_path(const char *dir, const char *file);
void construir_caminhos(ConfigT *config, char **caminho_geo, char **caminho_qry, char **caminho_svg_final);

int main(int argc, char *argv[]) {
    ConfigT config;
    init_config(&config);
    parse_args(argc, argv, &config);

    if (!config.arq_geo || !config.bsd) {
        fprintf(stderr, "ERRO: -f <arquivo.geo> e -o <saida> sao obrigatorios.\n");
        return EXIT_FAILURE;
    }

    char *caminho_geo = NULL, *caminho_qry = NULL, *caminho_svg_final = NULL;
    construir_caminhos(&config, &caminho_geo, &caminho_qry, &caminho_svg_fin
        


    ListT formas = List_Criar();

    printf("Lendo GEO: %s\n", caminho_geo);
    if (GeoParser_Ler(caminho_geo, formas) != 0) {
        fprintf(stderr, "Erro ao ler .geo\n");
        List_Destruir(formas);
        free(caminho_geo); free(caminho_qry); free(caminho_svg_final);
        return EXIT_FAILURE;
    }
    printf("Gerando SVG em: %s\n", caminho_svg_final);


    SvgWriter_Gerar(caminho_svg_final, formas);

    if (config.arq_qry) {
        printf("Processando QRY: %s\n", caminho_qry);
        QryProcessor_Processar(caminho_qry, formas, config.bsd);
    }

    List_Destruir(formas);
    free(caminho_geo); free(caminho_qry); free(caminho_svg_final);
    printf("Execucao finalizada.\n");
    return EXIT_SUCCESS;
}

void parse_args(int argc, char **argv, ConfigT *config) {
    int opt;
    while ((opt = getopt(argc, argv, "e:f:o:q:t:i:")) != -1) {
        switch (opt) {
            case 'e': config->bed = strdup(optarg); break;
            case 'f': config->arq_geo = strdup(optarg); break;
            case 'o': config->bsd = strdup(optarg); break;
            case 'q': config->arq_qry = strdup(optarg); break;
            case 't': config->tipo_ord = strdup(optarg); break;
            case 'i': config->n_insercao = atoi(optarg); break;
            default: break;
        }
    }
}

void init_config(ConfigT *config) {
    config->bed = NULL; config->arq_geo = NULL; config->bsd = NULL;
    config->arq_qry = NULL; config->tipo_ord = strdup("q"); config->n_insercao = 10;
}

char *concat_path(const char *dir, const char *file) {
    if (!dir) return strdup(file);
    size_t len = strlen(dir) + strlen(file) + 2;
    char *buf = (char*)malloc(len);
    if (dir[strlen(dir)-1] == '/') snprintf(buf, len, "%s%s", dir, file);
    else snprintf(buf, len, "%s/%s", dir, file);
    return buf;
}

void construir_caminhos(ConfigT *config, char **caminho_geo, char **caminho_qry, char **caminho_svg_final) {
    if (config->bed) *caminho_geo = concat_path(config->bed, config->arq_geo);
    else *caminho_geo = strdup(config->arq_geo);
    if (config->arq_qry) {
        if (config->bed) *caminho_qry = concat_path(config->bed, config->arq_qry);
        else *caminho_qry = strdup(config->arq_qry);
    } else *caminho_qry = NULL;
    char base[256]; 
    const char *filename = strrchr(config->arq_geo, '/');
   if (filename)
    filename++;  
else
    filename = config->arq_geo;

    strcpy(base, filename);
    char *dot = strrchr(base, '.'); if (dot) *dot = '\0';
    char svgname[300]; snprintf(svgname, sizeof(svgname), "%s_geo.svg", base);
    *caminho_svg_final = concat_path(config->bsd, svgname);
}
