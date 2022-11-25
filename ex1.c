/*
Faça um programa que receba do usuário N pares de valores, onde cada PAR representa uma aresta
bidirecional entre cada valor do par.
Mostre uma matriz de adjacência que represente esse grafo
Mostre uma lista de adjacência que represente esse grafo.
1 2
1 4
2 5
3 6
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct lista{
    int qtd;
    struct registro *inicio;
    struct registro *fim;

}lista;

typedef struct registro{
    int valor1;
    int valor2;
    int qtd_ligacoes;
    int *ligacoes;
    struct registro *ant;
    struct registro *prox;
}registro;


registro *aloca_registro();
lista *aloca_lista();
void incluir_final(lista *l1, int n1,int n2);
void mostrar_lista(lista *l1);
void monta_matriz(lista *lista_pares);




void main(){
    int qtd_pares;
    printf("informe a quantidade de pares: ");
    scanf("%d",&qtd_pares);
    lista *lista_pares = aloca_lista();

    for(int i = 0; i<qtd_pares; i++){
        int par1,par2;
        printf("\ninforme o os pares a serem adicionados:");
        scanf("%d %d",&par1,&par2);
        incluir_final(lista_pares,par1,par2);
    }
    mostrar_lista(lista_pares);
    printf("\nMatriz: (50x50)\n");
    monta_matriz(lista_pares);
}



void monta_matriz(lista *lista_pares){
    int tam = 20;
    int *matriz = (int*)malloc(tam * tam * sizeof(int));

    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            int indice = (i*tam) +j;
            matriz[indice] = 0;
        }
    }


    if(lista_pares->inicio == NULL){
        printf("lista vazia\n");
    }
    else{
        registro *aux;
        aux = lista_pares->inicio;
        while(aux!=NULL){
            matriz[(aux->valor1-1)*tam+(aux->valor2-1)] = 1;
            matriz[(aux->valor1-1)+tam*(aux->valor2-1)] = 1;
            matriz[(aux->valor1-1)+tam*(aux->valor1-1)] = 1;
            matriz[(aux->valor2-1)+tam*(aux->valor2-1)] = 1;
            aux = aux->prox;
        }
    }
       

    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            int indice = i*tam +j;
            printf("%d",matriz[indice]);
        }
        printf("\n");
    }
    free(matriz);
}




lista *aloca_lista(){
    lista *l;
    l = (lista *)calloc(1,sizeof(lista));
    return l;
}

registro *aloca_registro(){
    registro *novo_reg;
    novo_reg = (registro*)calloc(1,sizeof(registro));
    return novo_reg;
}


void incluir_final(lista *l1, int n1, int n2){

    registro *novo,*aux;
    novo = aloca_registro();
    novo->valor1 = n1;
    novo->valor2 = n2;
    novo->qtd_ligacoes = 1;
    if(l1->inicio == NULL){
        l1->inicio = novo;
        l1->qtd++;
    }
    else{
        aux = l1->inicio;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
        l1->fim = novo;
        l1->qtd++;
    }
}



void mostrar_lista(lista *l1){
    if(l1->inicio == NULL){
        printf("lista vazia\n");
    }
    else{
        registro *aux;
        aux = l1->inicio;
        printf("pares recebidos: \n");
        while(aux!=NULL){
            printf("%d %d \n",aux->valor1, aux->valor2);
            aux = aux->prox;
        }
    }
}