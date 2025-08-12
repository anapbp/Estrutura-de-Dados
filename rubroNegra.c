#include <stdio.h>
#include <stdlib.h>

//Nós Vermelhos serão representados com o valor inteiro 0 e os nós Pretos com o valor inteiro 1
#define VERMELHO 0
#define PRETO 1

typedef int TIPOCHAVE;

//Cada um dos nós da Árvore:
struct Node{
    int cor; //A cor do nó (Preto ou Vermelho)
    TIPOCHAVE chave; //Valor que será atribuído ao nó
    struct Node *pai; //Ponteiro para o pai
    struct Node *esq; //Ponteiro para o filho da esq
    struct Node *dir; //Ponteiro para o filho da dir
};

typedef struct Node Node;

//Função que cria um novo nó
Node *criarNo(int valor){

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->chave = valor; //Adicionando o valor que será atribuído ao novo nó
    newNode->cor = VERMELHO; //Novos nós são sempre vermelhos
    newNode->pai = NULL;
    newNode->esq = NULL;
    newNode->dir = NULL;

    return newNode;
}

/*      Esquema para função abaixo:

        (X)                      (Y)
        / \                      / \
      (a) (Y)       ---->      (X) (c)
          / \                  / \     
        (b)  (c)             (a)  (b)      

*/
//Função auxiliar para fazer a rotação à esq
void rotacaoesq(Node **tree, Node *x){

    Node *y = x->dir;

    x->dir = y->esq; //(X) terá como filho da esq (b)

    if(y->esq != NULL){
        y->esq->pai = x; //O filho a esq de (Y) era (b), mas agora (b) será filho de (X)
    }

    y->pai = x->pai; //O pai de (Y) será o pai de (X)

    if(x->pai == NULL){ //Caso o pai de (X) for nulo, então (X) era a raíz

        *tree = y; //Agora, (Y) será a raíz

    } else if(x == x->pai->esq){ //Analisando se (X) era filho da esq

        x->pai->esq = y; //Se for, agora o filho da esq será (Y)

    } else { //Analisando se (X) era filho da dir

        x->pai->dir = y; //Se for, agora o filho da dir será (Y)
    }

    y->esq = x; //(X) será filho de (Y)...
    x->pai = y; // ... ou seja, (Y) será pai de (X)
}

/*      Esquema para função abaixo:

            (Y)                (X)   
            / \                / \   
          (X) (c)   ---->    (a) (Y)   
          / \                    / \   
        (a)  (b)               (b)  (c)         

*/
//Função auxiliar para fazer a rotação à dir
void rotacaodir(Node **tree, Node *y){

    Node *x = y->esq; //(X) é o filho da esq de Y antes

    y->esq = x->dir; //O filho da esq de (Y) será (b), o antigo filho da dir de (b)

    if(x->dir != NULL){
        x->dir->pai = y; //O filho a dir de (X) era (b), mas agora (b) será filho de (Y)
    }

    x->pai = y->pai; //O pai de (X) será o pai de (Y)

    if(y->pai == NULL){ //Caso o pai de (Y) for nulo, então (Y) era a raíz

        *tree = x; //Agora, (X) será a raíz

    } else if(y == y->pai->esq){ //Analisando se (Y) era filho da esq

        y->pai->esq = x; //Se for, agora o filho da esq será (X)

    } else { //Analisando se (Y) era filho da dir

        y->pai->dir = x; //Se for, agora o filho da dir será (X)
    }

    x->dir = y; //(Y) será filho de (X)
    y->pai = x; // ... ou seja, (X) será pai de (Y)
}

//Função auxiliar para inserção
void inserirAuxiliar(Node **tree, Node *new) {

    /* O pai do nosso novo nó não pode ser Vermelho, pois, se for, o nosso novo nó também será e isso
    fere uma das regras, sendo assim, irá ficar no while enquanto esse erro não for consertado. */
    while(new != *tree && new->pai->cor == VERMELHO){

        if(new->pai == new->pai->pai->esq){

            Node *y = new->pai->pai->dir;

            if(y != NULL && y->cor == VERMELHO){
                //Recolorindo...
                new->pai->cor = PRETO;
                y->cor = PRETO;
                new->pai->pai->cor = VERMELHO;
                new = new->pai->pai;

            } else {

                if(new == new->pai->dir){
                    //Rotacionando para a esq
                    new = new->pai;
                    rotacaoesq(tree, new);
                }

                new->pai->cor = PRETO;
                new->pai->pai->cor = VERMELHO;
                //Rotacionando para a dir
                rotacaodir(tree, new->pai->pai);

            }

        } else { //Caso simétrico

            Node *y = new->pai->pai->esq; 

            if(y != NULL && y->cor == VERMELHO){
                //Recolorindo...
                new->pai->cor = PRETO;
                y->cor = PRETO;
                new->pai->pai->cor = VERMELHO;
                new = new->pai->pai;

            } else {

                if (new == new->pai->esq) {
                    //Rotacionando para a dir
                    new = new->pai;
                    rotacaodir(tree, new);
                }

                new->pai->cor = PRETO;
                new->pai->pai->cor = VERMELHO;
                //Rotacionando para a esq
                rotacaoesq(tree, new->pai->pai);
            }

        }

    }

    (*tree)->cor = PRETO;
}

