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


bool arcExists(Graph G, int w, int v) {
    link p = G->adj[w];
    while (p != NULL) {
        if (p->vertex == v) {
            return true;
        }
        p = p->link;
    }
    return false;
}

bool GRAPHundir(Graph G) {
    for (int v = 0; v < G->V; v++) {
        link p = G->adj[v];
        while (p != NULL) {
            int w = p->vertex;
            if (!arcExists(G, w, v)) {
                return false;
            }
            p = p->link;
        }
    }
    return true;
}

int main() {
    int V = 3;
    
    Graph G1 = GRAPHinit(V);
    GRAPHinsertArc(G1, 0, 1);
    GRAPHinsertArc(G1, 1, 0);
    GRAPHinsertArc(G1, 1, 2);
    GRAPHinsertArc(G1, 2, 1);

    std::cout << "--- Grafo G1 (Simetrico) ---" << std::endl;
    GRAPHshow(G1);
    std::cout << "G1 es no dirigido: " << (GRAPHundir(G1) ? "Verdadero" : "Falso") << std::endl;

    Graph G2 = GRAPHinit(V);
    GRAPHinsertArc(G2, 0, 1);
    GRAPHinsertArc(G2, 1, 2);
    GRAPHinsertArc(G2, 2, 1);
    
    std::cout << "\n--- Grafo G2 (No Simetrico) ---" << std::endl;
    GRAPHshow(G2);
    std::cout << "G2 es no dirigido: " << (GRAPHundir(G2) ? "Verdadero" : "Falso") << std::endl;

    free(G1->adj);
    free(G1);
    free(G2->adj);
    free(G2);

    return 0;
}