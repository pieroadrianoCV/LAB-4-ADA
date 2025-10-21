#include <iostream>
#include <cstdlib>
#include <cstdio>

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

bool removeArcInternal(Graph G, int v, int w) {
    link p = G->adj[v];
    link prev = NULL;
    
    while (p != NULL) {
        if (p->vertex == w) {
            if (prev == NULL) {
                G->adj[v] = p->link;
            } else {
                prev->link = p->link;
            }

            free(p);
            G->A--;
            return true;
        }
        
        prev = p;
        p = p->link;
    }
    return false;
}

void UGRAPHremoveEdge(Graph G, int v, int w) {
    if (v < 0 || v >= G->V || w < 0 || w >= G->V) {
        return;
    }
    
    removeArcInternal(G, v, w);
    
    removeArcInternal(G, w, v);
}

int main() {
    int V = 4;
    Graph G = GRAPHinit(V);
    UGRAPHInsertEdge(G, 0, 1);
    UGRAPHInsertEdge(G, 1, 2);
    UGRAPHInsertEdge(G, 2, 3);
    
    std::cout << "--- Grafo Inicial ) ---" << std::endl;
    GRAPHshow(G);

    std::cout << "\n--- Eliminando arista 1a2 ---" << std::endl;
    UGRAPHremoveEdge(G, 1, 2);
    GRAPHshow(G); // A debe ser 4

    std::cout << "\n--- Eliminando arista 0a1 ---" << std::endl;
    UGRAPHremoveEdge(G, 0, 1);
    GRAPHshow(G); // A debe ser 2
    
    std::cout << "\n--- Intentando eliminar arista 0a2 (noexiste) ---" << std::endl;
    UGRAPHremoveEdge(G, 0, 2);
    GRAPHshow(G); 

    free(G->adj);
    free(G);

    return 0;
}