//Função para inserir elementos na árvore
void inserir(Node **tree, int valor){

    Node *novo = criarNo(valor);
    Node *aux = NULL;
    Node *x = *tree;

    while(x != NULL){

        aux = x;

        //Caso o valor que será inserido for menor que o valor de X, entrar no caminho da esq
        if(novo->chave < x->chave){ 

            x = x->esq;

        } else { //Caso o valor que será inserido for maior que o valor de X, entrar no caminho da dir

            x = x->dir;
        }
    }
    //Quando sair do while, então X == NULL, ou seja, achou onde inserir o novo nó

    novo->pai = aux;

    if(aux == NULL){ //Caso for nulo, então era a raíz nula

        *tree = novo;

    } else if(novo->chave < aux->chave){ //Se for menor, adiciona no filho da esq

        aux->esq = novo;

    } else { //Se for maior, adiciona no filho da dir

        aux->dir = novo;
    }

    //Realizar análises para saber se as regras estão sendo obedecidas
    inserirAuxiliar(tree, novo);
}

//Função para buscar um elemento na árvore.
Node *busca(Node *tree, int valor){

    while(tree != NULL){

        if (valor == tree->chave){ //Caso o valor for o mesmo, encontrou

            return tree;

        } else if (valor < tree->chave){ //Caso o valor for menor, percorrer o caminho da esq em busca

            tree = tree->esq;

        } else { //Caso o valor for maior, percorrer o caminho da dir em busca

            tree = tree->dir;
        }

    }

    return NULL;
}

//Função que encontra o menor valor da sub-árvore
Node *menorValor(Node *node){

    //O menor valor é o que estará mais a esq
    while (node != NULL && node->esq != NULL){ 
        node = node->esq;
    }

    return node;
}

//Função auxiliar para a função de remoção
void deletarAuxiliar(Node **tree, Node *x){

    while(x != *tree && (x == NULL || x->cor == PRETO)){

        if (x == NULL) {
            break; 
        }

        if(x == x->pai->esq){

            Node *w = x->pai->dir;

            if(w != NULL && w->cor == VERMELHO){

                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoesq(tree, x->pai);
                w = x->pai->dir;

            }

            if(w == NULL){
                x = x->pai;
                continue;   // Continua para o próximo loop
            }

            if((w->esq == NULL || w->esq->cor == PRETO) &&
                (w->dir == NULL || w->dir->cor == PRETO)){
                w->cor = VERMELHO;
                x = x->pai;

            } else {

                if(w->dir == NULL || w->dir->cor == PRETO){

                    if(w->esq != NULL){
                        w->esq->cor = PRETO;
                    }

                    w->cor = VERMELHO;
                    rotacaodir(tree, w);
                    w = x->pai->dir;

                }

                w->cor = x->pai->cor;
                x->pai->cor = PRETO;

                if(w->dir != NULL){
                    w->dir->cor = PRETO;
                }

                rotacaoesq(tree, x->pai);
                x = *tree;
            }

        } else { //Simétrico

            Node *w = x->pai->esq; 

            if(w != NULL && w->cor == VERMELHO){

                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaodir(tree, x->pai);
                w = x->pai->esq;

            }

            if(w == NULL){
                x = x->pai; 
                continue;   // Continue para o próximo loop
            }

            if((w->dir == NULL || w->dir->cor == PRETO) &&
                (w->esq == NULL || w->esq->cor == PRETO)){
                w->cor = VERMELHO;
                x = x->pai;

            } else {

                if(w->esq == NULL || w->esq->cor == PRETO){

                    if (w->dir != NULL){
                        w->dir->cor = PRETO;
                    }

                    w->cor = VERMELHO;
                    rotacaoesq(tree, w);
                    w = x->pai->esq;
                }

                w->cor = x->pai->cor;
                x->pai->cor = PRETO;

                if (w->esq != NULL){
                    w->esq->cor = PRETO;
                }

                rotacaodir(tree, x->pai);
                x = *tree;
            }

        }
    }

    if (x != NULL){
        x->cor = PRETO;
    }
}

