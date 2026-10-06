#include <stdio.h>
#include "tipos.h"
#include "entrada.h"
#include "guloso.h"
#include "forca_bruta.h"

int main(){
    Matriz m = {0};

    if(!entrada(&m)){
        return 1;
    }
    
    printf("Entrada validada: %d testes, %d requisitos.\n", m.n, m.m);

    return 0;
}

