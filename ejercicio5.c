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

// Libera toda la memoria usada por el grafo
void GRAPHdestroy(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        link a = G->adj[v];
        while (a != NULL) {
            link temp = a;
            a = a->next;
            free(temp);
        }
    }
    free(G->adj);
    free(G);
}

// Ejemplo para probar
int main() {
    Graph G = GRAPHinit(6);

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 5);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 5);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 3, 1);
    GRAPHinsertArc(G, 5, 3);

    // Usamos el grafo (por ejemplo mostramos)
    for (vertex v = 0; v < G->V; v++) {
        printf("%d:", v);
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            printf(" %d", a->w);
        }
        printf("\n");
    }

    GRAPHdestroy(G);  // Liberamos memoria

    return 0;
}
