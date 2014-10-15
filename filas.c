/******************************************* 
* Nome: Giovani Garuffi Rondel             *
* RA: 155559                               *
* Laboratorio 03 - Linha Divisora de Águas *
********************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */ 
typedef enum{false, true} boolean;
/* Struct para cada ponto da matriz */
typedef struct Ponto{
	int altura;
	int x, y;
	char bacia;
} Ponto, Matriz;
/* Struct da fila */
typedef struct NoFila {
	Ponto info;
	struct NoFila *prox;
} Fila, *ApRegFila, RegFila;

/* FUNCOES DA TAD */
Fila *fila_cria();
void fila_insere(Fila **p, Ponto x);
Ponto fila_retira(Fila **p);
boolean fila_vazia(Fila *p);
void fila_libera(Fila *p);
/* Outras funcoes */
Matriz** matriz_cria(int H, int W);
void matriz_libera(Matriz **m, int H);
void dissipador_encontra(Matriz **m, int H, int W, Fila *Ord[MAX]);
void pontos_rotula(Matriz **m, Fila *Ord[MAX]);

/* SEU PROGRAMA - MAIN */
int main() {
	int H, W, i, j;
	Ponto **matriz;
	Fila *FilaOrd[MAX];

	/* Leitura do tamanho da matriz */
	scanf("%d %d", &H, &W);
	/* Criar fila ordenada (tamanho 100) */
	for(i = 0; i < MAX; i++){
		FilaOrd[i] = fila_cria();
	}
	/* Criar e alocar mapa como matriz */
	matriz = matriz_cria(H, W);
	/* Encontrar pontos dissipadores */
	dissipador_encontra(matriz,H,W, FilaOrd);
	/* Rotular pontos vizinhos aos dissipadores */
	pontos_rotula(matriz,FilaOrd);
	/* Imprimir matriz rotulada */
	for(i=1;i<=H;i++){
		for(j=1;j<=W;j++){
			printf("%c ", matriz[i][j].bacia);
		}
		printf("\n");
	}
	/* Liberar matriz */
	matriz_libera(matriz, H);

	return 0;
} 

/* Funcao que cria uma matriz que representa o mapa de bacias */
Matriz** matriz_cria(int H, int W){
	int i, j;
	Ponto **m;

	/* Alocar a matriz de acordo com as dimensoes do mapa */
	m = (Ponto**)malloc((H+2)*sizeof(Ponto));
	for(i = 0; i < H+2; i++){
		m[i] = (Ponto*)malloc((W+2)*sizeof(Ponto));
	}
	/* Zerar bordas */
	for(i = 0; i < H+2; i++){
		m[i][0].altura = 101;
		m[i][W+1].altura = 101;
	}
	for(j = 0; j < W+2; j++){
		m[0][j].altura = 101;
		m[H+1][j].altura = 101;
	}

	/* Atribuir na matriz os valores do mapa, assim como suas coordenadas */
	for(i = 1; i <= H; i++){
		for(j = 1; j <= W; j++){
			scanf("%d", &m[i][j].altura);
			m[i][j].x = j;
			m[i][j].y = i;
			m[i][j].bacia = '0';
		}
	}

	/* Retorna matriz que representa o mapa */
	return m;
}

/* Funcao que encontra os pontos dissipadores */
void dissipador_encontra(Matriz **m, int H, int W, Fila *Ord[MAX]){
	int i, j;
	char bacia = 'a';
	
	/* Procura pontos com menor valor com relacao aos vizinhos (dissipador) */
	for(i = 1; i <= H; i++){
		for(j = 1; j <= W; j++){
			if(m[i][j].altura <= m[i-1][j].altura && m[i][j].altura <= m[i][j-1].altura
			&& m[i][j].altura <= m[i+1][j].altura && m[i][j].altura <= m[i][j+1].altura){
				m[i][j].bacia = bacia;
				/* Muda a letra da bacia */
				bacia += 1;
				/* Insere no vetor de filas no indice da altura */
				fila_insere(&Ord[m[i][j].altura], m[i][j]);
			}
		}
	}
}

/* Funcao que rotula os pontos vizinhos aos dissipadores */
void pontos_rotula(Matriz **m, Fila *Ord[MAX]){
	int i;
	Ponto p; 

	for(i = 0; i < MAX; i++){
		/* Enquanto a fila nao esta vazia, retira o ponto e rotula seus vizinhos */
		while(Ord[i]->info.altura != -1){
			p = fila_retira(&Ord[i]);
			if(m[p.y - 1][p.x].bacia == '0'){
				m[p.y - 1][p.x].bacia = p.bacia;
				fila_insere(&Ord[m[p.y - 1][p.x].altura], m[p.y - 1][p.x]);
			}
			if(m[p.y][p.x - 1].bacia == '0'){
				m[p.y][p.x - 1].bacia = p.bacia;
				fila_insere(&Ord[m[p.y][p.x - 1].altura], m[p.y][p.x - 1]);
			}
			if(m[p.y][p.x + 1].bacia == '0'){
				m[p.y][p.x + 1].bacia = p.bacia;
				fila_insere(&Ord[m[p.y][p.x + 1].altura], m[p.y][p.x + 1]);
			}
			if(m[p.y + 1][p.x].bacia == '0'){
				m[p.y + 1][p.x].bacia = p.bacia;
				fila_insere(&Ord[m[p.y + 1][p.x].altura], m[p.y + 1][p.x]);
			}
		}
	}

}

/* Funcao que libera a matriz de pontos */
void matriz_libera(Matriz **m, int H){
	int i;

	for(i = 0; i < H; i++){
		free(m[i]);
	}
	free(m);
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */
Fila *fila_cria() {
	Fila *p = (Fila*)malloc(sizeof(RegFila));
	
	p->prox = p;
	p->info.altura = -1;
	
	return p;
}

void fila_insere(Fila **p, Ponto x) {
	ApRegFila q;
	
	q = (RegFila*)malloc(sizeof(RegFila));
	q->info = x;
	q->prox = (*p)->prox;
	(*p)->prox = q;
	*p = q;
}

Ponto fila_retira(Fila **p) {
	ApRegFila q, r; 
	Ponto x;

	x.altura = -1;
	
	q = (*p)->prox;
	if(*p == q){
		printf("Fila vazia\n");
		return x;
	}
	else{
		r = q->prox;
		x = r->info;
		q->prox = r->prox;
		if (r == *p){ /* ultimo elemento removido? */
			*p = q;
		}
		free(r);
		return x;
	}

	return x;
}

boolean fila_vazia(Fila *p) {
	return(p == p->prox);
}

void fila_libera(Fila *p) {
	ApRegFila q, r;
	
	q = p->prox;
	while(q != p){
		r = q->prox;
		free (q);
	q = r;
	}
	free (p);
}
