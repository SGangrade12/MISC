#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 100
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;} Queue;
typedef struct {
    int items[MAX_VERTICES];
    int top;} Stack;
typedef struct {
    int vertices;
    bool adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];} Graph;
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;}
bool isEmpty(Queue* q) {
    return q->rear == -1;}
void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        printf("Queue is full\n");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;}}
int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = -1;
            q->rear = -1;}
        return item;}}
Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;}
bool isStackEmpty(Stack* s) {
    return s->top == -1;}
void push(Stack* s, int value) {
    if (s->top == MAX_VERTICES - 1)
        printf("Stack is full\n");
    else {
        s->top++;
        s->items[s->top] = value;}}
int pop(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    } else {
        int item = s->items[s->top];
        s->top--;
        return item;}}
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjacencyMatrix[i][j] = false;}}
    return graph;}
void addEdge(Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = true;    
    graph->adjacencyMatrix[dest][src] = true;}
void BFS(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    Queue* q = createQueue();
    visited[startVertex] = true;
    printf("BFS traversal starting from vertex %d: ", startVertex);
    printf("%d ", startVertex);
    enqueue(q, startVertex);
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjacencyMatrix[currentVertex][i] && !visited[i]) {
                printf("%d ", i);
                visited[i] = true;
                enqueue(q, i);}}}
    printf("\n");
    free(q);}
void DFSRecursive(Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] && !visited[i])
            DFSRecursive(graph, i, visited);}}
void DFS(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    printf("DFS traversal starting from vertex %d: ", startVertex);
    DFSRecursive(graph, startVertex, visited);
    printf("\n");}
void DFSIterative(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    Stack* s = createStack();
    printf("Iterative DFS traversal starting from vertex %d: ", startVertex);
    push(s, startVertex);
    while (!isStackEmpty(s)) {
        int currentVertex = pop(s);
        if (!visited[currentVertex]) {
            printf("%d ", currentVertex);
            visited[currentVertex] = true;}
        for (int i = graph->vertices - 1; i >= 0; i--) {
            if (graph->adjacencyMatrix[currentVertex][i] && !visited[i]) {
                push(s, i);}}}
    printf("\n");
    free(s);}
int main() {
    Graph* graph = createGraph(7);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);
    printf("Graph Traversal Algorithms\n");
    printf("==========================\n\n");
    BFS(graph, 0);
    DFS(graph, 0);
    DFSIterative(graph, 0);
    free(graph);
    return 0;}