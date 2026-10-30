/*
    DSA Practical 22: Graph Representation (Adjacency Matrix) + BFS, DFS
    ----------------------------------------------------
    Compile : gcc graph_bfs_dfs.c -o graph_bfs_dfs
    Run     : ./graph_bfs_dfs
*/

#include <stdio.h>

#define MAX 10

int adj[MAX][MAX];
int visited[MAX];
int nV;

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;   // undirected graph
}

void bfs(int start) {
    int q[MAX], front = 0, rear = 0;
    for (int i = 0; i < nV; i++) visited[i] = 0;

    visited[start] = 1;
    q[rear++] = start;

    printf("BFS: ");
    while (front < rear) {
        int u = q[front++];
        printf("%d ", u);
        for (int v = 0; v < nV; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                q[rear++] = v;
            }
        }
    }
    printf("\n");
}

void dfsUtil(int u) {
    visited[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < nV; v++) {
        if (adj[u][v] && !visited[v]) {
            dfsUtil(v);
        }
    }
}

void dfs(int start) {
    for (int i = 0; i < nV; i++) visited[i] = 0;
    printf("DFS: ");
    dfsUtil(start);
    printf("\n");
}

int main() {
    int nE, u, v, start;

    printf("Enter number of vertices: ");
    scanf("%d", &nV);

    printf("Enter number of edges: ");
    scanf("%d", &nE);

    for (int i = 0; i < nV; i++)
        for (int j = 0; j < nV; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < nE; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    printf("Enter starting vertex for traversal: ");
    scanf("%d", &start);

    bfs(start);
    dfs(start);

    return 0;
}