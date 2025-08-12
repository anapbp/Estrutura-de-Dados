#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAX_VERTICES 6
#define MAX_ARESTAS (MAX_VERTICES * (MAX_VERTICES - 1))

//Definindo a estrutura do nó do grafo
typedef struct NO{
    char id;
    int nroVizinhos;
    struct NO* vizinhos[MAX_ARESTAS];
    bool visitado;
    int distancia;
}*Vertice;

//Função para criar um novo vértice
//Inicia sem vizinhos, tem que conectar com outros vértices depois
Vertice criaVertice(char id){
    Vertice novoVertice = (Vertice)malloc(sizeof(struct NO));
    novoVertice->id = id;
    novoVertice->nroVizinhos = 0;
    novoVertice->visitado = false;

    for (int i = 0; i < MAX_ARESTAS; i++){
        novoVertice->vizinhos[i] = NULL;
    }

    return novoVertice;
}

//Função para ligar dois vértices
//Vai procurando até achar um espaço livre e preencher com seu novo vizinho
bool ligaVertices(Vertice v1, Vertice v2){
    int aux = 0;

    while (v1->vizinhos[aux] != NULL){
        aux++;
    }

    v1->vizinhos[aux] = v2;
    aux = 0;

    while (v2->vizinhos[aux] != NULL){
        aux++;
    }

    v2->vizinhos[aux] = v1;
    v1->nroVizinhos++;
    v2->nroVizinhos++;

    return true;
}

//Função para realizar a busca em largura
//Retorna 1 caso encontre e 0 caso não encontre
int buscaEmLargura(Vertice inicio, Vertice destino){
    int iniFila = 0;
    int tamFila = 1;

    Vertice FILA[MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++){
        FILA[i] = NULL;
    }

    FILA[iniFila] = inicio;
    inicio->distancia = 0;

    while (iniFila < tamFila){
        if (FILA[iniFila] == destino){
            return 1; //Encontrou o destino
        }
		//Vai passando pelos vizinhos
        for (int i = 0; i < FILA[iniFila]->nroVizinhos; i++){
            if (FILA[iniFila]->vizinhos[i]->visitado == false){ //Entra caso ele não foi visitado ainda
                FILA[iniFila]->vizinhos[i]->visitado = true;
                FILA[iniFila]->vizinhos[i]->distancia = FILA[iniFila]->distancia + 1; //Aumenta a distância
                FILA[tamFila] = FILA[iniFila]->vizinhos[i]; //Coloca no final da fila
                tamFila++; //Aumenta o tamanho da fila
            }
        }
        iniFila++;
    }

    return 0; //Não encontrou o destino
}

int main() {
    //Criando Vértices
    Vertice A = criaVertice('A');
    Vertice B = criaVertice('B');
    Vertice C = criaVertice('C');
    Vertice D = criaVertice('D');
    Vertice E = criaVertice('E');
    Vertice F = criaVertice('F');

    //Ligando Vértices
    ligaVertices(A, B);
    ligaVertices(A, C);
    ligaVertices(B, D);
    ligaVertices(C, D);
    ligaVertices(B, E);
    ligaVertices(D, E);
    ligaVertices(E, F);
    ligaVertices(D, F);

    int aux = buscaEmLargura(A, C);

    if (aux == 1) {
        printf("Encontrou\n");
    } else {
        printf("Não encontrou\n");
    }

    return 0;
}