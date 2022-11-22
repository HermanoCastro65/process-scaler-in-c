typedef struct processo {
    int pid;
    int temp_exec;
    int temp_remain;
    int entrada;
    int prio_est;
    int prio_din;
} Processo;

typedef struct node {
    Processo processo;
    struct node * prox;
} Node;

typedef struct lista {
    int qtd;
    Node * prim;
    Node * ult;
} Lista;

Lista * cria_lista(void);

void inserir_processo(Lista * lista, Processo * processo);

void ler_arquivo(Lista * lista);

void imprimir_processos(Lista * lista);
