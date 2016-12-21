#include "grafo.h"
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int resultado = INF;
list<int> caminho;

/*
@input:
    lista de adjacencia do grafo
*/
void imprimeCaminho(vertice *vertices){

    list<int>::iterator it;

    for (it=caminho.begin(); it!=caminho.end(); ++it)
        cout << *it << ' ';
    cout << '0' << endl;
}

/*
adiciona na lista 'caminho' os vertices que compoe o menor caminho
a insercao é feita do ultimo vertice do caminho(ignorando a volta para a origem)
para o começo. O lista porem fica organizada da forma correta.

@input:
    lista de adjacencia do grafo;
    ultimo vertice adicionado ao caminho
*/
void salvaCaminho(vertice *vertices, int v_atual){

    caminho.clear();//exclui caminho anterior
    while(v_atual){ //vertice nao é a origem
        caminho.push_front(v_atual);//adiciona no comeco da lista
        v_atual = vertices[v_atual].pai;//atualiza o vertice
    }
    caminho.push_front(0);//adiciona o vertice inicial
}

/*
@input:
    lista de adjacencia do grafo;
    lista de vertices nao adicionados ao caminho;
    cpc = custo parcial do caminho;
    ultimo vertice adicionado ao caminho
*/
void backtrack(vertice *vertices, list<int> l, int cpc, int v_atual){

    //lista vazia == nenhum vertice para se adicionar ao caminho
    if(l.empty()){

        //exite a aresta para a origem?
        //custo 0 == aresta nao existe
        int custo_aresta = verificaAresta(vertices, v_atual, 0);
        if(custo_aresta){           //se existe

            //novo caminho possui um custo melhor que o atual?
            if((cpc + custo_aresta) < resultado){
                //atualiza o custo final
                resultado = cpc + custo_aresta;
                //atualiza o caminho
                vertices[0].pai = v_atual;
                salvaCaminho(vertices, v_atual);
            }
        }
    }
    else{//ha vertices para se adicionar ao caminho
        aresta *a = vertices[v_atual].adjacente;//lista de arestas
        while(a){//verifica todas as arestas

            /*verifica se a aresta nao aponta para um
            vertice ja adicionado no caminho*/
            if(vertices[a->dest].pai == -1){
                if(a->dest){//aresta ainda nao pode apontar para a origem
                    /*branch and bound
                    ainda é viavel proceguir no caminho?*/
                    if((cpc + a->custo) < resultado){//se sim
                        //remove o vertice da lista de vertices nao adicionados
                        l.remove(a->dest);
                        vertices[a->dest].pai = v_atual;//atualiza referencias
                        //explora caminho a partir de a->dest
                        backtrack(vertices, l, cpc+a->custo, a->dest);
                        /* caminho por a->dest ja foi explorado
                        reinserir o vertice na lista*/
                        vertices[a->dest].pai = -1;
                        l.push_back(a->dest);
                    }
                }
            }
            a = a->prox;//proxima resta
        }
    }
}

int **Alocar_matriz (int m, int n)
{
  int **v;  /* ponteiro para a matriz */
  int   i;    /* variavel auxiliar      */
  if (m < 1 || n < 1) { /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (NULL);
     }
  /* aloca as linhas da matriz */
  v =  (int**) calloc (m, sizeof(int *));	/* Um vetor de m ponteiros para int */
  if (v == NULL) {
     printf ("** Erro: Memoria Insuficiente **");
     return (NULL);
     }
  /* aloca as colunas da matriz */
  for ( i = 0; i < m; i++ ) {
      v[i] = (int*) calloc (n, sizeof(int));	/* m vetores de n int */
      if (v[i] == NULL) {
         printf ("** Erro: Memoria Insuficiente **");
         return (NULL);
         }
      }
  return (v); /* retorna o ponteiro para a matriz */
}

int **Liberar_matriz (int m, int n, int **v)
{
  int  i;  /* variavel auxiliar */
  if (v == NULL) return (NULL);
  if (m < 1 || n < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (v);
     }
  for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz (vetor de ponteiros) */
  return (NULL); /* retorna um ponteiro nulo */
}

int main ()
{
	vertice *vertices;
	char  test[10000];
	int n_ver, n_are, ori, dest, custo, contador, x, i, j;
	int **lidaTxt;
	list <int> l;
	list <int>::iterator k;
    char url[]="matriz.txt", ch1, ch2, ch3;
	FILE *arq;

	arq = fopen(url, "r");
	
	if(arq == NULL)
	{
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}
	else
	{
		fscanf(arq,"%d\n", &n_ver);
		printf("%d\n", n_ver);
	}
	
	lidaTxt = Alocar_matriz (n_ver, n_ver);
	
	printf("Numero de vertices: %d\n", n_ver);
	n_are = (n_ver*(n_ver-1))/2;
	vertices = (vertice*)malloc(n_ver * sizeof(vertice));
	
	lidaTxt = (int **)malloc(n_ver * n_ver * sizeof(int));

	printf("Malloc feito!!!\n");

	inicializaGrafo(vertices, n_ver);
	
	printf("Grafo inicializado!!!\n");

	for (i=0; i<n_ver; i++)
	{
		//fscanf(arq, "%d", &contador);
		printf("i: %d ", i);

		for (j=0; j<n_ver; j++)
		{
			fscanf(arq, "%d" , &lidaTxt[i][j]);
			printf("j: %d ",  j);
			
			//insereAresta(vertices, i, j, lidaTxt[i][j]);
		}
		//fscanf(arq, "\n");
		printf("\n");
    }


	//adiciona todos os vertices à lista, exceto a origem
	//for(int i = 1; i < n_ver+1; i++)
	//{
 //       l.push_back(i);
 //   }
	//
	//for ( k = l.begin(); k != l.end(); k++ )
	//	cout << "Imprimindo a lista...: " << *k << endl;

	//printf("Inseriu elementos na lista\n");

	//imprimeCaminho(vertices);

 //   //o caminho inicializa-se com custo 0, no vertice 0
 //   backtrack(vertices, l, 0, 0);

	//printf("Saiu do backtrack\n");
	//
	//imprimeCaminho(vertices);

	//free(vertices);
	//fclose(arq);
 //   liberaGrafo(vertices, n_ver);

return 0;
}
