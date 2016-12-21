#include <stdlib.h>
#include <iostream>
#include "grafo.h"

using namespace std;
/*
 * seta os vertices e o heap com as configuracoes nescessarias para iniciar o calculo das rotas
 */
void inicializaGrafo(vertice *vertices, int n_ver){

    //vertices[0].pai = 0;
    //vertices[0].adjacente = NULL;
    for(int i=0; i<n_ver; i++) {
        vertices[i].pai = -1;
        vertices[i].adjacente = NULL;
    }
}

/*
 * informa via saida padrao ou arquivo de saida os valores calculados
 */
void listaVertices(vertice *vertices, int n_ver){

    for(int i = 0; i < n_ver; i++){
        cout << "vertice: " << i << "\tpai: " << vertices[i].pai << endl;
    }
}

/*
 * informa as arestas existentes no grafo
 */
void listaArestas(vertice *vertices, int n_ver){

    aresta *aux;
    for(int i=0; i<n_ver; i++){
        aux = vertices[i].adjacente;
        while(aux){
            cout << "Aresta de " << i << " a " << aux->dest << "\tcusto: " << aux->custo << endl;
            aux = aux->prox;
        }
    }
}

/*
 * remove unidirecionalmente a aresta dos vertices envolvidos
 */
void removeAresta(vertice *vertices, int ori, int dest){

    aresta *are = vertices[ori].adjacente;
    if(are->dest == dest){
        vertices[ori].adjacente = vertices[ori].adjacente->prox;
        free(are);
    }
    else{
        aresta *are2 = are->prox;
        while(are2){
            if(are2->dest == dest){
                are->prox = are2->prox;
                free(are2);
                break;
            }
            are = are2;
            are2 = are2->prox;
        }
    }
}

int verificaAresta(vertice *vertices, int ori, int dest){

    aresta *are = vertices[ori].adjacente;
    while(are){
        if(are->dest == dest){
            return are->custo;
        }
        are = are->prox;
    }
    return 0;
}

/*
 * insere uma aresta unidirecionalmente no grafo
 */
void insereAresta(vertice *vertices, int ori, int dest, int custo){

    aresta *novaAresta = (aresta*)malloc(sizeof(aresta));
    novaAresta->prox = vertices[ori].adjacente;
    novaAresta->dest = dest;
    novaAresta->custo = custo;
    vertices[ori].adjacente = novaAresta;
}

void liberaGrafo(vertice *vertices, int n_ver){

    int i;
    aresta *aux, *aux2;
    for(i=0; i<n_ver; i++){
        aux = vertices[i].adjacente;
        while(aux){
            aux2 = aux->prox;
            free(aux);
            aux = aux2;
        }
    }
    free(vertices);
}
