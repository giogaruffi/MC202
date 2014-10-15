/********************************************* 
* Nome: Giovani Garuffi Rondel	             *
* RA: 155559                                 *
* Laboratorio 02 - Matrioshkas Generalizadas *
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
typedef struct PilhaMatrioshkas {
	int tamanho;
	int contador;
	struct PilhaMatrioshkas *prox;
} Pilha, InicioPilha;

/* FUNCOES DA TAD */
void pilha_cria(Pilha *inicio);
void pilha_push(Pilha *p, int v);
void pilha_pop(Pilha *p);
int pilha_vazia(Pilha *p);
void pilha_libera(Pilha *p);
void pilha_imprime(Pilha *topo);
/* Outras funcoes */
int Matrioshkas(Pilha *pilha_matrioskhas, int numero);
int MatrioshkasPush(Pilha *matrioshka, int valor);
int MatrioshkasPop(Pilha *matrioshka, int valor);
/* SEU PROGRAMA - MAIN */
int main() {
	int numero;
	Pilha pilha_matrioskhas;
	/* Leitura da quantidade de elementos da possivel Matrioshka */
	while(scanf("%d", &numero) && numero != 0){
		/* Criacao da pilha de Matrioshkas */
		pilha_cria(&pilha_matrioskhas);
		/* Confirmacao se a pilha eh Matrioshka ou nao */
		if(Matrioshkas(&pilha_matrioskhas,numero)){
			printf(":-) Matrioshka!\n");
		}
		else{
			printf(":-( Tente novamente.\n");
		}
		/* Liberacao da pilha */
		pilha_libera(&pilha_matrioskhas);
	}

	return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */
void pilha_cria(Pilha *inicio){
	inicio->tamanho = -1;
	inicio->prox = NULL;
} 

void pilha_push(Pilha *p, int v){
	Pilha *q;

	q = (Pilha*)malloc(sizeof(Pilha));
	q->tamanho = v;
	q->contador = 0;
	q->prox = p->prox;
	p->prox = q;
}

void pilha_pop(Pilha *p){
	Pilha *q;
	
	q = p->prox;
	p->prox = p->prox->prox;
	free(q); 
}

int pilha_vazia(Pilha *p){
	return (p->prox == NULL);
}

void pilha_libera(Pilha *p) {
	Pilha *l;
	
	for(l = p->prox ; l != NULL; l = l-> prox){
		free(l);
	}
}

void pilha_imprime(Pilha *p) {
	Pilha *l;

	for(l = p->prox; l != NULL; l = l->prox){
		printf("%d\n", l->tamanho);
	}

}

/* Implementacao de outras funcoes*/
int Matrioshkas(Pilha *matrioshka, int numero){
	int valor, i, sentinela = 1;

	/* Leitura dos dados da pilha */	
	for (i = 0; i < numero; i++){
		scanf("%d", &valor);
		/* Variavel sentinela verifica se ainda ha a possibilidade
		 * da pilha formar uma Matrioshka */
		if(sentinela){
			/* No caso de valor negativo, eh uma ramificacao */
			if(valor < 0){
				sentinela = MatrioshkasPush(matrioshka, valor);
			}
			/* Valor positivo indica fechamento da Matrioshka */
			else{
				sentinela = MatrioshkasPop(matrioshka, valor);
			}
		}
	}

	/* Caso não seja Matrioshka */
	if(!sentinela){
		return 0;
	}
	/* Caso seja Matrioshka */
	return 1;
}

/* Funcao de abertura de uma nova Matrioshka */
int MatrioshkasPush(Pilha *matrioshka, int valor){

	/* Caso nao seja o fim da pilha ou o módulo da externa menor que o da interna,
	 * Matrioshka invalida */
	if(matrioshka->prox != NULL && valor < matrioshka->prox->tamanho){
		return 0;
	}
	/* Entra na pilha */
	pilha_push(matrioshka, valor);
	/* Caso nao seja a penultima */
	if(matrioshka->prox->prox != NULL){
		/* Soma o tamanho das Matrioshkas internas */
		matrioshka->prox->prox->contador += matrioshka->prox->tamanho;
		/* Soma das internas eh maior ou igual o tamanho da externa,
		 * Matrioshka invalida */
		if(matrioshka->prox->prox->contador <= matrioshka->prox->prox->tamanho){
			return 0;
		}
	}
	/* Processo realizado sem cair nos casos invalidos */
	return 1;
}

/* Funcao de fechamento de uma Matrioshka */
int MatrioshkasPop(Pilha *matrioshka, int valor){

	/* Caso sobre uma Matrioshka aberta, ou o valor nao eh o certo para fechar,
	 * Matrioshka invalida */
	if(matrioshka->prox == NULL || matrioshka->prox->tamanho != (-1)*(valor)){
		return 0;
	}
	/* Retira as Matrioshkas validas */
	pilha_pop(matrioshka);

	/* Processo realizado sem cair nos casos invali+dos */
	return 1;
}
