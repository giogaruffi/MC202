/****************************************** 
* Nome: Giovani Garuffi Rondel            *
* RA: 155559                              *
* Laboratorio 07 - Cobertura de Conjuntos *
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include "balloc.h"

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
typedef enum{false, true} boolean;

typedef struct Arvore{
	int chave;
	struct Arvore *esq, *dir, *pai;
}ArvBin, NoArvBin;

typedef struct lista{
	int info;
	int tamanho;
	struct lista *prox;
	ArvBin *arv;
} Lista, Noh, InicioLista, *ApNohLista;

/* TAD LISTA */
Noh *InicializaLista();
void InsereNoh(Noh **inicio, int dado);
boolean ListaVazia(Lista *l);
void ImprimeLista(Lista *inicio);
void LiberaLista(Lista *l);
void RemoveProx(Lista **l);
/* TAD ABB */
ArvBin *CriaABB();
ArvBin *Insere(int k, ArvBin **p, ArvBin **pai);
ArvBin *Remove(int k, ArvBin **p);
ArvBin *Busca(ArvBin *p, int k);
ArvBin *Troca(NoArvBin **r, NoArvBin **g);
ArvBin *LiberaArv(ArvBin *p);
void RotEsq(NoArvBin *p, NoArvBin **q);
void RotDir(NoArvBin *p, NoArvBin **q);
void Afunilamento(NoArvBin *p);
void ImprimeABB(NoArvBin *p);

void bprint(char *who, int where, void *ptr, size_t size) {
/* Funcao auxiliar que imprime dados sobre bloco de memoria nao
   liberado. */
  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
} /* bprint */

NoArvBin *Guloso(NoArvBin *U, Lista *S);
void Uniao(NoArvBin **p, NoArvBin *q);
void Diferenca(NoArvBin **p, NoArvBin *q);
int CalculaTamanho(ArvBin *p);

