#include <stdio.h>
#include <stdlib.h>

#include "processos.h"

#define FATOR 2

Lista * cria_lista() {
    Lista * lista = (Lista * ) malloc(sizeof(Lista));
    if (!lista) exit(1);
    lista -> qtd = 0;
    lista -> prim = NULL;
    lista -> ult = NULL;
    return lista;
}

void inserir_processo(Lista * lista, Processo * processo) {
    Node * node = (Node * ) malloc(sizeof(Node));

    if (!node) exit(1);
    if (lista -> prim == NULL) {
        lista -> prim = node;
        lista -> ult = node;
    } else {
        lista -> ult -> prox = node;
        node -> ant = lista -> ult;
        lista -> ult = node;
    }

    node -> processo.pid = 100 + rand() % 900;
    node -> processo.temp_exec = processo -> temp_exec;
    node -> processo.temp_remain = node -> processo.temp_exec;
    node -> processo.entrada = processo -> entrada;
    node -> processo.prio_est = processo -> prio_est;
    node -> processo.prio_din = node -> processo.prio_est;
    node -> prox = NULL;
}

void ler_arquivo(Lista * lista) {
    FILE * file = NULL;
    file = fopen("arquivo.txt", "r");
    if (!file) exit(1);

    int i = 0;
    Processo processo;

    fscanf(file, "%d", & lista -> qtd);
    for (i = 0; i < lista -> qtd; i++) {
        fscanf(file, "%d", & processo.entrada);
        fscanf(file, "%d", & processo.temp_exec);
        fscanf(file, "%d", & processo.prio_est);
        inserir_processo(lista, & processo);
    }

    fclose(file);
}

void imprimir_processos(Lista * lista) {
    Node * node = lista -> prim;
    if (!lista) exit(1);

    printf("\n\n***** Processos na Lista ******\n\n");
    printf("===> Quantidade: %d\n\n", lista -> qtd);

    int i = 0;
    for (i = 0; i < lista -> qtd; i++) {
        printf("Processo 0%d - PID: %d\n", i + 1, node -> processo.pid);
        printf("temp_exec: %d - temp_remain: %d\n", node -> processo.temp_exec, node -> processo.temp_remain);
        printf("entrada: %d\n", node -> processo.entrada);
        printf("prio_est: %d - prio_din: %d\n", node -> processo.prio_est, node -> processo.prio_din);
        printf("\n");

        node = node -> prox;
    }
}

Node * varrer_processos(Lista * lista, int temp) {
    Node * node = lista -> prim;
    Node * prio = node;

    int i;
    for (i = 0; i < lista -> qtd; i++) {
        if (node -> processo.entrada <= temp) {
            if (node -> processo.prio_din > prio -> processo.prio_din)
                prio = node;
        }
        node = node -> prox;
    }

    return prio;
}

void libera_processo(Lista * lista, Node * node) {
    if (node == lista -> prim)
        lista -> prim = node -> prox;
    else node -> ant -> prox = node -> prox;

    node = NULL;
    free(node);
    lista -> qtd--;
}

void executar_processos(Lista * lista, Node * node_exec) {
    Node * node = lista -> prim;

    int i;
    for (i = 0; i < lista -> qtd; i++) {
        if (node == node_exec) {
            node -> processo.temp_remain--;
            printf("Processo EM EXEC %d - PID: %d\n", i + 1, node -> processo.pid);
            printf("temp_exec: %d - temp_remain: %d\n", node -> processo.temp_exec, node -> processo.temp_remain);
            printf("entrada: %d\n", node -> processo.entrada);
            printf("prio_est: %d - prio_din: %d\n", node -> processo.prio_est, node -> processo.prio_din);
            printf("\n");
        } else {
            node -> processo.prio_din = node -> processo.prio_din + FATOR;
        }

        node = node -> prox;
    }
    if (node_exec -> processo.temp_remain == 0) libera_processo(lista, node_exec);
}
