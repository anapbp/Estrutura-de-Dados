#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


typedef int bool;
typedef int TIPOCHAVE;


typedef struct aux{
    TIPOCHAVE chave;
    /* Dados armazenados */
    struct aux *esq; //Filho da esquerda
    struct aux *dir; //Filho da direita
    int fb; //Fator de balanceamento (fb = altura_da_direita - altura_da_esquerda)

}NO, *PONT;


/* Função que recebe dois parâmetros inteiros (valor1 e valor2) e retorna o maior valor. */
int qualOMaximo(int valor1, int valor2){

    if(valor1 > valor2){
        return valor1;
    } else {
        return valor2;  
    }
}

/* Função recursiva que recebe um ponteiro para uma árvore e retorna a sua altura. */
int altura(NO* tree){

    if (tree == NULL){
        return 0;
    }

    int altura_da_esquerda = altura(tree->esq);
    int altura_da_direita = altura(tree->dir);

    /* Obtém a altura máxima da árvore, que pode estar localizada na direita
     ou na esquerda do nosso ponteiro incial. */
    int altura_maxima = qualOMaximo(altura_da_esquerda, altura_da_direita); 

    return altura_maxima + 1; //Adiciona + 1, pois também conta com a localização atual do nosso ponteiro inicial.
}

/* Função que recebe como parâmetro um valor inteiro que será adicionado na árvore 
 e retorna um nó correspondente a esse valor. */
NO* criandoNovoNo(int chave){

    NO* no_auxiliar = malloc(sizeof(NO));

    no_auxiliar->chave = chave;
    no_auxiliar->fb = 0; // Inicializando o fator de balanceamento
    no_auxiliar->esq = NULL; //Atualmente não possui filho da esquerda
    no_auxiliar->dir = NULL; //Atualmente não possui filho da direita

    return no_auxiliar;
}

/*Função que atualiza o Fator de Balanceamento (fb) de um determinado ponto da árvore. */
void atualizacaoDoFatorDeBalanceamento(NO* tree){

    if (tree == NULL){
        return;
    }

    //Fb = altura_da_direita - altura_da_esquerda.
    tree->fb = altura(tree->dir) - altura(tree->esq);
}

/* Rotaciona árvore que está desbalanceada na direita. */
NO* rotacaoDireita(NO* tree){

    NO* new_tree = tree->esq;

    tree->esq = new_tree->dir;
    new_tree->dir = tree;

    return new_tree;
}

/* Rotaciona árvore que está desbalanceada na esquerda. */
NO* rotacaoEsquerda(NO* tree){

    NO* new_tree = tree->dir;

    tree->dir = new_tree->esq;
    new_tree->esq = tree;

    return new_tree;
}

/* Função que recebe como parâmetro um ponteiro para uma árvore e realiza uma análise 
do fator de balanceamento e, caso estiver desbalanceada, realiza os ajustes necessários. 
Retorna o ponteiro para a árvore. */
NO* AnaliseDoFatorDeBalanceamento(NO* tree){

    if (tree == NULL){
        return tree;
    }

    atualizacaoDoFatorDeBalanceamento(tree);

    // fb_aux recebe o fator de balanceamento (fb) da árvore para analisar.
    int fb_aux = tree->fb;

    //Caso for para realizar uma rotação do tipo LL ou LR
    if (fb_aux < -1){ //Caso o fator de balanceamento for < -1, a árvore está desbalanceada na esquerda

        if (tree->esq->fb > 0){
            tree->esq = rotacaoEsquerda(tree->esq); //Para o tipo LR
        }

        return rotacaoDireita(tree); //Se não entrar no if acima, tipo LL

    //Caso for para realizar uma rotação do tipo RR ou RL
    } else if (fb_aux > 1){ //Caso o fator de balanceamento for > 1, a árvore está desbalanceada na direita

        if (tree->dir->fb < 0){
            tree->dir = rotacaoDireita(tree->dir); //Para o tipo RL
        }

        return rotacaoEsquerda(tree); //Se não entrar no if acima, tipo RR
    }

    return tree;
}

