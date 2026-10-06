#include <stdio.h>
#include <string.h>
#include "tipos.h"
#include "entrada.h"

// retorna 0 quando erro, 1 quando certo
int entrada(Matriz *mat){
    int n, m;

    if(scanf("%d %d", &n, &m) != 2){
        printf("Erro: n e m ausentes ou inválidos.\n");
        return 0;
    }
    if(n < 1 || n > MAX_TESTES || m > MAX_REQ){
        printf("Erro: n deve estar entre 1 e %d e m entre 1 e %d.\n", MAX_TESTES, MAX_REQ);
        return 0;
    }
    mat->n = n;
    mat->m = m;

    for(int j = 0; j < m; j++){
        if(scanf("%31s", mat->id_req[j]) != 1){
            printf("Erro: Faltam identificadores de requisitos.\n");
            return 0;
        }
        for(int k = 0; k < j; k++){
            if(strcmp(mat->id_req[j], mat->id_req[k]) == 0){
                printf("Erro: Requisito repetido: %s\n", mat->id_req[j]);
                return 0;
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(scanf("%31s", mat->id_teste[i]) != 1){
            printf("Erro: Faltam testes.\n");
            return 0;
        }
        for(int k = 0; k < i; k++){
            if(strcmp(mat->id_teste[k], mat->id_teste[i]) == 0){
                printf("Erro: Teste repetido: %s\n", mat->id_teste[i]);
                return 0;
            }
        }
        for(int j = 0; j < m; j++){
            int v;
            if(scanf("%d", &v) != 1 || (v != 0 && v != 1)){
                printf("Erro: valor invalido na linha de %s (esperado 0 ou 1).\n", mat->id_teste[i]);
                return 0;
            }
            mat->cobre[i][j] = v;
        }
    }
    return 1;
}