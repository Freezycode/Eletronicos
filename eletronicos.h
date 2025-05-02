#ifndef ELETRONICOS_H
#define ELETRONICOS_H

typedef struct {
    char nome[100];
    char categoria[300];
    float preco;
} Produto;

void ordenar_por_nome(Produto *produtos, int n);
void ordenar_por_categoria(Produto *produtos, int n);
void ordenar_por_preco(Produto *produtos, int n);

#endif
