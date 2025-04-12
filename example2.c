/*parcurgerge  graf cu DFS/BFS*/
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

/// utils
NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *create_graph(int vertices)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *)); //lista de adiacenta

    graph->visited = malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}

void add_edge(GPH *graph, int src, int dest) // Adaugam o muchie neorientata intre src si dest
{
    NODE *new_node = create_node(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

int *insedg(int nr_of_vertices, int nr_of_edges, GPH *graph)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d %d",&src, &dest); //citim cate muchii si ce muchii punem, dar in vector sunt indexate de la 0, deci trb sa punem
                                    //decrementat cu 1
        add_edge(graph, src - 1, dest - 1);
    }
}
/// bfs utils
int is_empty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);

    if (is_empty(*queue))
        *queue = new_node;
    else
    {
        NODE *temp = *queue; //sau fara *
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void print_graph(GPH *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i ++)
    {
        NODE *temp = graph->adjacency_lists[i];

        while (temp)
        {
            printf("%d ", temp->data + 1);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_queue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void wipe_visited_list(GPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i ++)
    {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GPH *graph, int vertex_nr)
{   
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    static int primul_apel = 1;// daca e primul apel afiseaza doar numarul, pentru o afisare prietenoasa

    if(primul_apel == 1){
        printf("%d",vertex_nr + 1);
        primul_apel = 0;
    }
    else
        printf("->%d", vertex_nr + 1);

    while (temp != NULL)
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
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current + 1);

        NODE *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{

    int nr_of_vertices;
    int nr_of_edges;
    int src, dest;
    int i;
    int starting_vertex;
    int *adj_matrix;

    printf("cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nr_of_vertices);
    insedg(nr_of_vertices, nr_of_edges, graph);

    printf("de unde plecam in DFS?");
    scanf("%d", &starting_vertex); // =)))
    starting_vertex --;
    printf("parcurgere cu DFS:");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph, nr_of_vertices); //refacem tot la 0 ca si cum lista nu a fost parcursa
                                              //pentru bfs
    printf("\n");

    printf("de unde plecam in BFS?");
    scanf("%d", &starting_vertex);
    starting_vertex --;//tot legat de incrementare
    printf("parcurgere cu BFS:");
    BFS(graph, starting_vertex);

    return 0;
}
