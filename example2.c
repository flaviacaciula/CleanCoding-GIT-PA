#include <stdlib.h>
#include <stdio.h>

typedef struct Node 
{
  int data;
  struct Node *next;
} NODE;

typedef struct Graph 
{
  int vertices;
  int *visited;
  struct Node **adjacency_lists;
} GPH;

NODE *create_node(int v) 
{
  NODE *new_node = malloc(sizeof(NODE));
  new_node->data = v;
  new_node->next = NULL;
  return new_node;
}

GPH *create_graph(int vertices) 
{
  GPH *graph = malloc(sizeof(GPH));
  graph->vertices = vertices;
  graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
  graph->visited = malloc(sizeof(int) * vertices);
  for (int i = 0; i < vertices; i++) 
  {
    graph->adjacency_lists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

void add_edge(GPH *graph, int src, int dest) 
{
  NODE *new_node = create_node(dest);
  new_node->next = graph->adjacency_lists[src];
  graph->adjacency_lists[src] = new_node;
  new_node = create_node(src);
  new_node->next = graph->adjacency_lists[dest];
  graph->adjacency_lists[dest] = new_node;
}

void DFS(GPH *graph, int vertex_nr) 
{
  graph->visited[vertex_nr] = 1;
  printf("%d ", vertex_nr);
  NODE *temp = graph->adjacency_lists[vertex_nr];
  while (temp) 
  {
    int connected_vertex = temp->data;
    if (graph->visited[connected_vertex] == 0) 
    {
      DFS(graph, connected_vertex);
    }
    temp = temp->next;
  }
}

void BFS(GPH *graph, int start) 
{
  int *queue = malloc(graph->vertices * sizeof(int));
  int front = 0, rear = 0;
  graph->visited[start] = 1;
  printf("%d ", start);
  queue[rear++] = start;
  while (front < rear) 
  {
    int current = queue[front++];
    NODE *temp = graph->adjacency_lists[current];
    while (temp) {
      int adj_vertex = temp->data;
      if (graph->visited[adj_vertex] == 0) 
      {
        graph->visited[adj_vertex] = 1;
        printf("%d ", adj_vertex);
        queue[rear++] = adj_vertex;
      }
      temp = temp->next;
    }
  }
  free(queue);
}

int main() 
{
  int nr_of_vertices, nr_of_edges, starting_vertex;
  printf("Cate noduri are graful? ");
  scanf("%d", &nr_of_vertices);
  printf("Cate muchii are graful? ");
  scanf("%d", &nr_of_edges);
  GPH *graph = create_graph(nr_of_vertices);
  printf("Adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices - 1);
  for (int i = 0; i < nr_of_edges; i++) 
  {
    int src, dest;
    scanf("%d %d", &src, &dest);
    add_edge(graph, src, dest);
  }
  printf("De unde plecam in DFS? ");
  scanf("%d", &starting_vertex);
  printf("Parcurgere cu DFS: ");
  DFS(graph, starting_vertex);
  printf("\n");
  // Resetăm vizitările pentru BFS
  for (int i = 0; i < nr_of_vertices; i++) 
  {
    graph->visited[i] = 0;
  }
  printf("De unde plecam in BFS? ");
  scanf("%d", &starting_vertex);
  printf("Parcurgere cu BFS: ");
  BFS(graph, starting_vertex);
}