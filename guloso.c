#include "guloso.h"

int guloso(const Matriz *mat, int escolhidos[]){
    int restantes = mat->m;      // número de requisitos restantes
    int usado[MAX_TESTES] = {0}; // usado[teste] = 1 se o teste já foi usado
    int coberto[MAX_REQ] = {0};  // coberto[requisito] = 1 se o requisito já está coberto
    int qtd = 0;                 // quantidade de testes escolhidos

    while(restantes != 0){
        int melhor = -1;
        int melhor_ganho = 0;

        for(int i = 0; i < mat->m; i++){
            if(usado[i]) continue;

            int ganho = 0;
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
            if(mat->cobre[melhor][j] && !coberto[j]){
                coberto[j] = 1;
                restantes--;
            }
        }
    }
    
    return qtd;
}
