/********************************* 
* Nome: Giovani Garuffi Rondel   *
* RA: 155559                     *
* Laboratorio 06 - Pré, In e Pós *
**********************************/

#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
typedef struct No {
	char info;
	struct No *esq, *dir;
}ArvBin, NoArvBin;

ArvBin *criaVazia();
void CriaNo(ArvBin **p, char x);
void AdicionaEsq(ArvBin *p, char x);
void AdicionaDir(ArvBin *p, char x);
void InsereEsq(ArvBin *p, int x);
void InsereDir(ArvBin *p, int x);
void LiberaArv(ArvBin *p);
void PreOrdem(ArvBin *p);
void PosOrdem(ArvBin *p);
void InOrdem(ArvBin *p);

/* Funcao auxiliar */
void InterpretaArv(ArvBin *p, char nohs_pre[], char nohs_in[], int tamanho);

/* SEU PROGRAMA - MAIN */
int main() {
	int num_casos, num_nohs, i;
	char *nohs_pre, *nohs_in;
	ArvBin *arvore;

	/* Entra com o numero de casos de teste */
	scanf("%d", &num_casos);
	
	for(i = 0;i < num_casos;i++){
		/* Entra com a quantidade de nohs da arvore */
		scanf("%d", &num_nohs);
		/* Cria os vetores que armazenam a sequencia em InOrdem e PreOrdem */
		nohs_pre = (char*)malloc((num_nohs+1)*sizeof(char));
		nohs_in = (char*)malloc((num_nohs+1)*sizeof(char));
		scanf("%s", nohs_pre);
		scanf("%s", nohs_in);
		/* Cria a arvore e a interpreta */
		arvore = criaVazia();		
		InterpretaArv(arvore, nohs_pre, nohs_in, num_nohs);
		/* Imprime o \n ao fim da impressao da arvore */
		printf("\n");
		/* Libera a arvore e os vetores */
		LiberaArv(arvore);
		free(nohs_pre);
		free(nohs_in);
	}

	return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */
ArvBin *criaVazia(){
	return NULL;
}

void CriaNo(ArvBin **p, char x){
	
	*p = (NoArvBin*)malloc(sizeof(NoArvBin));
	(*p)->info = x;
	(*p)->esq = NULL;
	(*p)->dir = NULL;
}

void AdicionaEsq(ArvBin *p, char x){
	NoArvBin *q;
	
	if(p != NULL){
		CriaNo(&q, x);
		p->esq = q;
	}
}

void AdicionaDir(ArvBin *p, char x){
	NoArvBin *q;
	
	if(p != NULL){
		CriaNo(&q, x);
		p->dir = q;
	}
}

void InsereEsq(ArvBin *p, int x){
	NoArvBin *q;

	q = (NoArvBin*)malloc(sizeof(NoArvBin));
	
	q->info = x;
	q->esq = p->esq;
	q->dir = NULL;
	p->esq = q;
}

void InsereDir(ArvBin *p, int x){
	NoArvBin *q;

	q = (NoArvBin*)malloc(sizeof(NoArvBin));
	
	q->info = x;
	q->dir = p->dir;
	q->esq = NULL;
	p->dir = q;
}

void LiberaArv(ArvBin *p){

    if(p != NULL){
	    LiberaArv(p->esq); 
    	LiberaArv(p->dir);
    	free(p);
	}
}

void PreOrdem(ArvBin *p){
	
	if(p != NULL){
		printf("%c",p->info);
		PreOrdem(p->esq);
		PreOrdem(p->dir);
	}
}

void PosOrdem(ArvBin *p){

	if(p != NULL){
		PosOrdem(p->esq);
		PosOrdem(p->dir);
		printf ("%c", p->info);
	}
}

void InOrdem(ArvBin *p){

	if (p != NULL){
		InOrdem(p->esq);
		printf("%c", p->info);
		InOrdem(p->dir);
	}
}

/* Funcao que interpreta os vetores em PreOrdem e InOrdem, 
 * cria e imprime uma arvore em Pos Ordem */
void InterpretaArv(ArvBin *p, char nohs_pre[], char nohs_in[], int tamanho){
	char *pre_esq, *in_esq, *pre_dir, *in_dir;
	int tam_esq = 0, i, j;

	/* Caso base, tamanho dos vetores vazio, entao se trata de um NULL */
	if(tamanho == 0){
		return;
	}

	/* Primeiro noh da PreOrdem eh a raiz da arvore/subarvore */
	CriaNo(&p,nohs_pre[0]);

	/* Calcula a posicao da raiz no vetor em InOrdem */
	while(nohs_in[tam_esq] != nohs_pre[0]){
		tam_esq++;
	}
	/* O valor calculado eh o tamanho dos novos vetores a esquerda */
	pre_esq = (char*)malloc(tam_esq*sizeof(char));
	in_esq = (char*)malloc(tam_esq*sizeof(char));
	/* O tamanho dos vetores da direita eh o valor total 
	 * menos a raiz menos o tamanho da esquerda */
	pre_dir = (char*)malloc((tamanho - 1 - tam_esq)*sizeof(char));
	in_dir = (char*)malloc((tamanho - 1 - tam_esq)*sizeof(char));
	/* Preenche os novos vetores com os valores correspondentes */
	for(i = 1, j = 0; i <= tam_esq && j < tam_esq; i++, j++){
		pre_esq[j] = nohs_pre[i];
		in_esq[j] = nohs_in[j];
	}
	for(i = tam_esq + 1, j = 0; i < tamanho; i++, j++){
		pre_dir[j] = nohs_pre[i];
		in_dir[j] = nohs_in[i];
	}

	/* Chama recursivamente para os nohs filhos */
	InterpretaArv(p->esq, pre_esq, in_esq, tam_esq);
	InterpretaArv(p->dir, pre_dir, in_dir, tamanho - 1 - tam_esq);

	/* Imprime o noh em PosOrdem */
	printf("%c",p->info);

	/* Libera a memoria alocada */
	free(pre_esq);
	free(in_esq);
	free(pre_dir);
	free(in_dir);
	free(p);
}
