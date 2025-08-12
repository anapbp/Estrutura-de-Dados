#ifndef LISTA_H
#define LISTA_H

typedef struct reg celula;  

struct reg{
    int conteudo; 
    struct reg *prox;
};

/* Função que imprime valores da lista encadeada le */
void imprime (celula *lista_encadeada);

/* Função que busca em uma lista encadeada le o valor inteiro x e retorna a sua célula. 
   Retorna NULL caso não exista 
*/
celula *busca(int x, celula *lista_encadeada);

/* Função que insere um valor x na lista encadeada le */
void insere(int x, celula *p);

/* Função que recebe o endereço de uma célula p e remove a próxima */
void remove_lista(celula *p);

/* Funççao que recebe como parâmetro uma lista encadeada le e remove 
   o primeiro valor inteiro y que encontrar 
*/
void busca_e_remove (int y, celula *lista_encadeada);

#endif