/************************************************
* Nome: Giovani Garuffi Rondel                  *
* RA: 155559                                    *
* Laboratorio 01 - O problema do acesso à lista * 
*************************************************/

#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
typedef struct lista {
	int info;
	struct lista *prox;
	int contagem;
} Lista;

/* FUNCOES TAD */
void InicializaLista(Lista *inicio);
void InsereInicio(Lista *inicio, int dado);
void ImprimeLista(Lista *inicio);
void LiberaLista(Lista *l);
/* Outras funcoes */
int MTF(Lista *l, int operacao);
int TR(Lista *l, int operacao);
int FC(Lista *l, int operacao);

/* SEU PROGRAMA - MAIN */
int main() {
	int N, R, aux, soma_MTF = 0, soma_TR = 0, soma_FC = 0, operacao;
	Lista Arq_MTF, Arq_TR, Arq_FC;

	/* Leitura dos elementos da lista */
	scanf("%d", &N);
	/* Cria a lista de arquivos */
	InicializaLista(&Arq_MTF);
	InicializaLista(&Arq_TR);
	InicializaLista(&Arq_FC);
	/* Enumera os arquivos de 1 ate N */
	for(aux = N; aux > 0; aux--){
		InsereInicio(&Arq_MTF, aux);
		InsereInicio(&Arq_TR, aux);	
		InsereInicio(&Arq_FC, aux);
	}

	/* Leitura da quantidade de operacoes */
	scanf("%d", &R);

	/* Realizacao das diferentes operacoes e calculo do peso de cada uma */
	for (aux = 0; aux < R; aux++){
		scanf("%d", &operacao);
		/* Caso a operacao seja maior que o valor maximo ou invalida, somar o peso maximo */
		if(operacao < 1 || operacao > N){
			soma_MTF += N;
			soma_TR += N;
			soma_FC += N;
		}
		else{
			soma_MTF += MTF(&Arq_MTF, operacao);
			soma_TR += TR(&Arq_TR, operacao);
			soma_FC += FC(&Arq_FC, operacao);
		}
	/*	ImprimeLista(&Arq_FC);*/
	}
	
	/*Liberar listas ao fim do programa*/
	LiberaLista(&Arq_MTF);
	LiberaLista(&Arq_TR);
	LiberaLista(&Arq_FC);
	
	/* Impressao dos pesos finais calculados */
	printf("%d %d %d\n", soma_MTF, soma_TR, soma_FC);
	
 return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */ 
void InicializaLista(Lista *inicio) {
	inicio->info = -1;
	inicio->prox = NULL;
}

void InsereInicio(Lista *inicio, int dado) {
	Lista *temp;
	
	temp = (Lista*)malloc(sizeof(Lista));
	temp->info = dado;
	temp->prox = inicio->prox;
	inicio->prox = temp;
	inicio->contagem = 0;

}

void LiberaLista(Lista *l) {
	Lista *p;

	for(p = l->prox ; p != NULL; p = p-> prox){
		free(p);
	}
}

void ImprimeLista(Lista *inicio) {
	Lista *temp;

	for(temp = inicio->prox; temp != NULL; temp = temp->prox)
		printf("%d ", temp->info);
	printf("\n");
}

/* Implementacao das outras funcoes */
int MTF(Lista *l, int operacao){
	int peso = 1;
	Lista *p, *ant;

	/* Retorna 1 se o numero procurado ja eh o primeiro */
	if(l->prox->info == operacao)
		return 1;
	/* Busca o numero desejado e sua posicao, assim como a de seu anterior */
	for(ant = l, p = l->prox; p->info != operacao && p != NULL; p = p->prox, ant = ant->prox){
		peso++;
	}

	/* Insere na primeira posicao o elemento desejado e o tira de sua posicao anterior */
	ant->prox = p->prox;
	InsereInicio(l, operacao);

	/* Retorna o peso calculado */
	return peso;
}

int TR(Lista *l, int operacao){
	int peso = 1;
	Lista *p;

	/* Retorna 1 se o numero procurado ja eh o primeiro */
	if(l->prox->info == operacao)
		return 1;
	/* Busca o numero desejado e sua posicao */
	for(p = l->prox; p->prox->info != operacao && p->prox != NULL; p = p->prox){
		peso++;
	}
	/* Como o loop anterior para uma posicao antes da desejada, o peso precisa ser acrescido em 1 */
	peso++;
	/* Realiza a troca entre o desejado e seu anterior */
	p->prox->info = p->info;
	p->info = operacao;
	/* Como a operacao de substituicao considera um acrescimo no peso */
	peso++;

	/* Retorna o peso calculado */
	return peso;
}

int FC(Lista *l, int operacao){
	int peso = 1;
	Lista *p, *ant, *inicio, *aux;

	/* Cria ponteiros auxiliares para o inicio da lista e para o noh cabeca */
	aux = l;
	p = l->prox;
	inicio = l->prox;
	/* Busca o numero desejado e sua posicao */
	while(p != NULL && p->info != operacao){
		ant = p;
		p = p->prox;
		peso++;
	}
	/* Checa se o elemento procurado eh o primeiro da lista */
	if(p->info == inicio->info){
		p->contagem++;
		return 1;
	}
	/* Checa se o elemento procurado foi encontrado e ordena */
	else if(p->info == operacao){
		p->contagem++;
		/* Procura o elemento com o numero igual ou menor que a operacao atual */
		while(p->contagem < inicio->contagem){
			aux = inicio;
			inicio = inicio->prox;
		}
		if(p != inicio){
			/* Ordena a lista e retorna o peso total da operacao */
			ant->prox = p->prox;
			p->prox = inicio;
			aux->prox = p;
		}
	}

	/* Retorna o peso calculado */
	return peso;
}
