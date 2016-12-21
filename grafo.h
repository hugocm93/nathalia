typedef struct aresta{
    int dest, custo;
    struct aresta *prox;
} aresta;

typedef struct vertice{
    int pai;
    aresta *adjacente;
} vertice;

const int INF = 20000;

void liberaGrafo(vertice *vertices, int n_ver);
void inicializaGrafo(vertice *vertices, int n_ver);
void listaVertices(vertice *vertices, int n_ver);
void listaArestas(vertice *vertices, int n_ver);
void removeAresta(vertice *vertices, int ori, int dest);
void insereAresta(vertice *vertices, int ori, int dest, int custo);
int verificaAresta(vertice *vertices, int ori, int dest);
