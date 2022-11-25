#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int lista_adj[1000];
    int tam_lista_adj;
    int visitado;
    int in;
    int lower;
}vertice;

int count;

void dfs2(vertice * vertices, int qtd_vertices, int raiz, int anterior);
int menor(int a, int b);

void main()
{
    int qtd_vertices, qtd_arestas;
    int i,a,b,qtd_cc=0;
    vertice * vertices;
    scanf("%d %d",&qtd_vertices, &qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(i=0;i<qtd_arestas;i++)
    {
        scanf("%d %d",&a,&b);
        vertices[a].lista_adj[vertices[a].tam_lista_adj] = b;
        vertices[a].tam_lista_adj++;
        vertices[b].lista_adj[vertices[b].tam_lista_adj] = a;
        vertices[b].tam_lista_adj++;
    }
    dfs2(vertices,qtd_vertices,1,1);
}



void dfs2(vertice * vertices, int qtd_vertices, int raiz, int anterior)
{
    int i,proximo;

    vertices[raiz].visitado = 1;
    vertices[raiz].in = count;
    vertices[raiz].lower = count;
    count++;

    for(i=0;i<vertices[raiz].tam_lista_adj;i++)
    {
        proximo = vertices[raiz].lista_adj[i];
        if(proximo != anterior)
        {
            if (vertices[proximo].visitado == 1)
            {
                //printf("achou back edge")
                vertices[raiz].lower = menor(vertices[raiz].lower,vertices[proximo].in);
            }
            else
            {
                //checar se é ponte
                dfs2(vertices,qtd_vertices,proximo,raiz);
                if (vertices[proximo].lower > vertices[raiz].in)
                {
                    printf("\n A estrada que conecta as cidades %d e %d  nao pode ser reformada", raiz, proximo);
                }
                vertices[raiz].lower = menor(vertices[raiz].lower, vertices[proximo].lower);
            }
        }
    }

}

int menor(int a, int b){ 
    if(a>b){
        return b;
    }
    return a;
}