#include <stdio.h>
#include <string.h>
#include "tipos.h"
#include "entrada.h"

// retorna 0 quando erro, 1 quando certo
int entrada(Matriz *mat){
    int n, m;

    if(scanf("%d %d", &n, &m) != 2){    // scanf retorna n quando conseguiu armazenar n variáveis. portanto, se for diferente de 2 (que é o número de variáveis que eu quero), tá errado.
        printf("Erro: n e m ausentes ou inválidos.\n");
        return 0;
    }
    if(n < 1 || n > MAX_TESTES || m < 1 || m > MAX_REQ){    // verificação dos valores de m, n. devem estar entre 1 e MAX_TESTES ou 1 e MAX_REQ.
        printf("Erro: n deve estar entre 1 e %d e m entre 1 e %d.\n", MAX_TESTES, MAX_REQ);
        return 0;
    }
    mat->n = n;    // se não deu erro no n, atribui à matriz.
    mat->m = m;    // se não deu erro no m, atribui à matriz.

    for(int j = 0; j < m; j++){
        if(scanf("%31s", mat->id_req[j]) != 1){     // mesma coisa, se o scanf não conseguir ler, erro.
            printf("Erro: Faltam identificadores de requisitos.\n");
            return 0;
        }
        for(int k = 0; k < j; k++){
            if(strcmp(mat->id_req[j], mat->id_req[k]) == 0){    // strcmp retorna 0 quando duas strings são iguais. nesse caso, as strings são os ID's dos testes.
                printf("Erro: Requisito repetido: %s\n", mat->id_req[j]);
                return 0;
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(scanf("%31s", mat->id_teste[i]) != 1){   // se scanf leu corretamente
            printf("Erro: Faltam testes.\n");
            return 0;
        }
        for(int k = 0; k < i; k++){
            if(strcmp(mat->id_teste[k], mat->id_teste[i]) == 0){    // strcmp retorna 0 quando strings são iguais. nesse caso, as strings são os ID's dos testes.
                printf("Erro: Teste repetido: %s\n", mat->id_teste[i]);
                return 0;
            }
        }
        for(int j = 0; j < m; j++){
            int v;
            if(scanf("%d", &v) != 1 || (v != 0 && v != 1)){    // se v (que é o valor da matriz cobre) for diferente de 0 ou 1, que são os valores que estão lá: cobre ou não cobre.
                printf("Erro: valor invalido na linha de %s (esperado 0 ou 1).\n", mat->id_teste[i]);
                return 0;
            }
            mat->cobre[i][j] = v;
        }
    }
    return 1;
}