#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Função que imprime valores da lista encadeada */
void imprime(celula *lista_encadeada){

   celula *aux;

   //Printa na tela até chegar no valor nulo, ou seja, fim da lista
   for (aux = lista_encadeada; aux != NULL; aux = aux->prox){
        printf ("%d\n", aux->conteudo);
    }

}

/* Função que busca em uma lista encadeada o valor inteiro x e retorna a sua célula. 
   Retorna NULL caso não exista 
*/
celula *busca(int x, celula *lista_encadeada){

   celula *aux;
   aux = lista_encadeada;

    //Percorre a lista até encontrar o valor x, que é o valor que estamos buscando
    //Caso não encontre, teremos percorrido a lista até o final e retornaremos NULL a seguir
   while(aux != NULL && aux->conteudo != x){
      aux = aux->prox; 
   }

   return aux;
}

/* Função que insere um valor x na lista encadeada */
void insere(int x, celula *p){
   celula *nova;
   nova = malloc (sizeof (celula));
   nova->conteudo = x;
   nova->prox = p->prox;
   p->prox = nova;
}

void remove_lista(celula *p) {
    if (p == NULL) {
        // Não faz nada se o ponteiro for nulo
        return;
    }
    
    celula *removida = p->prox;
    if (removida != NULL) {
        p->prox = removida->prox;
        free(removida);
    }
}

/* Funççao que recebe como parâmetro uma lista encadeada lista_encadeada e remove 
   o primeiro valor inteiro x que encontrar 
*/
void busca_e_remove(int x, celula *lista_encadeada){

   celula *elemento_1, *elemento_2;
   elemento_1 = lista_encadeada;
   elemento_2 = lista_encadeada->prox;

    //Percorre a lista até encontrar o valor x que deseja-se remover ou até o final (NULL)
   while(elemento_2 != NULL && elemento_2->conteudo != x){
      elemento_1 = elemento_2;
      elemento_2 = elemento_2->prox;
   }

    //Caso não encontrou o valor x, o elemento_2 será NULL (fim da lista) e não entrará no if
   if(elemento_2 != NULL){
      elemento_1->prox = elemento_2->prox;
      free (elemento_2);
   }

}