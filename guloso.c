#include "guloso.h"

// o objetivo é encontrar a menor quantidade de testes para que todos os requisitos estejam cobertos.
int guloso(const Matriz *mat, int escolhidos[]){
    int restantes = mat->m;      // número de requisitos restantes
    int usado[MAX_TESTES] = {0}; // usado[teste] = 1 se o teste já foi usado
    int coberto[MAX_REQ] = {0};  // coberto[requisito] = 1 se o requisito já está coberto
    int qtd = 0;                 // quantidade de testes escolhidos

    while(restantes > 0){        // enquanto ainda houverem requisitos restantes 
        int melhor = -1;         
        int melhor_ganho = 0;

                                 // calcula o ganho de cada teste e guarda o maior
        for(int i = 0; i < mat->m; i++){    
            if(usado[i]) continue;      // se o teste já foi usado, ignora e vai pro próximo

            int ganho = 0;      //
            for(int j = 0; j < mat->m; j++){
                if(mat->cobre[i][j] && !coberto[j]){
                    ganho++;
                }
            }

            if(ganho > melhor_ganho){
                melhor_ganho = ganho;
                melhor = i;
            }
        }

        if(melhor == -1) break;

        usado[melhor] = 1; 
        escolhidos[qtd++] = melhor;

        for(int j = 0; j < mat->m; j++){
            if(mat->cobre[melhor][j] && !coberto[j]){       // se o requisito j cobre 
                coberto[j] = 1;     // define o requisito j como coberto.
                restantes--;        // diminui a quantidade de requisitos, já que adicionamos o requisito j no vetor de cobertos.
            }
        }
    }
    
    return qtd;
}
