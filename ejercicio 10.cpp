#include <iostream>
#include <cstdlib>
#include <algorithm> // Para std::max

struct node {
    int vertex;
    struct node *link;
};

typedef struct node *link;

struct graph {
    int V;
    int A;
    link *adj;
};

typedef struct graph *Graph;

static link NEWnode(int w, link next) {
    link a = (link)malloc(sizeof(struct node));
    a->vertex = w;
    a->link = next;
    return a;
}

Graph GRAPHinit(int V) {
    Graph G = (Graph)malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = (link*)malloc(V * sizeof(link));
    for (int v = 0; v < V; v++) {
        G->adj[v] = NULL;
    }
    return G;
}

void GRAPHshow(Graph G) {
    std::cout << "V = " << G->V << ", A = " << G->A << std::endl;
    for (int v = 0; v < G->V; v++) {
        std::cout << v << ": ";
        link p = G->adj[v];
        while (p != NULL) {
            std::cout << "-> " << p->vertex << " ";
            p = p->link;
        }
        std::cout << std::endl;
    }
}

bool arcExists(Graph G, int v, int w) {
    link p = G->adj[v];
    while (p != NULL) {
        if (p->vertex == w) {
            return true;
        }
        p = p->link;
    }
    return false;
}

void insertArcUnique(Graph G, int v, int w) {
    if (!arcExists(G, v, w)) {
        G->adj[v] = NEWnode(w, G->adj[v]);
        G->A++;
    }
}

void UGRAPHInsertEdge(Graph G, int v, int w) {
    if (v < 0 || v >= G->V || w < 0 || w >= G->V) {
        return;
    }
    insertArcUnique(G, v, w);
    insertArcUnique(G, w, v);
}

int degree(Graph G, int v) {
    int count = 0;
    link p = G->adj[v];
    while (p != NULL) {
        count++;
        p = p->link;
    }
    return count;
}

int UGRAPHdegrees(Graph G) {
    int maxDegree = 0;
    for (int v = 0; v < G->V; v++) {
        int currentDegree = degree(G, v);
        maxDegree = std::max(maxDegree, currentDegree);
    }
    return maxDegree;
}

int main() {
    int V = 5;
    Graph G = GRAPHinit(V);

    UGRAPHInsertEdge(G, 1, 2);
    UGRAPHInsertEdge(G, 1, 3);
    UGRAPHInsertEdge(G, 2, 4); 
    UGRAPHInsertEdge(G, 3, 4);

    std::cout << "--- Grafo de Prueba ---" << std::endl;
    GRAPHshow(G);

    UGRAPHInsertEdge(G, 0, 1);
    
    std::cout << "\n--- Grafo Modificado ---" << std::endl;
    GRAPHshow(G);
    
    int max = UGRAPHdegrees(G);
    
    std::cout << "\nEl grado maximo del grafo es: " << max << std::endl;

    free(G->adj);
    free(G);

    return 0;
}