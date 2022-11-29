#include <stdbool.h>

typedef struct processo {
    int pid;
    int temp_exec;
    int temp_remain;
    int entrada;
    int prio_est;
    int prio_din;
}
Processo;

typedef struct node {
    Processo processo;
    struct node * prox;
    struct node * ant;
}
Node;

typedef struct lista {
    int qtd;
    Node * prim;
    Node * ult;
}
Lista;

Lista * cria_lista(void);

void inserir_processo(Lista * lista, Processo * processo);

void ler_arquivo(Lista * lista);

void imprimir_processos(Lista * lista);

Node * varrer_processos(Lista * lista, int temp);

void executar_processos(Lista * lista, Node * node_exec);
