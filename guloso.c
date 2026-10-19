#include "guloso.h"

// o objetivo é encontrar a menor quantidade de testes para que todos os requisitos estejam cobertos.
int guloso(const Matriz *mat, int escolhidos[]){
    int restantes = mat->m;      // número de requisitos restantes
    int usado[MAX_TESTES] = {0}; // usado[teste] = 1 se o teste já foi usado
    int coberto[MAX_REQ] = {0};  // coberto[requisito] = 1 se o requisito já está coberto
    int qtd = 0;                 // quantidade de testes escolhidos

    while(restantes > 0){        // enquanto ainda houver requisitos restantes
        int melhor = -1;         // índice do teste que cobre mais requisitos novos
        int melhor_ganho = 0;    // maior quantidade de requisitos novos cobertos
                                 
        // calcula o ganho de cada teste e guarda o maior
        for(int i = 0; i < mat->n; i++){
            if(usado[i]) continue; // se o teste já foi usado, ignora e vai para o próximo

            int ganho = 0;         // quantidade de requisitos novos que o teste cobre

            for(int j = 0; j < mat->m; j++){
                if(mat->cobre[i][j] && !coberto[j]){
                    ganho++;       // aumenta o ganho se o teste cobre um requisito ainda não coberto
                }
            }

            if(ganho > melhor_ganho){
                melhor_ganho = ganho; // atualiza o maior ganho encontrado
                melhor = i;           // guarda o índice do teste com maior ganho
            }
        }

        if(melhor == -1) break; // se nenhum teste cobre novos requisitos, encerra o laço

        usado[melhor] = 1;       // marca o teste escolhido como já utilizado
        escolhidos[qtd++] = melhor; // adiciona o índice do teste ao vetor de escolhidos e aumenta a quantidade

        // atualiza os requisitos cobertos pelo teste escolhido
        for(int j = 0; j < mat->m; j++){
            if(mat->cobre[melhor][j] && !coberto[j]){
                coberto[j] = 1;  // define o requisito j como coberto
                restantes--;    // diminui a quantidade de requisitos restantes
            }
        }
    }

    return qtd; // retorna a quantidade de testes escolhidos
}