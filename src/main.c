#include <stdio.h>
#include "tipos.h"
#include "entrada.h"
#include "forca_bruta.h"
#include "guloso.h"

// Imprime "<nome>: <qtd> testes, <ids>" usando os índices escolhidos
static void imprimir_selecao(const char *nome, const Matriz *mat,
                             const int escolhidos[], int qtd) {
    printf("%s: %d testes,", nome, qtd);
    for (int k = 0; k < qtd; k++) {
        printf(" %s", mat->id_teste[escolhidos[k]]);
    }
    printf("\n");
}

int main() {
    Matriz mat = {0};

    // 1. Lê e valida a entrada (a função imprime o motivo se for inválida)
    if (!entrada(&mat)) {
        return 1;
    }

    // 2. Força bruta. Ela já verifica a viabilidade e devolve -1 se algum
    //    requisito não for coberto por nenhum teste (a mensagem já foi impressa)
    int exato[MAX_TESTES];
    int qtd_exato = forca_bruta(&mat, exato);
    if (qtd_exato == -1) {
        return 0;   // cobertura impossível: não executa o guloso
    }

    // 3. Guloso
    int gul[MAX_TESTES];
    int qtd_gul = guloso(&mat, gul);

    // 4. Saída das duas estratégias
    imprimir_selecao("Forca bruta", &mat, exato, qtd_exato);
    imprimir_selecao("Guloso", &mat, gul, qtd_gul);

    // 5. Comparação
    if (qtd_gul == qtd_exato) {
        printf("Quantidade do guloso igual ao minimo: sim\n");
        printf("Testes adicionais: 0\n");
    } else {
        printf("Quantidade do guloso igual ao minimo: nao\n");
        printf("Testes adicionais: %d\n", qtd_gul - qtd_exato);
    }

    return 0;
}