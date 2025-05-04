#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_VERTICES 100
#define INF INT_MAX
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int V) {
    int dist[V];
    bool sptSet[V];
    int parent[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = false;
        parent[i] = -1;}
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int min = INF, min_index;
        for (int v = 0; v < V; v++)
            if (sptSet[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;
        int u = min_index;
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];}}
    printf("\nVertex\tDistance\tPath");
    for (int i = 0; i < V; i++) {
        printf("\n%d -> %d\t%d\t\t", src, i, dist[i]);
        int j = i;
        while (j != src) {
            printf("%d <- ", j);
            j = parent[j];}
        printf("%d", src);}
    printf("\n");}
void bellmanFord(int graph[MAX_VERTICES][MAX_VERTICES], int src, int V) {
    int dist[V];
    int parent[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;}
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;}}}}
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                printf("Graph contains negative weight cycle\n");
                return;}}}
    printf("\nVertex\tDistance\tPath");
    for (int i = 0; i < V; i++) {
        printf("\n%d -> %d\t%d\t\t", src, i, dist[i]);
        int j = i;
        while (j != src && j != -1) {
            printf("%d <- ", j);
            j = parent[j];}
        if (j != -1) printf("%d", src);}
    printf("\n");}
void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int dist[V][V];
    int next[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != 0 && graph[i][j] != INF)
                next[i][j] = j;
            else
                next[i][j] = -1;}}
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];}}}}
    printf("\nAll-Pairs Shortest Paths:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                printf("\n%d -> %d: Distance = %d, Path: %d", i, j, dist[i][j], i);
                int path = i;
                while (path != j) {
                    path = next[path][j];
                    if (path == -1) {
                        printf(" -> No path exists");
                        break;}
                    printf(" -> %d", path);}}}}
    printf("\n");}
int main() {
    int V, E, choice, src;
    int graph[MAX_VERTICES][MAX_VERTICES];
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;}}
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edge information (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;}
    while (1) {
        printf("\n=== SHORTEST PATH ALGORITHMS ===\n");
        printf("1. Dijkstra's Algorithm\n");
        printf("2. Bellman-Ford Algorithm\n");
        printf("3. Floyd-Warshall Algorithm\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter source vertex: ");
                scanf("%d", &src);
                dijkstra(graph, src, V);
                break;
            case 2:
                printf("Enter source vertex: ");
                scanf("%d", &src);
                bellmanFord(graph, src, V);
                break;
            case 3:
                floydWarshall(graph, V);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");}}}