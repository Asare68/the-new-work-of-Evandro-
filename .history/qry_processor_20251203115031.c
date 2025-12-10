#include "qry_processor.h"
#include "vis_alg.h"
#include "segment.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Minimal QRY processor stub:
   - supports a command "d x y" that computes visibility from (x,y) and writes a simple output svg and txt (stub)
*/

int QryProcessor_Processar(const char* caminho_qry, ListT formas, const char* bsd) {
      /* unused for now */   
    if (!caminho_qry || !formas) return -1;
    FILE* f = fopen(caminho_qry, "r");
    if (!f) return -1;
    char cmd[32];
    while (fscanf(f, "%31s", cmd) == 1) {
        if (strcmp(cmd, "d") == 0) {
            double x,y;
            if (fscanf(f, "%lf %lf", &x, &y) == 2) {
                PontoT obs = Ponto_Criar(x,y);
                ListT V = CalculeVisibilidade(formas, obs);
                /* In a real program we would write outputs to files; for now print summary */
                printf("[QRY] d %.2f %.2f -> V segments: %d\n", x, y, List_Tamanho(V));
                /* destroy V and observer */
                List_Destruir(V);
                Ponto_Destruir(obs);
            }
        } else {
            /* skip rest of line */
            char line[256];
            fgets(line, sizeof(line), f);
        }
    }
    fclose(f);
    return 0;
}
