
/* 
 * File:   prim.c
 * Author: Maraiza Adami Pereira 
 *
 * Exercicio de programacao 1- Disciplina AEDII- 1°semestre de 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>


#define true 1
#define false 0


/*estrutura fila*/
typedef float TIPOCHAVE;


typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct aux{
    REGISTRO vert;
    REGISTRO dist;
    struct aux* prox;
} ELEMENTO, *PONT;

typedef struct{
    PONT inicio;
    PONT fim;
} FILA;



/*Estrutura grafo*/
typedef int bool;
typedef int TIPOPESO;


/*representa uma aresta*/
typedef struct adjacencia{
    int vertice; //VERTICE FINAL- ADJACENTE ONDE A ARESTA ESTÁ CHEGANDO
    TIPOPESO peso; //PESO
    struct adjacencia *prox;//PROXIMO NA LISTA
}ADJACENCIA; 


typedef struct vertice{
    /*outros dados*/
    bool processado;
    ADJACENCIA *cab; //CABEÇA DA LISTA DE ADJACENCIAS- ARESTAS(LIGAÇÕES)
}VERTICE;


typedef struct grafo{
    int vertices; //NUMERO DE VERTICES
    int arestas; //NUMERO DE ARESTAS
    VERTICE *adj; //ARRANJO DE VERTICES
}GRAFO; //ESTRUTURA CHAMADA GRAFO

#define MAX 1000
#define infinito INT_MAX/2;//infinito maior inteiro possivel 

int distancia[MAX]; // o array de distâncias à fonte


float prim (GRAFO *g, int orig){
    int t;
    
   FILA *f= (FILA* ) malloc (g->vertices * sizeof(FILA));//aloca mémoria para fila com o numero de vertices e  com dois registros 
   int salva [g->vertices];
   
   
    for(t = 1; t<= g->vertices ;t++) {
        distancia[t] = infinito;//declara todas a distancias como infinito 
        g->adj[t].processado = false;
    }
        distancia[orig] = 0; //Declara a primeira distancia como 0.
        g->adj[orig].processado = false;
    
    /* inserimos o primeiro elemento no topo da fila */
    push(f ,g->adj[orig].cab->vertice,g->adj[orig].cab->peso ); 
	int posicao = 0;
    
    while(true){ // rodar procurando por não visitados 
       
            int processa= -1; //cria uma variavel de controle processa
            
        
        /* verifica se existe elemento na fila*/
        
        while(f->inicio != NULL){ 
            
            REGISTRO atual = f->inicio->vert ; // receber o vertice no topo da lista
            
            
            pop(f,f->inicio->vert, f->inicio->dist);//retira o vertice da fila para ser processado
            
            
            
            if(g->adj[posicao].processado!= true){ // verifica se o atual está na lista de processados 
                processa = 1; 
		
               
            }
            
            // se não, continuamos procurando
        }
        
        if(processa == -1) break; // saiu do laço e não achou ngm
        
        g->adj[posicao].processado = true; 
       
        int i;
       
        // atualizar as distâncias
       for( i = 0;i < g->vertices ;i++){
  
            float distProx = g->adj[posicao].cab->prox->peso ;
            float distAtual = g->adj[posicao].cab->peso;
            int atual = g->adj[posicao].cab->vertice ;
           
            
            
            
            if(( distAtual > distProx) &&(g->adj[posicao+1].processado!= true)){ 
                distancia[posicao] = distProx;  
                 
                                
                 // atualizamos a distância
                push( f, atual,distancia[posicao]);// inserimos na fila de prioridade
                salva [atual];
                posicao ++;
               
            }
        }
    }
    
    float custo_arvore = 0.0;
    int j;
    for ( j = 0;j<= g->vertices;j++){
            custo_arvore = custo_arvore + distancia[j];
    }
   
   
    printf("custo da Arvore geradora minima é: %f\n", custo_arvore); 
    return custo_arvore;
}


/*estrutura de grafos*/

GRAFO *criaGrafo(int v){
    GRAFO *g = (GRAFO *)malloc (sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE * )malloc(v*sizeof(VERTICE));
    
    /*declara como NULL todos os ponteiros de adjacencias*/
    int i;
    for(i= 0; i<v; i++){
        (g->adj[i].cab) = NULL;
    }
   return (g);    
}

//cria  uma aresta no grafo com parametros o No final e o peso da aresta
ADJACENCIA *criaAdj (int v,int peso){
    
    /*aloca espaço para uma aresta- cria um nó*/
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    
    temp->vertice = v;//vertice alvo ou adjacente
    temp->peso = peso;//peso
    temp->prox = NULL;
    return (temp);
    
}
/* cria uma aresta dirigida de vi a vf*/
bool criaAresta(GRAFO* grafo, int vi, int vf, TIPOPESO p){
    
    /*testa se o grafo já foi criado*/
    if(!grafo) return (false);
    
    /*testa se o vertice final não é o primeiro, e se ele é menor que o ultimo do grafo*/
    if ((vf<0)||(vf>= grafo->vertices)){
        return false;
    }
    if ((vi<0)||(vi>= grafo->vertices)){
        return false;
    }
    
    ADJACENCIA *novo = criaAdj(vf,p);
    /*insere no começo da lista de adjacencias*/
    
    novo ->prox = grafo->adj[vi].cab; 
    grafo->adj[vi].cab = novo;
    grafo->arestas ++;
    
    return (true);
}

void imprimeGrafo(GRAFO *grafo){
    
    printf("Verticie %d. Arestas:%d. \n:" , grafo->vertices , grafo->arestas);
   
        int i;
    for(i =0; i<grafo->vertices;i++){
        printf(" v%2d:" , i);
        
        ADJACENCIA *ad = (grafo->adj[i].cab);
      
        while(ad){
            printf("v%d(%d) ", ad->vertice , ad->peso);
            
            ad = ad->prox;
        }
        printf("\n");   
    }
}

/*metodos fila */

void inicializaFila(FILA* f){
    f->inicio= NULL;
    f->fim = NULL;
}

/*funçao que inseri um elemento no fim da fila*/
bool push ( FILA* f, REGISTRO vert, REGISTRO dist){
    PONT novo = (PONT) malloc (sizeof(ELEMENTO));
    novo->vert = vert;
    novo->dist = dist;
    novo->prox = NULL;
    
    if(f->inicio ==NULL) f->inicio = novo;
    else f->fim->prox = novo;
   	 f->fim= novo;
    return true;   
}

/*exclui um elemento inicio da  fila*/
bool pop ( FILA* f, REGISTRO *vert, REGISTRO *dist){
    if(f->inicio ==NULL) return false;
    
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free ( apagar);
    
    if(f->inicio == NULL){
            f->fim = NULL;
        }
        
    return true;
}


