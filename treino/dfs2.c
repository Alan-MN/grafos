#include <stdio.h>
#include <stdlib.h>

typedef struct vertice{
    int adj_list[100];
    int tamanho_adj;
    int visitado;
    int dist;
}vertice;


int dfs(vertice * vertices, int qtd_vertices,int raiz, int dist);
void faz_consultas(vertice *vertices, int qtd_vertices, int qtd_consultas);

void main(){
    int qtd_vertices, qtd_pares;
    vertice * vertices = (vertice*)calloc( qtd_vertices+1 ,sizeof(vertice));
    printf("informe quantos vertices ");
    scanf("%d", &qtd_vertices);
    printf("informe quantos pares ");
    scanf("%d", &qtd_pares);

    for(int i = 0; i < qtd_pares; i++ ){
        int n1,n2;
        printf("informe o par");
        scanf("%d %d",&n1, &n2);

        vertices[n1].adj_list[vertices[n1].tamanho_adj] = n2;
        vertices[n1].tamanho_adj++;
        vertices[n2].adj_list[vertices[n2].tamanho_adj] = n1;
        vertices[n2].tamanho_adj++;
                
    }

    dfs(vertices,qtd_vertices,1,0);
    for(int i = 1; i <= qtd_vertices; i++){
        printf("%d -> %d",i,vertices[i].dist);
        printf(".\n");
    }

    int consultas;
    scanf("%d", &consultas);
    printf("Consultas: %d\n",consultas);
    faz_consultas(vertices,qtd_vertices,consultas);
}

int dfs(vertice * vertices, int qtd_vertices,int raiz, int dist){
    if(vertices[raiz].visitado == 0){
        vertices[raiz].visitado = 1; 
        vertices[raiz].dist = dist;
    }

    for(int i = 0; i < vertices[raiz].tamanho_adj; i++){
        if(vertices[vertices[raiz].adj_list[i]].visitado == 0){
            dfs(vertices, qtd_vertices, vertices[raiz].adj_list[i], dist+1);
        }
    }
}

void faz_consultas(vertice *vertices, int qtd_vertices, int qtd_consultas){
    int *consultas = (int*)calloc(qtd_consultas*2,sizeof(int));
    int *resultados = (int*)calloc(qtd_consultas,sizeof(int));


    for(int j = 0 ; j<qtd_consultas;j++){
        int r1,r2;
        scanf("%d %d",&r1,&r2);
        consultas[(j*2)] = r1;
        consultas[(j*2)+1] = r2;

        printf("recebido: %d %d\n",consultas[(j*2)],consultas[(j*2)+1] );

    }


    for(int i = 0; i< qtd_consultas;i++){

        for(int j = 1; j<=qtd_vertices;j++){
            if(vertices[j].visitado==1){
                vertices[j].visitado = 0;
            }
        }

        

        dfs(vertices,qtd_vertices,consultas[(i*2)],0);
        for(int j = 1; j <= qtd_vertices; j++){
            if(j == consultas[(i*2)+1]){
                resultados[i] = vertices[j].dist;
            }
        }
    }


    for(int i = 0; i<qtd_consultas;i++){
        printf("%d\n",resultados[i]);
    }

   
}