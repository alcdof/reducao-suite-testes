#include <stdio.h>
#include "tipos.h"
#include "forca_bruta.h"

// Verifica se eh possivel cobrir todos os requisitos
// Retorna 1 se possivel e 0 se impossivel
int verifica_possibilidade(const Matriz *mat) {
    int possivel = 1; // Flag que controla se o problema tem solucao

    // Avanca coluna por coluna (requisitos)
    for (int j = 0; j < mat->m; j++) {
        // Assume inicialmente que temos apenas 0 no requisito atual
        int coberto = 0;

        // Desce linha por linha (testes) da coluna atual
        for (int i = 0; i < mat->n; i++) {
            // Se achar um "1", o requisito esta coberto
            if (mat->cobre[i][j] == 1) {
                coberto = 1; 
                break; // Nao eh necessario testar outras linhas da mesma coluna, ja encontrou o "1"
            }
        }

        // Se saiu do loop das linhas e coberto continuou 0, a coluna eh vazia
        // Esta verificacao deve ficar DENTRO do loop das colunas para avaliar cada 'j' corretamente
        if (coberto == 0) {
            // Primeiro erro encontrado, imprime o aviso inicial
            if (possivel == 1) {
                printf("Cobertura impossivel. Requisitos nao cobertos:\n");
            }

            // Imprime o identificador do requisito que ficou descoberto
            printf("%s ", mat->id_req[j]);
            possivel = 0; // Muda a flag marcando que sera impossivel resolver
        }
    }

    if (possivel == 0) {
        printf("\n"); // Quebra a linha apos listar todos os requisitos falhos
        return 0;
    }

    return 1; // Retorna positivo caso todas as colunas possuam cobertura
}

int forca_bruta(const Matriz *mat, int escolhidos[]) {

    // Verifica se existe solucao
    if (verifica_possibilidade(mat) == 0) {
        return -1; // Retorna um codigo de erro para parar a execucao
    }

    int n = mat->n;
    int m = mat->m;

    // Calculo do total de combinacoes usando deslocamento de bits a esquerda
    // O operador << desloca o bit "1" n vezes para a esquerda
    // Se n=4, 1 << 4 resulta em 16 (que eh 2 elevado a 4)
    int total_combinacoes = 1 << n;

    // Inicializa a "menor_quantidade" com um valor maior que o maximo de testes
    // Garantindo que a primeira combinacao valida substitua esse valor
    int menor_quantidade = n + 1;

    // Guarda qual foi o numero binario que representou a melhor combinacao
    int melhor_combinacao = 0;

    // Teste de todas as combinacoes comecando em 1, porque 0 significa nao escolher nenhum teste
    for (int i = 1; i < total_combinacoes; i++) {
        int teste_usados = 0; // Contador de testes selecionados nesta tentativa
        int req_cobertos[MAX_REQ] = {0}; // Vetor temporario para marcar quais colunas foram cobertas

        // Le a combinacao atual como se fosse um conjunto de bits
        // Cada bit representa um teste. Se for 1, o teste foi escolhido
        for (int k = 0; k < n; k++) {

            // Verifica se o k-esimo bit do numero "i" eh 1
            // Se i = 5 (binario 0101), os bits das posicoes 0 e 2 sao 1
            if (i & (1 << k)) {
                teste_usados++; // Adiciona 1 ao custo desta combinacao

                // Como o teste "k" foi selecionado, olhamos na matriz e marcamos os requisitos resolvidos
                for (int j = 0; j < m; j++) {
                    if (mat->cobre[k][j] == 1) {
                        req_cobertos[j] = 1; // Marca a coluna "j" como resolvida
                    }
                }
            }
        }

        // Verifica se cobriu todos os requisitos, assumindo inicialmente que sim
        int todos_cobertos = 1;

        for (int j = 0; j < m; j++) {
            // Se encontrar algum requisito que continuou 0 no vetor temporario
            if (req_cobertos[j] == 0) {
                todos_cobertos = 0; // Atualiza a flag indicando que a combinacao falhou
                break; // Para de verificar o resto das colunas
            }
        }

        // Se cobriu todos os requisitos e usou uma quantidade menor de testes, atualiza o recorde
        if (todos_cobertos == 1 && teste_usados < menor_quantidade) {
            menor_quantidade = teste_usados;
            melhor_combinacao = i; // Salva o numero binario desta combinacao
        }
    }

    // Variavel para controlar a posicao de preenchimento dentro do vetor escolhidos
    int index_escolhidos = 0;

    // Faz um ultimo loop na melhor combinacao para preencher o vetor
    for (int k = 0; k < n; k++) {
        // Se o bit da posicao 'k' for 1 na melhor combinacao
        if (melhor_combinacao & (1 << k)) {
            // Salva a posicao original 'k' do teste no vetor em vez de imprimir
            escolhidos[index_escolhidos] = k;
            index_escolhidos++;
        }
    }

    // Retorna a quantidade minima para o main saber quantos itens tem no vetor validos
    return menor_quantidade;
}