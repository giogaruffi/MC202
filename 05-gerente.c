/************************************* 
* Nome: Giovani Garuffi Rondel       *
* RA: 155559                         *
* Laboratorio 05 - Gerente do Espaço *
**************************************/

/* NAO FOI POSSIVEL CONCLUIR ESSE LABORATORIO */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
typedef enum{false, true} boolean;

typedef struct lista {
	char arquivo[11];
	int memoria;
	boolean ocupado;
	struct lista *prox;
} Lista, No, InicioLista, *ApNoLista;

/* FUNCOES DA TAD */
void InicializaLista(Lista *inicio, int memoria_vazia);
void InsereProx(No *lista, int dado, char arquivo[]);
void RemoveProx(Lista *l);
boolean ListaVazia(Lista *l);
void ImprimeLista(Lista *inicio, int memoria_disco, int memoria_vazia);
void LiberaLista(Lista *l);

int ler_memoria();
int interpretar_memoria(char mem_char[]);
void operacao_otimiza(Lista *disco);

/* SEU PROGRAMA - MAIN */
int main() {
	int op_tot = -1, mem_total, i, mem_arquivo, erro = 0, inserido = 0;
	char operacao[8], arquivo[11], memoria[7], arq_tamanho[7];
	Lista *disco_memoria, *aux_disco;

	/* Entrada da quantidade de operacoes */
	scanf("%d", &op_tot);
	while(op_tot != 0){

		erro = 0;

		/* Entrada da memoria total do disco */
		scanf("%s", memoria);
		printf("memoria %s\n", memoria);
		mem_total = interpretar_memoria(memoria);
		
		/* Criacao da lista de alocacao de arquivos */
		disco_memoria = (Lista*)malloc(sizeof(Lista));
		InicializaLista(disco_memoria, mem_total);

		/* Execucao das operacoes */
		for(i=0; i < op_tot; i++){
			/* Ponteiro auxiliar para manipulacao da lista */
			aux_disco = disco_memoria;
			
			scanf("%s", operacao);
			scanf("%s", arquivo);
			printf("%s em %s ", operacao, arquivo);

			/* Operacao insere */
			if(!strcmp("insere", operacao)){

				/* Entrada do tamanho do arquivo */
				scanf("%s", arq_tamanho);
				printf("de tamanho %s ", arq_tamanho);
				mem_arquivo = interpretar_memoria(arq_tamanho);
				printf("que eh igual a %d\n", mem_arquivo);

				/* Tentativa de inserir arquivo em espacos vazios entre nos */
				inserido = 0;
				/* Percorrer ate o fim porque senao inserir agora eh preciso inserir no fim */
				while(aux_disco->prox != NULL){

					if((aux_disco->prox->memoria >= mem_arquivo) && 
					!(aux_disco->prox->ocupado) && !inserido){
						
						InsereProx(aux_disco, mem_arquivo, arquivo);
						disco_memoria->memoria -= mem_arquivo;
						inserido = 1;
						printf("inserindo entre nohs %d e inserido vale %d\n", mem_arquivo, inserido);
			
					}
					aux_disco = aux_disco->prox;
				}
				/* Caso nao seja encontrado espaco entre arquivos e ainda exista 
				 * espaco na memoria, inserir no fim da lista */
				if(disco_memoria->memoria - mem_arquivo >= 0 && !inserido){
					InsereProx(aux_disco, mem_arquivo, arquivo);
					disco_memoria->memoria -= mem_arquivo;
					inserido = 1;
					printf("inserindo no fim %d e inserido vale %d\n", mem_arquivo, inserido);
				}
				/* Caso nao seja possivel inserir em nenhuma posicao, otimizar memoria */
				if(!inserido){
					/* Auxiliar volta para o inicio da lista */
					aux_disco = disco_memoria;
					/* Procura espacos vazios entre os arquivos */
					while(aux_disco->prox != NULL){
						if(!aux_disco->prox->ocupado){
							/* Retira o noh vazio para otimizar a memoria */
							operacao_otimiza(aux_disco);
							disco_memoria->memoria += mem_arquivo;
						}
						aux_disco = aux_disco->prox;
					}
					/* Testa se eh possivel inserir apos a otimizacao */
					if(disco_memoria->memoria - mem_arquivo >= 0){
						InsereProx(aux_disco, mem_arquivo, arquivo);
						disco_memoria->memoria -= mem_arquivo;
						printf("inserindo pos otimizacao %d\n", mem_arquivo);
					/* Caso nao seja possivel inserir, acusa erro */
					}else{
						printf("entrou em %d\n", i+1);
						erro = 1;
					}
				}
			}
			/* Operacao remove */
			else if(!strcmp("remove", operacao)){
				/* Procura arquivo na lista para remocao */
				while(strcmp(arquivo, aux_disco->prox->arquivo) && aux_disco->prox != NULL){
					aux_disco = aux_disco->prox;
				}
				if(aux_disco->prox != NULL && aux_disco->prox->ocupado){
					/* Muda o noh para desocupado e passa a memoria desse para o total*/
					RemoveProx(aux_disco);
					disco_memoria->memoria += mem_arquivo;
					printf("removendo %d\n", mem_arquivo);
				}
			}
			/* Operacao otimiza */
			else if(!strcmp("otimiza", operacao)){
				/* Procura espacos vazios entre os arquivos */
				while(aux_disco->prox != NULL){
					if(!aux_disco->prox->ocupado){
						/* Retira o noh vazio para otimizar a memoria */
						operacao_otimiza(aux_disco);
						disco_memoria->memoria += mem_arquivo;
					}
					aux_disco = aux_disco->prox;	
				}
			}
		}
		if(!erro){
			ImprimeLista(aux_disco, mem_total, disco_memoria->memoria);
		}else{
			printf("ERRO: disco cheio\n");
		}
		LiberaLista(disco_memoria);
		
		scanf("%d", &op_tot);
	}

	return 0;
}