/* Função que recebe como parâmetros um ponteiro para uma árvore e um valor inteiro que queira adicionar na mesma. */
NO* inserir(NO* tree, int chave){

    if (tree == NULL){
        return criandoNovoNo(chave);
    }

    /* Caso o valor a ser adicionado na árvore for maior do que o valor atual, inserir no filho da direita,
    caso contrário, inserir no filho da esquerda. */
    if (chave < tree->chave){

        tree->esq = inserir(tree->esq, chave); 

    } else if (chave > tree->chave){

        tree->dir = inserir(tree->dir, chave);

    }

    return AnaliseDoFatorDeBalanceamento(tree);
}

NO* buscarMinimo(NO* tree){

    while (tree->esq != NULL){

        tree = tree->esq;

    }

    return tree;
}

/* Função que recebe como parâmetros um ponteiro para uma árvore e um valor inteiro que deseja excluir.
Retorna um ponteiro para a árvore. */
NO* excluir(NO* tree, int chave){

    if (tree == NULL){
        return tree;
    }

    //Procura o nó a ser excluído na árvore
    if (chave < tree->chave){

        tree->esq = excluir(tree->esq, chave);

    } else if (chave > tree->chave){

        tree->dir = excluir(tree->dir, chave);

    //Encontrou o nó a ser excluído
    } else {

        if (tree->esq == NULL || tree->dir == NULL) {

            NO* temp = tree->esq ? tree->esq : tree->dir;

            // Caso de um ou nenhum filho
            if (temp == NULL){

                temp = tree;
                tree = NULL;

            //Copia o conteúdo do nó filho não vazio
            } else{

                *tree = *temp; // Copia o conteúdo do nó filho não vazio
            }

            free(temp);

        } else{

            NO* temp = buscarMinimo(tree->dir);

            //Copia o valor do sucessor para este nó
            tree->chave = temp->chave;

            //Exclui o sucessor
            tree->dir = excluir(tree->dir, temp->chave);
        }
    }

    //Retorna a árvore se tinha apenas um nó
    if (tree == NULL){
        return tree;
    }

    //Atualiza o fator de balanceamento (fb)
    atualizacaoDoFatorDeBalanceamento(tree);

    //Analisa se a árvore está balanceada ou não
    return AnaliseDoFatorDeBalanceamento(tree);
}

/*Função auxiliar para imprimir valores da árvore */
void printarAuxiliar(NO* aux, int indent){

    for (int i = 0; i < indent; i++){
        printf(" ");
    }

    if (!aux){

        printf("Nó vazio\n");

    } else {

        printf("nó: %d\n", aux->chave);
        printarAuxiliar(aux->esq, indent + 4);
        printarAuxiliar(aux->dir, indent + 4);

    }
}

/* Função para imprimir valores da árvore. */
void printar(NO* aux) {
    printarAuxiliar(aux, 0);
}

int main(int argc, char* argv[]) {

    NO* tree = NULL;

    int indice = 4;
    int valor;

    printf("\n============================== Arvore AVL ==============================\n");

    while(indice != 0){

    printf("\nDigite 1 para inserir elementos na árvore AVL ou 2 para excluir:\n(Quando quiser finalizar, digite 0)\n");
    scanf("%d", &indice);

        if(indice == 1){

            printf("Elemento a ser inserido: ");
            scanf("%d", &valor);
            printf("\n\n");

            tree = inserir(tree, valor);

        } else if(indice == 2){

            printf("Elemento a ser deletado: ");
            scanf("%d", &valor);
            printf("\n\n");

            excluir(tree, valor);

        } else if(indice != 0){

            printf("Valor inválido, tente novamente\n\n");

        }
    }

    printf("Programa finalizado :)\n\nSegue abaixo a sua árvore final:\n\n");

    printar(tree);

    return 0;
}