#ifndef TIPOS_H
#define TIPOS_H

#define MAX_TESTES 15                  // definido pelo professor
#define MAX_REQ 20                     // definido pelo professor
#define TAM_ID 32                      // definido pelo professor

typedef struct {
    int n;                             // número de requisitos
    int m;                             // número de testes
    char id_teste[MAX_TESTES][TAM_ID]; // nomes dos Testes (T1, T2, ...).
    char id_req[MAX_REQ][TAM_ID];      // nomes dos Requisitos (R1, R2, ...).
    int cobre[MAX_TESTES][MAX_REQ];    // matriz de 0's e 1's, onde: se cobre[i][j] == 1, então o teste i cobre o requisito j. se cobre[i][j] == 0, o teste i não cobre o requisito j.
} Matriz;

#endif