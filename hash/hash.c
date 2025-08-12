#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//Tamanho da tabela hash
#define TAMANHO 1000

typedef struct tabela_hash TH;

struct tabela_hash{
    celula *Hash[TAMANHO];
};

/* Função que cria uma nova Tabela Hash e retorna um ponteiro para ela. */
TH* new_hash(){
    TH* new = malloc(sizeof(TH));

    for (int i = 0; i < TAMANHO; i++) {
        new->Hash[i] = malloc(sizeof(celula)); 
        new->Hash[i]->prox = NULL;
    }

    return new;
}

/* Função que realiza o método por Análise de Dígito.
 - Caso tiver um vetor de 10 espaços, analisará o primeiro digito (Ex: 9 é inserido na posição 9 e 38 na posição 3);
 - Caso tiver um vetor de 100 espaços, analisará os dois primeiros digitos (Ex: 9 é inserido na posição 9 e 38 na posição 38);
 - E assim por diante...
 */
int hashing(int chave, int tam){

    int valorBase = chave; // Começa com o valor inicial

    //Reduzindo o valor incial para os primeiros dígitos
    while(valorBase >= tam){
        valorBase /= 10;
    }

    //Retorna o valorBase como índice na Tabela Hash
    return valorBase;
}

/* Insere valores na Tabela Hash */
void insert_hash(int chave, TH* tabela){

    int indice = hashing(chave, TAMANHO); //Realiza o processo de análise por dígito
    insere(chave, tabela->Hash[indice]);

}

/* Função que busca na Tabela Hash um determinado valor inteiro */
celula* busca_hash(int buscando, TH* tabela){

    int indice = hashing(buscando, TAMANHO); //Analisa em qual posição do vetor o elemento que procuramos se encontra
    celula* aux = tabela->Hash[indice];

    //Percorrendo a lista até encontrar o valor (ou não, nesse casso retornando NULL)
    while(aux != NULL && aux->prox != NULL && aux->prox->conteudo != buscando){
        aux = aux->prox;
    }

    return aux;
}

/* Função para remover um valor inteiro chave da Tabela Hash */
void remove_hash(int chave, TH* tabela){

    celula* auxiliar = busca_hash(chave, tabela);
    remove_lista(auxiliar);

}

/* Função para printar na tela os valores da Tabela Hash */
void print_TH(TH* tabela){

    for(int i = 0; i < TAMANHO; i++){
        
        celula* aux = tabela->Hash[i];

        if(aux!=NULL){
            aux = aux -> prox;
        }

        printf("indice [ %d ]: ", i);

        while(aux != NULL){
            printf("%d ", aux->conteudo);
            aux = aux->prox;
        }

        printf("\n");
    }

}

int main(){

    TH* tabelaH = new_hash(); //Criando tabela

    //Inserindo valores...
    insert_hash(10, tabelaH);
    insert_hash(1, tabelaH);
    insert_hash(20, tabelaH);
    insert_hash(30, tabelaH);
    insert_hash(35, tabelaH);
    insert_hash(130, tabelaH);
    insert_hash(12, tabelaH);
    insert_hash(110, tabelaH);
    insert_hash(813459, tabelaH);
    insert_hash(279384, tabelaH);
    insert_hash(52936410, tabelaH);
    insert_hash(422, tabelaH);
    insert_hash(550, tabelaH);
    insert_hash(2, tabelaH);
    insert_hash(973, tabelaH);
    insert_hash(956, tabelaH);
    insert_hash(95212, tabelaH);
    insert_hash(95672131, tabelaH);

    //Removendo o valor 10
    remove_hash(10, tabelaH);

    //Imprimindo na tela a Tabela Hash final
    print_TH(tabelaH);

    return 0;
}