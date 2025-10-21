#include <stdio.h>
#include <stdlib.h>

#define vertex int

typedef struct node *link;
struct node {
    vertex w;
    link next;
};

struct graph {
    int V;
    int A;
    link *adj;
};
typedef struct graph *Graph;

static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof(struct node));
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

// Calcula grado de salida de v (cantidad de arcos que salen de v)
int GRAPHoutdeg(Graph G, vertex v) {
    int count = 0;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        count++;
    return count;
}

// Calcula grado de entrada de v (cantidad de arcos que llegan a v)
int GRAPHindeg(Graph G, vertex v) {
    int count = 0;
    for (vertex u = 0; u < G->V; u++) {
        for (link a = G->adj[u]; a != NULL; a = a->next) {
            if (a->w == v) count++;
        }
    }
    return count;
}

// Función para testear
int main() {
    Graph G = GRAPHinit(6);

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 5);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 5);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 3, 1);
    GRAPHinsertArc(G, 5, 3);

    printf("Grado de salida del vértice 1: %d\n", GRAPHoutdeg(G, 1));
    printf("Grado de entrada del vértice 1: %d\n", GRAPHindeg(G, 1));

    return 0;
}