/* SEU PROGRAMA - MAIN */
int main() {
    int num_U, num_S, i;
    char lixo;
	ArvBin *arvore;
	Lista *subcnjts;

	/* Entra com o tamanho do conjunto e 
	 * com o numero de subconjuntos */
	scanf("%d %d%c", &num_U, &num_S, &lixo);

	/* Inicializa a arvore do tipo abb */
	arvore = CriaABB();
	/* Inicializa a lista de subconjuntos */
	subcnjts = InicializaLista();
	/* Cria arvore Universo */
	for (i = 1; i <= num_U; i++){
		arvore = Insere(i, &arvore, &arvore->pai);
		Afunilamento(arvore);
	}
	/* Cria floresta de subconjuntos */
	for(i = 0; i < num_S; i++){
	  InsereNoh(&subcnjts, i+1);
	}
	/* Executa o algoritmo guloso */
	arvore = Guloso(arvore, subcnjts);

	/* Libera as memorias alocadas */
	LiberaLista(subcnjts);
	arvore = LiberaArv(arvore);

	bapply(bprint);

	return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */ 
Noh *InicializaLista() {
	Noh *p;

	p = (Lista*)MALLOC(sizeof(Lista));

	p->info = -1;
	p->tamanho = -1;
	p->prox = NULL;
	p->arv = CriaABB();

	return p;
}

void InsereNoh(Noh **inicio, int dado) {
  Lista *novo;
	int valor;
	char lixo;
	
	novo = InicializaLista();
	
	novo->info = dado;
     	novo->prox = (*inicio)->prox;
        (*inicio)->prox = novo;

	/* Aloca os valores da arvore e afunila */
	scanf("s ");
	do{
		scanf("%d%c", &valor, &lixo);
		novo->arv = Insere(valor, &novo->arv, &novo->arv->pai);
		Afunilamento(novo->arv);
	}while(lixo != '\n');
	/* Calcula o numero de elementos presentes no subconjunto */
	novo->tamanho = CalculaTamanho(novo->arv);

}

int CalculaTamanho(ArvBin *p){
  int tam = 1;

  if(p == NULL)
    return 0;
  
  /* Calcula o tamanho da arvore */
  tam += CalculaTamanho(p->esq);
  tam += CalculaTamanho(p->dir);

  return tam;
}

void RemoveProx(Lista **l) {
	Noh *temp;

	temp = (*l)->prox;
	(*l)->prox = temp->prox;
	FREE(temp);
}

void LiberaLista(Lista *l) {
	Noh *q;
  
	while(l != NULL) {
		q = l;
		q->arv = LiberaArv(q->arv);
    	l = l->prox;
    	FREE(q);
  	}
}

ArvBin *CriaABB(){
	ArvBin *p;

	p = (NoArvBin*)MALLOC(sizeof(NoArvBin));
	p->chave = -1;
	p->esq = NULL;
	p->dir = NULL;
	p->pai = NULL;

	return p;
}

ArvBin *Busca(ArvBin *p, int k){
	
	if(p == NULL || p->chave == k)
		return p;
	if(p->chave > k)
		return Busca(p->esq, k);
	else
		return Busca(p->dir, k);
}

/* Funcao que insere novo noh na arvore */
ArvBin *Insere(int k, ArvBin **p, ArvBin **pai){

	/* Caso ache o local para alocar o noh, o cria */
	if(*p == NULL || (*p)->chave == -1){
	  *p = (NoArvBin*)MALLOC(sizeof(NoArvBin));
		(*p)->chave = k;
		(*p)->esq = NULL;
		(*p)->dir = NULL;
		if((*p)->pai != NULL)
		  (*p)->pai = *pai;
		return *p;
	}
	/* Caso ja exista o noh a ser alocado, retorna */
	if(k == (*p)->chave)
	  return NULL;
	/* Procura a posicao de alocacao */
	else if(k < (*p)->chave)
		Insere(k, &(*p)->esq, p);
	else
		Insere(k, &(*p)->dir, p);
	/* Retorna o endereco do noh recem alocado */
	return *p;
}

ArvBin *Remove(int k, ArvBin **p){
  NoArvBin *g, *pai = NULL;

  	/* Caso nao exista o noh a ser retirado, retorna */
	if (*p == NULL) 
	  return NULL;
	/* Procura o noh a ser retirado */
	else if(k < (*p)->chave)
		Remove(k, &(*p)->esq);
	else if (k > (*p)->chave)
		Remove(k, &(*p)->dir);
	/* Remove o noh */
	else {
		g = *p;
		if (g->dir == NULL){
		  pai = (*p)->pai;
			*p = g->esq;
			if(*p != NULL)
			  (*p)->pai = g->pai;
		}
		else if (g->esq == NULL){
		  pai = (*p)->pai;
		  *p = g->dir;
		  if(*p != NULL)
		    (*p)->pai = g->pai;
		}
		else
			pai = Troca(&g->esq, &g);
		if(pai != g)
		 	FREE(g);
		return pai;
	}
	/* Retorna o noh pai do removido */
	return pai;
}

ArvBin *Troca(NoArvBin **r, NoArvBin **g){
  NoArvBin *pai;

	if((*r)->dir != NULL) 
		Troca (&(*r)->dir, g);
	else {
		(*g)->chave = (*r)->chave;
		pai = (*r)->pai;
		*r = (*r)->esq;
		if(*r != NULL)
		  (*r)->pai = pai;
		if(pai != NULL)
		  return pai;
	}
	return *g;
}

void RotEsq(NoArvBin *p, NoArvBin **q) {

	p->dir = (*q)->esq;
	if((*q)->esq != NULL)
	  (*q)->esq->pai = p;
	(*q)->esq = p;
	(*q)->pai = p->pai;
	p->pai = *q;
}

void RotDir(NoArvBin *p, NoArvBin **q){
	
	p->esq = (*q)->dir;
	if((*q)->dir != NULL)
	  (*q)->dir->pai = p;
	(*q)->dir = p;
	(*q)->pai = p->pai;
	p->pai = *q;
}

void Afunilamento(NoArvBin *R){
	NoArvBin *Q, *P;

	if(R == NULL)
	  return;
	/* Enquanto R nao eh raiz */
	while(R->pai != NULL){
	  /* Alocacao dos nohs pai e avo */
	  if(R != NULL)
	    Q = R->pai;
	  if(R->pai != NULL)
	    P = Q->pai;
		/* Se o ascendente de R eh a raiz */
		if(Q->pai == NULL){
			/* Afunilamento simples */
			if(R == Q->esq)
				RotDir(Q, &R);
			else
				RotEsq(Q, &R);
		/* Afunilamento homogeneo: gire Q ao redor de P 
		 * e depois R ao redor de Q */
		}else if(R == Q->esq && Q == P->esq){
			RotDir(P, &Q);
			RotDir(Q, &R);
		}else if(R == Q->dir && Q == P->dir){
			RotEsq(P, &Q);
			RotEsq(Q, &R);
		/* Afunilamento heterogeneo: gire R ao redor de Q 
		 * e depois ao redor de P */
		}else{
			if(R == Q->esq){
				RotDir(Q, &R);
				RotEsq(P, &R);
			}else{
				RotEsq(Q, &R);
				RotDir(P, &R);
			}
		}
	}
}

ArvBin *LiberaArv(ArvBin *p){

    if(p != NULL){
		LiberaArv(p->esq); 
		LiberaArv(p->dir);
		FREE(p);
	}
	return NULL;
}

/* Remove os elementos em comum entre as duas arvores */
void Diferenca(NoArvBin **p, NoArvBin *q){
	ArvBin *teste;

	if(q == NULL)
    	return;
    /* Testa se eh possivel remover o noh da arvore */
	teste = Remove(q->chave, p);
	/* Caso seja, afunila a arvore resultante */
	if(teste != NULL){
    	(*p) = teste;
    	Afunilamento(*p);
  	}

  	/* Realiza a diferenca para os outros elementos da arvore */
	Diferenca(p, q->esq);
  	Diferenca(p, q->dir);

}

/* Adiciona os elementos de uma arvore na outra */
void Uniao(NoArvBin **p, NoArvBin *q){
  ArvBin *teste;

    if(q == NULL)  
      return;
    /* Testa se eh possivel inserir o noh da arvore */
    teste = Insere(q->chave, p, &(*p)->pai);
    /* Caso seja, afunila a arvore resultante */
    if(teste != NULL){
      *p = teste;
      Afunilamento(*p);
    }

  	/* Realiza a uniao para os outros elementos da arvore */
    Uniao(p, q->esq);
    Uniao(p, q->dir);
}

NoArvBin *Guloso(NoArvBin *U, Lista *S){
	NoArvBin *R, *M;
	Lista *p;
	int maior = 0, posicao, *saida, i = 0, j;

	/* Cria R (arvore resposta final) */
	R = CriaABB();

	/* Cria vetor resposta de elementos */
	saida = (int*)MALLOC(sizeof(int));

	/* Enquanto U diferente de vazio */
	while(U != NULL && S->prox != NULL){
		maior = 0;
		/* M = subconjunto de S que cobre a maior quantidade de elementos em U */
		for(p = S->prox; p != NULL; p = p->prox){
			if(p->tamanho > maior){
				maior = p->tamanho;
				posicao = p->info;
				M = p->arv;
			}
			else if(p->tamanho == maior){
			  if(p->info > posicao){
			    posicao = p->info;
			    M = p->arv;
			  }
			}
		}
		/* Aloca na saida o elemento a ser somado */
		saida[i] = posicao;
		i++;
		/* Remove M de S */
		for(p = S; p->prox->info != posicao && p->prox->prox != NULL; p = p->prox);
		RemoveProx(&p);
		/* Para cada subconjunto C de S, C = C \ M */
		for(p = S->prox; p != NULL; p = p->prox){
		  Diferenca(&p->arv, M);
		  p->tamanho = CalculaTamanho(p->arv);
		}
		/* U = U \ M */
		Diferenca(&U, M);
		/* R = R U {M} */
        Uniao(&R, M);
	}

	/* Printa a saida, tanto para o caso correto quanto para o incorreto */
	if(U == NULL){
	  for(j = 0; j < i-1; j++)
	    printf("S%d U ", saida[j]);
	  printf("S%d :)\n", saida[j]);
	}
	if(S->prox == NULL && U != NULL)
	  printf(":(\n");

	FREE(saida);

	return R;
}
