#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_VERTICES 100
#define INF INT_MAX
typedef struct {
    int src, dest, weight;
} Edge;
typedef struct {
    int V, E;
    Edge* edges;
} Graph;
typedef struct {
    int parent;
    int rank;
} Subset;
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    return graph;}
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;}
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;}}
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;}
void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V-1];
    int e = 0;
    int i = 0;
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;}
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);}}
    printf("\nKruskal's MST:\n");
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        printf("Edge: %d -- %d  Weight: %d\n", 
               result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;}
    printf("Total Weight of MST: %d\n", totalWeight);
    free(subsets);}
int minKey(int key[], bool mstSet[], int V) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;}
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int parent[V];
    int key[V];
    bool mstSet[V];
    for (int i = 0; i < V; i++)
        key[i] = INF, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];}
    printf("\nPrim's MST:\n");
    int totalWeight = 0;
    for (int i = 1; i < V; i++) {
        printf("Edge: %d -- %d  Weight: %d\n", parent[i], i, graph[parent[i]][i]);
        totalWeight += graph[parent[i]][i];}
    printf("Total Weight of MST: %d\n", totalWeight);}
int main() {
    int choice, V, E, u, v, w;
    Graph* graph;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adjMatrix[i][j] = 0;
    printf("Enter number of edges: ");
    scanf("%d", &E);
    graph = createGraph(V, E);
    printf("Enter edge information (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph->edges[i].src = u;
        graph->edges[i].dest = v;
        graph->edges[i].weight = w;
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;}
    while (1) {
        printf("\n=== MINIMUM SPANNING TREE ALGORITHMS ===\n");
        printf("1. Find MST using Kruskal's Algorithm\n");
        printf("2. Find MST using Prim's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                kruskalMST(graph);
                break;
            case 2:
                primMST(adjMatrix, V);
                break;
            case 3:
                free(graph->edges);
                free(graph);
                return 0;
            default:
                printf("Invalid choice! Try again.\n");}}}