//Função auxiliar para substituir um nó por outro na árvore
void substituicao(Node **tree, Node *A, Node *B){

    if(A->pai == NULL){

        *tree = B;

    } else if(A == A->pai->esq){

        A->pai->esq = B; //O pai de A agora será o pai de B (com B sendo o filho da esq)

    } else {

        A->pai->dir = B; //O pai de A agora será o pai de B (com B sendo o filho da dir)
    }
    
    if(B != NULL){
        B->pai = A->pai; //O pai de B agora será o pai de A
    }

}

//Função para remoção de elementos da árvore
void deletar(Node **tree, int chave){

    Node *noAux = busca(*tree, chave);

    if(noAux == NULL){
        return; //Caso for nulo, então não foi posssível encontrar na árvore
    }

    //Caso encontrou o nó...

    Node *y = noAux;
    int corY = y->cor;
    Node *x;

    if(noAux->esq == NULL){ //Caso simples em que só substitui

        x = noAux->dir;
        substituicao(tree, noAux, noAux->dir);

    } else if(noAux->dir == NULL){ //Caso simples em que só substitui

        x = noAux->esq;
        substituicao(tree, noAux, noAux->esq);

    } else {

        //Obtém o menor valor da sub-árvore de noAux (o nó que contém o elemento q queremos remover)
        y = menorValor(noAux->dir); 
        corY = y->cor;
        x = y->dir;

        if(y->pai == noAux){
            if (x != NULL) { //Condição para não dar Segmentation Fault
                   x->pai = y;
            }
            
        } else {

            substituicao(tree, y, y->dir);
            y->dir = noAux->dir;

            if (y->dir != NULL) { //Condição para não dar Segmentation Fault
                    y->dir->pai = y;
            }

        }

        substituicao(tree, noAux, y);
        y->esq = noAux->esq;
        y->esq->pai = y;
        y->cor = noAux->cor;

    }

    if(corY == PRETO){
        deletarAuxiliar(tree, x);
    }

    free(noAux);
}

//Função auxiliar para printar os valores da árvore junto com a sua cor
void printarAuxiliar(Node *node, int espacamento){

    if(!node){ //Caso o nó esteja vazio

        for(int i = 0; i < espacamento; i++){
            printf(" ");
        }

        printf(" - No vazio\n");

    } else { //Caso o no possua elemento(s)

        for(int i = 0; i < espacamento; i++){
            printf(" ");
        }

        printf("(*) no: %d (", node->chave);

        if(node->cor == VERMELHO){
            printf("VERMELHO)\n");
        } else {
            printf("PRETO)\n");
        }

        printarAuxiliar(node->esq, espacamento + 4); //Printando filho da esq do no atual
        printarAuxiliar(node->dir, espacamento + 4); //Printando filho da esq do no atual
    }
}

//Função para printar os valores da arvore
void printar(Node *tree){
    printf("Resultado da Arvore Rubro-Negra:\n");
    printarAuxiliar(tree, 0);
}

int main(){

    Node *tree = NULL;
    int valor;
    int auxiliar = 0;

        printf("~ * ~ * ~ * ~ * ~ * ~ * ~  Arvore Rubro-Negra: ~ * ~ * ~ * ~ * ~ * ~ * ~\n");

        while(auxiliar != 5){

            printf("O que  deseja fazer?\n");
            printf("(1) Inserir elemento\n");
            printf("(2) Remover elemento\n");
            printf("(3) Buscar elemento\n");
            printf("(4) Imprimir arvore em ordem\n");
            printf("(5) Finalizar\n");
            printf("Escolha: ");
            scanf("%d", &auxiliar);

            if(auxiliar == 1){

                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &valor);
                inserir(&tree, valor);
                printf("Elemento %d inserido na arvore.\n", valor);

            } else if (auxiliar == 2) {
                printf("Digite o elemento a ser removido: ");
                scanf("%d", &valor);
                
                Node *encontrou = busca(tree, valor);

                if (encontrou != NULL) {
                    deletar(&tree, valor);
                    printf("Elemento %d removido da arvore.\n", valor);
                } else {
                    printf("Elemento %d não encontrado na arvore.\n", valor);
                }

            } else if(auxiliar == 3){

                printf("Digite o elemento a ser buscado: ");
                scanf("%d", &valor);
                Node *encontrou = busca(tree, valor);

                if (encontrou != NULL){
                    printf("Elemento %d encontrado na arvore.\n", valor);
                } else {
                    printf("Elemento %d não encontrado na arvore.\n", valor);
                }

            } else if(auxiliar == 4){

                printf("Arvore atual: ");
                printar(tree);
                printf("\n");

            } else if(auxiliar != 5){
                printf("Valor invalido, tente novamente.\n");
            }

            printf("\n");

        }

        printf("Programa finalizado :)\n");

    return 0;
}