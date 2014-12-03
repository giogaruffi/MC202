/***************************************** 
* Nome: Giovani Garuffi Rondel           *
* RA: 155559                             *
* Laboratorio 08 - Menor Ancestral Comum *
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
typedef struct lista_arvore{
	int info;
	struct lista_arvore *pai;
	struct lista_arvore *prox_arv;
} Lista, Arvore, Noh;

typedef enum{false, true} boolean;


Lista *InicializaLista();
void InsereInicio(Noh *inicio, int dado);
void ImprimeLista(Lista *inicio);
void LiberaLista(Lista *l);
boolean BuscaNoh(Lista *l, int dado);

void link(Lista *floresta);
void cut(Lista *floresta);
void lca(Lista *floresta);

/* SEU PROGRAMA - MAIN */
int main() {
	int N, M, i;
	char operacao[4];
	Lista *floresta;

	/* Le o numero de arvores e a quatidade de operacoes */
	scanf("%d %d", &N, &M);

	/* Criacao da floresta de elementos */
	floresta = InicializaLista();
	for(i = N; i > 0; i--){
		InsereInicio(floresta, i);
	}
	/* Leitura das operacoes e realizacao dessas */
	for(i = 0; i < M; i++){
		scanf("%s", operacao);
		/* Caso a operacao seja link, a realize */
		if(!strcmp("link", operacao))
			link(floresta);
		if(!strcmp("cut", operacao))
			cut(floresta);
		if(!strcmp("lca", operacao))
			lca(floresta);
	}

	/* Libera memória alocada */
	LiberaLista(floresta);

	return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */
Lista *InicializaLista(){
	Lista *inicio;

	inicio = (Noh*)malloc(sizeof(Noh));

	inicio->info = -1;
	inicio->prox_arv = NULL;
	inicio->pai = NULL;

	return inicio;
}

void InsereInicio(Noh *inicio, int dado) {
	Arvore *temp;
	
	temp = (Arvore*)malloc(sizeof(Arvore));
	temp->info = dado;
	temp->pai = NULL;
	temp->prox_arv = inicio->prox_arv;
	inicio->prox_arv = temp;
}

void LiberaLista(Lista *l) {
	Noh *q;
  
	while(l != NULL) {
		q = l;
    	l = l->prox_arv;
    	free(q);
  	}
}

boolean BuscaNoh(Lista *l, int dado){
	Lista *temp;

	for(temp = l; temp != NULL; temp = temp->pai){
		if(temp->info == dado)
			return true;
	}
	return false;
}

void link(Lista *floresta){
	int filho, pai;
	Arvore *noh_filho, *noh_pai;

	/* Entra os valores dos nohs que devem ser linkados */
	scanf("%d %d", &filho, &pai);

	/* Procura o noh com o conteudo igual ao filho */
	for(noh_filho = floresta->prox_arv; noh_filho != NULL &&
		noh_filho->info != filho; noh_filho = noh_filho->prox_arv);
	/* Procura o noh com o conteudo igual ao pai */
	for(noh_pai = floresta->prox_arv; noh_pai != NULL &&
		noh_pai->info != pai; noh_pai = noh_pai->prox_arv);
	/* Caso algum dos dois nohs desejados nao exista, retorne */
	if(noh_pai == NULL || noh_filho == NULL)
		return;

	noh_filho->pai = noh_pai;
}

void cut(Lista *floresta){
	int filho;
	Arvore *noh_filho;

	/* Entra com o valor do noh a ser cortado */
	scanf("%d", &filho);
	/* Procura o noh com o conteudo igual ao filho */
	for(noh_filho = floresta->prox_arv; noh_filho != NULL &&
		noh_filho->info != filho; noh_filho = noh_filho->prox_arv);
	/* Caso o noh a ser cortado nao exista, retorne */
	if(noh_filho == NULL)
		return;

	noh_filho->pai = NULL;
}

void lca(Lista *floresta){
	int A, B;
	Arvore *nohA, *nohB;

	scanf("%d %d", &A, &B);

	/* Procura o noh com o conteudo igual ao primeiro vertice */
	for(nohA = floresta->prox_arv; nohA != NULL &&
		nohA->info != A; nohA = nohA->prox_arv);
	/* Procura o noh com o conteudo igual ao segundo vertice */
	for(nohB = floresta->prox_arv; nohB != NULL &&
		nohB->info != B; nohB = nohB->prox_arv);
	/* Caso algum dos dois nohs desejados nao exista, retorne */
	if(nohA == NULL || nohB == NULL)
		return;	
	/* Percorre os ancestrais de A e procura o primeiro antepassado em comum com B*/
	while(nohA != NULL){
		if(BuscaNoh(nohB, nohA->info)){
			printf("%d\n", nohA->info);
			return;
		}
		nohA = nohA->pai;
	}
}
