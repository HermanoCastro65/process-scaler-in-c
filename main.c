#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#include "processos.h"

int temp = 0;

int main(int argc, char * argv[]) {
    Lista * lista = NULL;

    lista = cria_lista();
    ler_arquivo(lista);
    imprimir_processos(lista);
    printf("\nAperte ENTER para iniciar a execucao dos procesos na lista.");
    getchar();

    while (lista -> prim) {
        printf("\nTEMPO DE EXEC TOTAL: %d\n", temp);
        printf("\nPROCESSOS NA LISTA : %d\n", lista -> qtd);
        executar_processos(lista, varrer_processos(lista, temp));
        Sleep(1000);
        temp++;
    }

    printf("\nProcessos executados com SUCESSO.");
    getchar();
    return 0;
}
