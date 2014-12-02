/****************************************** 
* Nome: Giovani Garuffi Rondel            *
* RA: 155559                              *
* Laboratorio 09 - Árvores 2-3 (inserção) *
*******************************************/

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */

/*arvore23_no_t - define tipo nOH de uma arvore 2-3*/
typedef struct arvore23_no {
    /* valor das chaves do no, se existirem */
    int chave1, chave2;
    /* numero de chaves existentes no noh */
    int nchaves;		
   	/*ponteiros para os nohs filhos*/
    struct arvore23_no *filho1, *filho2, *filho3;
    /*ponteiro para o noh pai*/
    struct arvore23_no *pai;
} arvore23_t;

arvore23_t *arvore23_aloca();
void arvore23_libera(arvore23_t *t);
void arvore23_insere(arvore23_t **t, int chave);
int arvore23_busca(arvore23_t *t, int chave);
void arvore23_imprime(arvore23_t *t);


/* SEU PROGRAMA - MAIN */
int main(){
    arvore23_t *arv;
    int i,N,chave;
    char comando[9];

    /* Cria arvore 2-3 */
    arv = arvore23_aloca();
    
    /*le quantidade de entradas*/
    scanf("%d\n",&N);
    for(i = 0; i < N; i++) {
        /*le instrucao*/
	    scanf("%s", comando);
	        if (!strcmp(comando,"inserir")){
		        scanf("%d", &chave);
 		        arvore23_insere(&arv, chave);
	        }else if (!strcmp(comando,"buscar")){
		        scanf("%d", &chave);
 		        if (!arvore23_busca(arv, chave))
			        printf(":(\n");
		        else
			        printf(":)\n");		
        	}else if (!strcmp(comando,"imprimir")){
		        arvore23_imprime(arv);
        		printf("\n");
	        }
    } 
    /* libera memoria */
    arvore23_libera(arv);

    return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */
/* Cria arvore 2-3. */
arvore23_t *arvore23_aloca(){
    return NULL;
}

/* Libera arvore 2-3. */
void arvore23_libera(arvore23_t *t)
{
    if(t!=NULL){
	arvore23_libera(t->filho1);
	arvore23_libera(t->filho2);
	arvore23_libera(t->filho3);
	free(t); t=NULL;
    }
}

/* Insere chave na arvore 2-3. Nao insere se chave ja existir na arvore */
void arvore23_insere(arvore23_t **t, int chave){

    /*se t for vazia*/
    if(*t==NULL){
    	(*t) = (arvore23_t *) malloc(sizeof(arvore23_t));
    	(*t)->nchaves = 1;
	    (*t)->chave1 = chave;
    	(*t)->pai = (*t)->filho1 = (*t)->filho2 = (*t)->filho3 = NULL;
	    return;
    }
    /*se chave ja existe na arvore*/
    if (arvore23_busca((*t), chave)) 
	    return;

/*-------------------------------
Completar aqui
---------------------------------*/

}

/* Busca chave na arvore 2-3. Retorna 1 se encontrar ou 0 se nao encontrar */
int arvore23_busca(arvore23_t *t, int chave){

/*-------------------------------
Completar aqui
---------------------------------*/

    return 0;
}

/* Imprime arvore 2-3. */
void arvore23_imprime(arvore23_t *t){
    
    if(t!=NULL){
	    printf("( ");
    	if (t->nchaves == 1){
	    	arvore23_imprime(t->filho1);
	    	printf("%d ",t->chave1);
		    arvore23_imprime(t->filho2);
   	    }
    	else /*t->nchaves == 2*/{
		    arvore23_imprime(t->filho1);
		    printf("%d ",t->chave1);
		    arvore23_imprime(t->filho2);
		    printf("%d ",t->chave2);
		    arvore23_imprime(t->filho3);
	    }
	    printf(") ");
    }
}
