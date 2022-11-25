#include <stdio.h>
#include <stdlib.h>

typedef struct connection{
    int node;
    int distance;
}connection;

typedef struct graph{
    struct connection adj_list[1000];
    int adj_list_size;
    int visitado;
}graph;


void mostrar_tudo (graph * vertices, int qtd_vertices);
void dijkstra(graph * grafo, int qtd_arestas,int raiz ,int dist,int *distancias);
// custo pra inserir no min heap O de 1 retirar n * log n

void main(){
    int qtd_vertices, qtd_arestas;
    int i,a,b,qtd_cc=0;
    graph * vertices;
    scanf("%d %d",&qtd_vertices, &qtd_arestas);

    vertices = (graph*)calloc(qtd_vertices+1,sizeof(graph));

    for(i=1;i<qtd_arestas;i++)
    {
        scanf("%d %d ",&a,&b);
        int c  = 4;
        vertices[a].adj_list[vertices[a].adj_list_size].node= b;
        vertices[a].adj_list[vertices[a].adj_list_size].distance = c;
        vertices[a].adj_list_size++;
        vertices[b].adj_list[vertices[b].adj_list_size].node = a;
        vertices[b].adj_list[vertices[b].adj_list_size].distance = c;
        vertices[b].adj_list_size++;
    }
    int *distancias = (int*)calloc(qtd_arestas +1 ,sizeof(int));

    for(int i  = 1; i <qtd_arestas; i++){
        distancias[i] = 99999;
    }

    dijkstra(vertices, qtd_arestas,1,0,distancias);
    printf("distancia a partir do node 1: ");
    for(int i  = 1 ; i <=qtd_arestas;i++){
        printf(" %d - %d ", i,distancias[i]);
    }
    mostrar_tudo(vertices,qtd_arestas);
}


void dijkstra(graph * grafo, int qtd_arestas,int raiz ,int dist,int *distancias){
    if(grafo[raiz].visitado == 1){
        return;
    }
    if(dist == 0){
        distancias[raiz] = 0;
    }

    grafo[raiz].visitado = 1;
    int menor_c = 99999;
    int menor_node;

    for(int i =0;i< grafo[raiz].adj_list_size;i++){

        if(distancias[grafo[raiz].adj_list[i].node] > grafo[raiz].adj_list[i].distance){
            distancias[grafo[raiz].adj_list[i].node] = grafo[raiz].adj_list[i].distance;
        }
        if(menor_c > grafo[raiz].adj_list[i].distance){
            menor_c = grafo[raiz].adj_list[i].distance;
            menor_node = grafo[raiz].adj_list[i].node;
        }
    }
    printf("node:  %d distance: %d \n",grafo[raiz].adj_list[menor_node].node, grafo[raiz].adj_list[menor_node].distance );

    dijkstra(grafo, qtd_arestas, menor_node , dist + grafo[raiz].adj_list[menor_node].distance , distancias);
}






void mostrar_tudo (graph * vertices, int qtd_vertices)
{
    int i,j;

    for(i=1;i<=qtd_vertices;i++)
    {
        printf("\n Vertice: %d",i);
        printf("\n Lista de adjacencias: ");

        for(j=0;j<vertices[i].adj_list_size;j++)
        {
            printf("%d ",vertices[i].adj_list[j]);
        }

        printf("\n Lista de distancias: ");
        for(j=0;j<vertices[i].adj_list_size;j++)
        {
            printf("%d ",vertices[i].adj_list[j].distance);
        }

    }
}