int interpretar_memoria(char mem_char[]){
	int mem_int = 0, i = 0, j = 0;
	char mem_tipo;

	while(mem_char[i] >= '0' && mem_char[i] <= '9'){
		i++;
	}
	mem_tipo = mem_char[i--];
	while(i >= 0){
		mem_int += ((mem_char[j] - '0')*pow(10,i));
		i--;
		j++;
	}
	if(mem_tipo == 'M'){
		mem_int *= 1024;
		return mem_int;
	}
	if(mem_tipo == 'G'){
		return mem_int *= 1024*1024;
	}

	return mem_int;
}
/* Necessario passar o primeiro no do disco para "passar para o fim"
 * a memoria livre entre dois arquivos */
void operacao_otimiza(Lista *disco){
	No *temp;

	temp = disco->prox;
	disco->prox = temp->prox;
	
	free(temp);
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */ 
void InicializaLista(Lista *inicio, int memoria_vazia) {

	inicio->memoria = memoria_vazia;
	inicio->ocupado = true;
	inicio->prox = NULL;

}

void InsereProx(No *lista, int dado, char arquivo[]) {
	Lista *temp;

	temp = (Lista*)malloc(sizeof(Lista));

	temp->memoria = dado;
	temp->ocupado = true;
	strcpy(temp->arquivo, arquivo);
	temp->prox = lista->prox;
	lista->prox = temp;
}

void RemoveProx(Lista *l) {
	
	l->prox->ocupado = false;

}

boolean ListaVazia(Lista *l){
	return(l->prox == NULL);
}

void LiberaLista(Lista *l) {
	Lista *p;

	for(p = l ; p != NULL; p = p-> prox){
		free(p);
	}
}

void ImprimeLista(Lista *inicio, int memoria_disco, int memoria_vazia) {
	Lista *temp;
	double memoria_bloco[8], memoria_dividida;
	int i;

	for(i=0;i<8;i++){
		memoria_bloco[i] = memoria_disco/8;
	}
	memoria_dividida = memoria_disco/8;
	
	temp = inicio->prox;
	i = 0;
	while(temp != NULL){
		if(temp->ocupado){
			if((memoria_bloco[i] - temp->memoria) < 0){
				temp->memoria -= memoria_bloco[i];
				memoria_bloco[i] = 0;
				i++;
			} else if ((memoria_bloco[i] - temp->memoria) == 0){
				memoria_bloco[i] = 0;
				temp = temp->prox;
				i++;
			} else {
				memoria_bloco[i] -= temp->memoria;
				temp = temp->prox;
			}
		} else {
			temp = temp->prox;
		}
	}
	for(i=0; i < 8; i++){
		if(memoria_bloco[i]/memoria_dividida > 0.70 && 
			memoria_bloco[i]/memoria_dividida <= 1.0){
			printf("[ ]");
		} else if (memoria_bloco[i]/memoria_dividida > 0.25 && 
			memoria_bloco[i]/memoria_dividida <= 0.75){
			printf("[-]");
		} else {
			printf("[#]");
		}
	}

	for(temp = inicio->prox; temp != NULL; temp = temp->prox){
		if(temp->ocupado){
			printf("noh %s memoria %d\n", temp->arquivo, temp->memoria);
		}
	}
	printf("\n");
}
