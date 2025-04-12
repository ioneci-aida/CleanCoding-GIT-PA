/* Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf */
// am modificat un pic notatiile sa fie mai omenesti mai placute
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct g
{
    int v; // nr total de noduri 
    int *vis;   // noduri vizitate
    struct Node **alst; // lista de adiacenta
} GPH;

typedef struct s
{
    int t; // top
    int stk_cap; // stack capacity
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest)
{
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v)
{
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v); // alocam o lista intreaga de v elemente
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int stk_cap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(stk_cap * sizeof(int));
    s->t = -1;
    s->stk_cap = stk_cap;
    return s;
}

void push(int pshd, STK *s)
{
    s->t = s->t + 1; // s->t este stack-> top
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_idx)
{
    NODE *adj_list = g->alst[v_idx];
    NODE *aux = adj_list;
    g->vis[v_idx] = 1; // v_idx este nodul curent
    printf("%d ", v_idx + 1); // afisam +1 pentru user
    push(v_idx, s);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int no_edges)
{
    int src, dest, i;
    printf("adauga %d muchii (cu indicii de la 1 la %d)\n", no_edges, g->v); // user-friendly, indexare de la 1
    for (i = 0; i < no_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src - 1, dest - 1); // transformam in 0-based
    }
}

void wipe(GPH *g, int no_nodes)
{
    for (int i = 0; i < no_nodes; i++)
    {
        g->vis[i] = 0;
    }
}

int canbe(GPH *g, int src, int dest) // 0 sau 1 daca poate fi sau nu ajuns
{
   /* eu aici practic trebuie sa verific daca exista nod de la un restaurant la altul
    daca trebuie 0 sau 1, schimb tipul functiei o fac int
    Nu au sens declararile, doar parcurg in adancime de la src la dest */

    STK* s = create_s(2 * g->v); // worst case scenario, parcurgem toate nodurile
    DFS(g, s, src);
    int can_be = g->vis[dest]; // daca s-a pus 1 inseamna ca se poate ajunge din src
    
    // eliberam memoria
    free(s->arr);
    free(s);

    return can_be;
}

int main()
{
    int no_nodes;
    int no_edges;
    int vertex_1;
    int vertex_2;
    int ans;

    printf("Cate noduri are graful?(restaurante)  ");
    scanf("%d", &no_nodes);

    printf("Cate muchii are graful?(drumuri)  ");
    scanf("%d", &no_edges);

    GPH *g = create_g(no_nodes);

    insert_edges(g, no_edges);

    printf("Indicii pentru restaurantele intre care verificam daca este drum? (de la 1 la %d):\n", no_nodes);
    scanf("%d %d", &vertex_1, &vertex_2); 

    ans = canbe(g, vertex_1 - 1, vertex_2 - 1);

    if(ans == 1)
        printf("Este drum de la restaurantul %d la restaurantul %d.\n", vertex_1, vertex_2);
    else
        printf("Nu este drum de la restaurantul %d la restaurantul %d.\n", vertex_1, vertex_2);
}
