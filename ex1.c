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
    struct registro *ant;
    struct registro *prox;
}registro;

typedef struct lista_adj{
    int qtd;
    struct registro_adj *inicio;
    struct registro_adj *fim;

}lista_adj;

typedef struct registro_adj{
    int valor;
    int qtd_ligacoes;
    int *ligacoes;
    struct registro_adj *ant;
    struct registro_adj *prox;
}registro_adj;

registro *aloca_registro();
lista *aloca_lista();
void incluir_final(lista *l1, int n1,int n2);
void mostrar_lista(lista *l1);
void monta_matriz(lista *lista_pares);
lista_adj *aloca_lista_adj();
registro_adj *aloca_registro_adj();
void monta_lista_adj(lista *lista_pares);
void mostrar_lista_adj(lista_adj *l1);
void incluir_final_adj(lista_adj *l1, int n, int *vetor);






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
    printf("\nLista: \n");
    monta_lista_adj(lista_pares);
}



void monta_matriz(lista *lista_pares){
    int tam = 50;
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

void monta_lista_adj(lista *lista_pares){
    lista_adj *lista = aloca_lista_adj();
    registro_adj *aux = lista->inicio;
    registro *aux_pares = lista_pares->inicio;
    /*for(int i = 0; i < lista_pares->qtd; i++){
        if(aux->valor == aux_pares->valor1 && aux_pares!= NULL ){
            while(aux->valor == aux_pares->valor1){
                aux->qtd_ligacoes++;
                aux_pares = aux_pares->prox;
                printf("achei um numero repetido e aumentei as ligações para %d",aux->qtd_ligacoes);
            }
        }
        else{
            incluir_final_adj(lista,aux_pares->valor1,NULL);
            aux = aux->prox;
            aux_pares = aux_pares->prox;
        }
        
    }*/
    while(aux_pares!= NULL){
        if(aux_pares->valor1 == aux->valor){
            aux->qtd_ligacoes++;
            aux_pares = aux_pares->prox;
            printf("achei um numero repetido e aumentei as ligações para %d",aux->qtd_ligacoes);
        }
        else{
            incluir_final_adj(lista,aux_pares->valor1,NULL);
            aux_pares = aux_pares->prox;
            aux = aux->prox;
        }
    } 
    mostrar_lista_adj(lista);
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
lista_adj *aloca_lista_adj(){
    lista_adj *l;
    l = (lista_adj *)calloc(1,sizeof(lista_adj));
    return l;
}

registro_adj *aloca_registro_adj(){
    registro_adj *novo_reg;
    novo_reg = (registro_adj*)calloc(1,sizeof(registro_adj));
    return novo_reg;
}


void incluir_final(lista *l1, int n1, int n2){

    registro *novo,*aux;
    novo = aloca_registro();
    novo->valor1 = n1;
    novo->valor2 = n2;
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

void incluir_final_adj(lista_adj *l1, int n, int *vetor){
    printf("entrei no incluir no final tentando adicionar o valor de %d\n",n);
    registro_adj *novo,*aux;
    novo = aloca_registro_adj();
    novo->valor = n;
    novo->ligacoes = vetor;
    if(l1->inicio == NULL){
        l1->inicio = novo;
        l1->qtd++;
        printf("inicio estava nulo e inclui o valor de %d na lista e ela ficou com o tamanho %d\n",n,l1->qtd);
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
        printf("inclui o valor de %d na lista e ela ficou com o tamanho %d\n",n,l1->qtd);

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

void mostrar_lista_adj(lista_adj *l1){
    if(l1->inicio == NULL){
        printf("lista vazia\n");
    }
    else{
        registro_adj *aux;
        aux = l1->inicio;
        printf("Lista: \n");
        while(aux!=NULL){
            printf("%d \n",aux->valor);
            aux = aux->prox;
        }
    }
}