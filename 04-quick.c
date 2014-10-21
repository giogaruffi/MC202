/******************************************
* Nome: Giovani Garuffi Rondel            *
* RA: 155559                              *
* Laboratorio 04 - Quicksort aleatorizado *
*******************************************/

#include <stdio.h>
#include <stdlib.h>

/* Cabecalho da funcao TAD */
double quick(int A[], int pivo);
/* Funcoes auxiliares ao programa */
int separa_menores(int A[], int tamanho, int pivo, int *L0);
int separa_maiores(int A[], int tamanho, int pivo, int *L1);
double custo_indiv(int A[], int tamanho, int ind_pivo, int pivo);

/* SEU PROGRAMA - MAIN */
int main() {
	int *vet, tamanho,i;
	double media;

	/* Le as informacoes de entrada e monta o vetor inicial */
	scanf("%d", &tamanho);
	vet = (int*)malloc(tamanho*sizeof(int));
	for(i = 0; i < tamanho; i++)
		scanf("%d", &vet[i]);
	/* Calcula a media das somas dos pesos */
	media = (quick(vet,tamanho)/ tamanho);
	/* Imprime a media final */
	printf("%.10f\n", media);
	/* Desaloca a memoria do vetor */
	free(vet);

return 0;
}

/* Implementacao da funcao TAD */
double quick(int A[], int tamanho){
	int *L0, tam_L0, *L1, tam_L1, ind_pivo;
	double total = 0.0000000000;

	/* Caso base 1: menos de 2 elementos, nao ha oq ordenar */
	if(tamanho < 2){
		return 0;
	}
	/* Caso base 2: somente 2 elementos, verifica se ha oq 
	 ordenar e da peso 1 caso necessario */
	if(tamanho == 2){
		if(A[1] > A[0])
			return 0;
		return 1;
	}
	/* Cria os vetores auxiliares de elementos menores e maiores */
	else{
		L0 = (int*)malloc((tamanho - 1)*sizeof(int));
		L1 = (int*)malloc((tamanho - 1)*sizeof(int));
		/* Para todos os possiveis pivos, calcula seus pesos */
		for(ind_pivo = 0;ind_pivo < tamanho; ind_pivo++){
			tam_L0 = separa_menores(A, tamanho, A[ind_pivo], L0);
			tam_L1 = separa_maiores(A, tamanho, A[ind_pivo], L1);
			total += custo_indiv(A, tamanho, ind_pivo, A[ind_pivo]) 
			 + quick(L0, tam_L0) + quick(L1, tam_L1);
		}
		/* Desaloca a memoria dos vetores auxiliares */
		free(L0);
		free(L1);
	}
	/* Retorna o valor somado de todos os pesos */
	return total;
}

/* Implementacao das funcoes auxiliares */
int separa_menores(int A[], int tamanho, int pivo, int *L0){
	int i, j = 0;

	/* Para cada elemento menor no vetor original, copia-lo
	 no vetor de numeros menores */
	for(i=0;i<tamanho;i++){
		if(A[i] < pivo){
			L0[j] = A[i];
			j++;
		}
	}
	/* Retorna tamanho do vetor de numeros menores */
	return j;
}

int separa_maiores(int A[], int tamanho, int pivo, int *L1){
	int i, j = 0;


	/* Para cada elemento maior no vetor original, copia-lo
	 no vetor de numeros maiores */
	for(i=0;i<tamanho;i++){
		if(A[i] > pivo){
			L1[j] = A[i];
			j++;
		}
	}
	/* Retorna tamanho do vetor de numeros maiores */
	return j;
}

/* Calculo do custo individual do pivo */
double custo_indiv(int A[], int tamanho, int ind_pivo, int pivo){
	int i;
	double cont_esq = 0, cont_dir = 0;

	/* Conta o numero de elementos maiores que o pivo a sua esquerda */
	for(i=0;i<ind_pivo;i++){
		if(A[i] > pivo){
			cont_esq++;
		}
	}
	/* Conta o numero de elementos menores que o pivo a sua direita */
	for(i=ind_pivo+1;i<tamanho;i++){
		if(A[i] < pivo){
			cont_dir++;
		}
	}
	/* Retorna o valor da soma dos contadores */
	return (cont_esq + cont_dir);
}
