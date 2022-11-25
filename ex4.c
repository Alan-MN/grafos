#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int lista_adj[1000];
    int tam_lista_adj;
    int distance;
}vertice;


void dfs(vertice *vertices, int qtd_vertices, int raiz, int distancia);

int main()
{
    int qtd_vertices, qtd_arestas;
    int a,b,maior_dist_total = 0,maior_dist = 0, indice_Md;
    vertice * vertices;
    scanf("%d ",&qtd_vertices);

    qtd_arestas = qtd_vertices-1;

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i=0;i<=qtd_arestas;i++)
    {
        scanf("%d %d",&a,&b);
        vertices[a].lista_adj[vertices[a].tam_lista_adj] = b;
        vertices[a].tam_lista_adj++;
        vertices[b].lista_adj[vertices[b].tam_lista_adj] = a;
        vertices[b].tam_lista_adj++;
    }    
    dfs(vertices,qtd_vertices,1,0);

    for(int i = 1; i<=qtd_vertices;i++)
    {
        if(vertices[i].distance > maior_dist){
            maior_dist = vertices[i].distance;
            indice_Md = i;
        }
    }

    for(int i = 1; i<=qtd_vertices;i++){
        if(vertices[i].visitado == 1){
            vertices[i].visitado =0 ;
        }    
    }
    maior_dist = 0;
    dfs(vertices,qtd_vertices,indice_Md,0);
    for(int i = 0; i<qtd_vertices;i++){
        if(vertices[i].distance > maior_dist){
            maior_dist = vertices[i].distance;
        }
    }
    printf("%d",maior_dist);

    return 0;
}


void dfs(vertice *vertices, int qtd_vertices, int raiz, int distance)
{
    int i;

    if(vertices[raiz].visitado!=0){
        return;
    }

    vertices[raiz].visitado=1;
    vertices[raiz].distance = distance;

    for(i=0;i<vertices[raiz].tam_lista_adj;i++)
    {
        if (vertices[vertices[raiz].lista_adj[i]].visitado==0)
        {
            dfs(vertices,qtd_vertices,vertices[raiz].lista_adj[i], distance+1);
        }
    }
}