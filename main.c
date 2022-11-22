#include <stdlib.h>

#include "processos.h"

int main(int argc, char * argv[]) {
    Lista * lista = NULL;

    lista = cria_lista();
    ler_arquivo(lista);
    imprimir_processos(lista);

    return 0;
}
