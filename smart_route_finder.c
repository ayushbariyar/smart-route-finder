#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};
struct Graph {
    int numVertices;
    struct Node** adjLists;
};
struct Node* createNode(int v, int weight) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
void printGraph(struct Graph* graph) {
    for(int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("City %d -> ", v);
        while(temp) {
            printf("(City %d, Dist:%d) -> ",
                   temp->vertex,
                   temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    for(int i = 0; i < vertices; i++){
        graph->adjLists[i] = NULL;
    }
    return graph;
}
int minDistance(int dist[], int visited[], int vertices) {
    int min = INT_MAX;
    int minIndex = -1;
    for(int i = 0; i < vertices; i++) {
        if(visited[i] == 0 && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}
void printPath(int parent[], int city) {
    if(parent[city] == -1) {
        printf("%d ", city);
        return;
    }
    printPath(parent, parent[city]);
    printf("-> %d ", city);
}
void dijkstra(struct Graph* graph, int src) {
    int V = graph->numVertices;
    int dist[V];
    int visited[V];
    int parent[V];
    for(int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;
    for(int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if(u == -1) break;
        visited[u] = 1;
        struct Node* temp = graph->adjLists[u];
        while(temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if(!visited[v] &&
               dist[u] != INT_MAX &&
               dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    printf("\nShortest distances from City %d:\n", src);
    for(int i = 0; i < V; i++) {
        printf("To City %d -> Distance: %d\n", i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}
int main() {
    struct Graph* graph = createGraph(5);
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 5);
    addEdge(graph, 1, 2,3);
    printGraph(graph);
    dijkstra(graph, 0);
    return 0;
}





