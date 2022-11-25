#include <stdio.h>
#include <stdlib.h>

typedef struct vertice{
    int adj_list[100];
    int tamanho_adj;
    int visitado;
    int dist;
}vertice;



/* a primeira linha da entrada tera um numero q de vertices, 
a segunda será um numero V Referente aos pares(arestas), nas proximas
V linhas serão informados os pares no formato '%d %d' . Após isso,
será informado um numero C que será a quantidade de consultas,e C
pares para que seja feita a consulta da distância entre os vertices. */

int dfs(vertice * vertices, int qtd_vertices,int raiz, int dist);
int consultas(vertice *vertices,int qtd_vertices);




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


int consultas(vertice *vertices,int qtd_vertices){
    int qtd_consultas;
    scanf("%d",&qtd_consultas);

    int *consultas = (int*)calloc(qtd_consultas*2,sizeof(int));
    int *resultados = (int*)calloc(qtd_consultas,sizeof(int));


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