#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define VERTICES 3

//Função para encontrar o vértice com a menor distância, que ainda não foi incluído
int distanciaMinima(int distancia[], bool auxiliar[]){

    int indice_min, min = INT_MAX;

    for (int vert = 0; vert < VERTICES; vert++){
        if (auxiliar[vert] == false && distancia[vert] <= min){
            min = distancia[vert], indice_min = vert;
        }
    }

    return indice_min;
}

//Função que imprime os resultados do algoritmo Djikstra
void imprimirSolucao(int distancia[]){

    printf("~ * ~ * ~ * ~ Dijkstra: ~ * ~ * ~ * ~ \n\n");

    for (int i = 0; i < VERTICES; i++){
        printf("* Vertice: ( %d ) |-->| Distância: ( %d )\n", i, distancia[i]);
    }

    printf("\n");
}

//Função que implementa o algoritmo de Dijkstra
void dijkstra(int grafo[VERTICES][VERTICES], int origem){

    int distancia[VERTICES]; //Vetor para armazenar as distâncias mínimas da origem até cada vértice
    bool auxiliar[VERTICES]; //Vetor para controlar se o vértice foi incluído

    //Inicialização dos vetores
    for (int i = 0; i < VERTICES; i++){
        distancia[i] = INT_MAX;
        auxiliar[i] = false;
    }

    distancia[origem] = 0; //A distância do ponto de origem até ele mesma é sempre zero

    //Encontrar o caminho mínimo para todos os vértices
    for (int i = 0; i < VERTICES - 1; i++){

        int aux = distanciaMinima(distancia, auxiliar); //Encontrar o vértice com a menor distância não incluído
        auxiliar[aux] = true; //Marcar o vértice como incluído

        //Atualizar as distâncias dos vértices adjacentes ao vértice selecionado
        for (int vert = 0; vert < VERTICES; vert++){
            if (!auxiliar[vert] && grafo[aux][vert] && distancia[aux] != INT_MAX && distancia[aux] + grafo[aux][vert] < distancia[vert]){
                distancia[vert] = distancia[aux] + grafo[aux][vert];
            }
        }
    }

    imprimirSolucao(distancia);
}

int main() {

    //Teste para VERTICES = 3
    int grafo[VERTICES][VERTICES] = {{0, 1, 0},
                                     {1, 0, 2},
                                     {0, 2, 0}};
    

    //Teste para VERTICES = 5
    /*int grafo[VERTICES][VERTICES] = {{0, 1, 0, 3, 0},
                                     {1, 0, 2, 0, 0},
                                     {0, 2, 0, 1, 4},
                                     {3, 0, 1, 0, 5},
                                     {0, 0, 4, 5, 0}};
    */

    //Teste para VERTICES = 7
    /*int grafo[VERTICES][VERTICES] = {{0, 1, 0, 3, 0, 0, 0},
                                     {1, 0, 2, 0, 0, 0, 0},
                                     {0, 2, 0, 1, 4, 0, 0},
                                     {3, 0, 1, 0, 5, 6, 0},
                                     {0, 0, 4, 5, 0, 0, 7},
                                     {0, 0, 0, 6, 0, 0, 8},
                                     {0, 0, 0, 0, 7, 8, 0}};
    */

    //Teste para VERTICES = 9
    /*int grafo[VERTICES][VERTICES] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                     {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                     {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                     {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                     {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                     {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                     {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                     {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                     {0, 0, 2, 0, 0, 0, 6, 7, 0}};
    */
    
    dijkstra(grafo, 0);

    return 0;
}