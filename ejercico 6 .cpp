#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

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

void GRAPHinsertArc(Graph G, int v, int w) {
    link p = G->adj[v];
    while (p != NULL) {
        if (p->vertex == w) return;
        p = p->link;
    }
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
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

void GRAPHremoveArc(Graph G, int v, int w) {
    if (v < 0 || v >= G->V || w < 0 || w >= G->V) {
        return;
    }

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
            return;
        }
        
        prev = p;
        p = p->link;
    }
}

int main() {
    int V = 4;
    Graph G = GRAPHinit(V);

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 2);
    GRAPHinsertArc(G, 0, 3);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 0);

    std::cout << "--- Grafo Inicial ---" << std::endl;
    GRAPHshow(G);

    std::cout << "\n--- Eliminando 0 -> 2 ---" << std::endl;
    GRAPHremoveArc(G, 0, 2);
    GRAPHshow(G);
    
    std::cout << "\n--- Eliminando 2 -> 0 ---" << std::endl;
    GRAPHremoveArc(G, 2, 0);
    GRAPHshow(G);
    
    std::cout << "\n--- Eliminando 0 -> 3 ---" << std::endl;
    GRAPHremoveArc(G, 0, 3);
    GRAPHshow(G);
    
    std::cout << "\n--- Intentando eliminar 0 -> 3 (NOEXISTE) ---" << std::endl;
    GRAPHremoveArc(G, 0, 3);
    GRAPHshow(G);
    free(G->adj);
    free(G);

    return 0;
}