#ifndef TIPOS_H
#define TIPOS_H

#define MAX_TESTES 15
#define MAX_REQ 20
#define TAM_ID 32

typedef struct {
    int n;
    int m;
    char id_teste[MAX_TESTES][TAM_ID];
    char id_req[MAX_REQ][TAM_ID];
    int cobre[MAX_TESTES][MAX_REQ];
} Matriz;

#endif