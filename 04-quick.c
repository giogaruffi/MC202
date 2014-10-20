/******************************************
* Nome: Giovani Garuffi Rondel *
* RA: 155559 *
* Laboratorio 04 - Quicksort aleatorizado *
*******************************************/

#include <stdio.h>
#include <stdlib.h>

double quick(int A[], int pivo);
int separa_menores(int A[], int tamanho, int pivo, int *L0);
int separa_maiores(int A[], int tamanho, int pivo, int *L1);
double custo_indiv(int A[], int tamanho, int ind_pivo, int pivo);

/* SEU PROGRAMA - MAIN */
int main() {
	int *vet, tamanho,i;
	double media;

	scanf("%d", &tamanho);
	vet = (int*)malloc(tamanho*sizeof(int));
	for(i = 0; i < tamanho; i++)
		scanf("%d", &vet[i]);

	media = quick(vet,tamanho);

	printf("%.10f\n", media);

	free(vet);

return 0;
}

double quick(int A[], int tamanho){
	int *L0, tam_L0, *L1, tam_L1, ind_pivo;
	double total = 0.0000000000;

	if(tamanho < 2){
		return 0;
	}
	if(tamanho == 2){
		if(A[1] > A[0])
			return 0;
		return 1;
	}
	else{
		L0 = (int*)malloc((tamanho - 1)*sizeof(int));
		L1 = (int*)malloc((tamanho - 1)*sizeof(int));
		for(ind_pivo = 0;ind_pivo < tamanho; ind_pivo++){
			tam_L0 = separa_menores(A, tamanho, A[ind_pivo], L0);
			tam_L1 = separa_maiores(A, tamanho, A[ind_pivo], L1);
			total += custo_indiv(A, tamanho, ind_pivo, A[ind_pivo]) + quick(L0, tam_L0) + quick(L1, tam_L1);
		}
		free(L0);
		free(L1);
	}

	return (total/tamanho);
}

int separa_menores(int A[], int tamanho, int pivo, int *L0){
	int i, j = 0;

	for(i=0;i<tamanho;i++){
		if(A[i] < pivo){
			L0[j] = A[i];
			j++;
		}
	}
	return j;
}

int separa_maiores(int A[], int tamanho, int pivo, int *L1){
	int i, j = 0;

	for(i=0;i<tamanho;i++){
		if(A[i] > pivo){
			L1[j] = A[i];
			j++;
		}
	}
	return j;
}

double custo_indiv(int A[], int tamanho, int ind_pivo, int pivo){
	int i;
	double cont_esq = 0, cont_dir = 0;

	for(i=0;i<ind_pivo;i++){
		if(A[i] > pivo){
			cont_esq++;
		}
	}
	for(i=ind_pivo+1;i<tamanho;i++){
		if(A[i] < pivo){
			cont_dir++;
		}
	}

	return (cont_esq + cont_dir);
}
