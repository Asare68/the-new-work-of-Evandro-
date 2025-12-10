#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// ---- Internal project modules ----
#include "list.h"
#include "point.h"
#include "geo_parser.h"
#include "qry_processor.h"
#include "svg_writer.h"

// --------------------------------------
typedef struct {
    char *bed;        // -e base input directory
    char *arq_geo;    // -f file.geo
    char *bsd;        // -o output directory
    char *arq_qry;    // -q file.qry
    char *tipo_ord;   // -t ordering
    int n_insercao;   // -i integer
} ConfigT;

// ---- prototypes ----
void parse_args(int argc, char **argv, ConfigT *config);
void init_config(ConfigT *config);
char *concat_path(const char *dir, const char *file);
void construir_caminhos(ConfigT *config,
                        char **caminho_geo,
                        char **caminho_qry,
                        char **caminho_svg_final);

// ========================================
// MAIN
// ========================================
int main(int argc, char *argv[]) {

    ConfigT config;
    init_config(&config);
    parse_args(argc, argv, &config);

    if (!config.arq_geo || !config.bsd) {
        fprintf(stderr, "ERRO: -f <arquivo.geo> e -o <saida> sao obrigatorios.\n");
        return EXIT_FAILURE;
    }

    char *caminho_geo = NULL;
    char *caminho_qry = NULL;
    char *caminho_svg_final = NULL;

    construir_caminhos(&config, &caminho_geo, &caminho_qry, &caminho_svg_final);

    ListT formas_geometricas = List_Criar();

    // ---------------- GEO ------------------
    printf("Lendo GEO: %s\n", caminho_geo);

    if (GeoParser_Ler(caminho_geo, formas_geometricas) != 0) {
        fprintf(stderr, "Erro ao ler arquivo GEO.\n");
        List_Destruir(formas_geometricas);
        free(caminho_geo);
        free(caminho_qry);
        free(caminho_svg_final);
        return EXIT_FAILURE;
    }

    // -------------- SVG inicial ------------
    SvgWriter_Gerar(caminho_svg_final, formas_geometricas);

    // ---------------- QRY ------------------
    if (config.arq_qry) {
        printf("Processando QRY: %s\n", caminho_qry);

        if (QryProcessor_Processar(caminho_qry, formas_geometricas, config.bsd) != 0) {
            fprintf(stderr, "Erro ao processar QRY.\n");
            List_Destruir(formas_geometricas);
            free(caminho_geo);
            free(caminho_qry);
            free(caminho_svg_final);
            return EXIT_FAILURE;
        }
    }

    // ------------- cleanup -----------------
    List_Destruir(formas_geometricas);

    free(caminho_geo);
    free(caminho_qry);
    free(caminho_svg_final);

    printf("Execução finalizada com sucesso!\n");
    return EXIT_SUCCESS;
}

// ========================================
// Arg parsing
// ========================================
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
            default:
                fprintf(stderr, "Argumento inválido.\n");
                break;
        }
    }
}

void init_config(ConfigT *config) {
    config->bed = NULL;
    config->arq_geo = NULL;
    config->bsd = NULL;
    config->arq_qry = NULL;
    config->tipo_ord = strdup("q");
    config->n_insercao = 10;
}

// ========================================
// Path functions
// ========================================
char *concat_path(const char *dir, const char *file) {
    if (!dir) return strdup(file);

    size_t len = strlen(dir) + strlen(file) + 4;
    char *res = malloc(len);

    if (dir[strlen(dir) - 1] == '/')
        sprintf(res, "%s%s", dir, file);
    else
        sprintf(res, "%s/%s", dir, file);

    return res;
}

void construir_caminhos(ConfigT *config,
                        char **caminho_geo,
                        char **caminho_qry,
                        char **caminho_svg_final)
{
    // full GEO path
    if (config->bed)
        *caminho_geo = concat_path(config->bed, config->arq_geo);
    else
        *caminho_geo = strdup(config->arq_geo);

    // full QRY path
    if (config->arq_qry) {
        if (config->bed)
            *caminho_qry = concat_path(config->bed, config->arq_qry);
        else
            *caminho_qry = strdup(config->arq_qry);
    } else {
        *caminho_qry = NULL;
    }

    // base name for SVG
    char nome_base[256];
    strcpy(nome_base, config->arq_geo);

    char *dot = strrchr(nome_base, '.');
    if (dot) *dot = '\0';

    char svg_out[300];
    sprintf(svg_out, "%s_geo.svg", nome_base);

    *caminho_svg_final = concat_path(config->bsd, svg_out);
}
