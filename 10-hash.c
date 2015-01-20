/*******************************
* Nome: Giovani Garuffi Rondel *
* RA: 155559                   *
* Laboratorio 10 - Hash        *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
#define TAMMAXNOME 100 /*tamanho máximo de no
me de aluno*/

typedef struct aluno{
  int ra;
  char *nome;
}Aluno;

typedef struct hash{
  Aluno al;
  struct hash *prox;
}Hash, TabelaHash;

void LeAluno(Aluno *a);
void lelinha();
Hash *CriaTabela();
int InsereTabela(TabelaHash *t, Aluno *a);
int RemoveTabela(TabelaHash *t, char buf[]);
int ConsultaTabela(TabelaHash *t, char buf[], Aluno *a);
int NumeroAlunosTabela(TabelaHash *t);
void ImprimeTabela(TabelaHash *t);
void LiberaTabela(TabelaHash *t);
unsigned int HashXOR(char nome[]);

/* SEU PROGRAMA - MAIN */
int main(int argc, char *argv[]) {
  TabelaHash *t = CriaTabela();
  char comando[100], buf[TAMMAXNOME];
  Aluno a;
  
  /*loop para ler entrada*/
  while(scanf("%s", comando) > 0){
    if(!strcmp(comando,"insere")){
      LeAluno(&a);
      printf("Insere: %06d \"%s\"\n", a.ra, a.nome);
      if(!InsereTabela(t, &a)){	/*insere aluno 'a' na tabela 't'*/
	printf("Nome repetido: \"%s\"\n", a.nome);
	free(a.nome);
      }
    }else if(!strcmp(comando, "remove")){
      scanf(" \"%[^\"]\"", buf);
      printf("Remove: \"%s\"\n", buf);
      if(!RemoveTabela(t, buf)) /*remove aluno de nome 'buf' da tabela 't'*/
	printf("Nome inexistente: \"%s\"\n", buf);
    }else if(!strcmp(comando, "consulta")){
      scanf(" \"%[^\"]\"", buf);
      printf("Consulta: \"%s\"\n", buf);
      /*consulta aluno de nome 'buf' na tabela 't', grava dados em 'a', retorna 0 se nao encontrou aluno*/
      if(ConsultaTabela(t, buf, &a))
	printf("%06d \"%s\"\n", a.ra, a.nome);
      else
	printf("Nome inexistente: \"%s\"\n", buf);
    }else if(!strcmp(comando, "imprime")){
      printf("\nImprime Tabela: %d aluno(s):\n", NumeroAlunosTabela(t)); /*Calcula numero de alunos na tabela 't'*/
      ImprimeTabela(t);
      printf("\n");
    }else if(!strcmp(comando, "sair")){ /*termina programa*/
      break;
    }else{
      printf("Comando desconhecido: `%s´\n", comando);
    }
  }
  
  LiberaTabela(t); /*libera memoria*/
  
  return 0;
}

/*le RA e nome de aluno*/
void LeAluno(Aluno *a){
  char buf[TAMMAXNOME];
  scanf("%d \"%[^\"]\"", &a->ra, buf);
  
  a->nome = malloc(strlen(buf)+1);
  strcpy(a->nome, buf);
  return;
}

/*le linha de comando*/
void lelinha(){
  int c;
  do{ c=getchar(); } while (c!='\n');
}

Hash *CriaTabela(){
  TabelaHash *t;
  int i;
  
  t = (TabelaHash*)malloc(13*sizeof(TabelaHash));
  for(i = 0; i < 13; i++){
    t[i].prox = NULL;
    t[i].al.ra = -1;
    t[i].al.nome = "a";
  }
	
  return t;
}

/* Insere o novo nome na tabela de Hashing */
int InsereTabela(TabelaHash *t, Aluno *a){
  unsigned int pos = 0;
  int  sentinela = 0, ordem;
  TabelaHash *novo, *temp;

  pos = HashXOR(a->nome);

  /* A posicao do novo noh deve iniciar apos o noh cabeça */
  novo = t[pos].prox;
  /* Aloca temp como ponteiro para a tabela */
  temp = &t[pos];
  /* Enquanto nao chega ao fim da tabela ou encontra a ordem */
  while(!sentinela && novo != NULL){
    /* Compara o nome da tabela com o q sera inserido */
    ordem = strcmp(novo->al.nome, a->nome);
    /* Caso o nome jah exista */
    if(ordem == 0)
      return 0;
    /* Caso seja encontrada a ordem alfabetica */
    if(ordem > 0)
      sentinela = 1;
    /* Continua percorrendo a tabela ate achar a posicao */
    temp = novo;
    novo = novo;
  }
  /* Aloca o novo aluno */
  novo = (Hash*)malloc(sizeof(Hash));
  novo->al = (*a);
  
  temp->prox = novo;
  
  return 1;
}

int RemoveTabela(TabelaHash *t, char buf[]){
  unsigned int pos = 0;
  Hash *p, *temp;

  /* Calcula a posicao que o nome deve estar */
  pos = HashXOR(buf);
  
  /* Procura  o nome na lista da posicao */
  for(p = &t[pos]; p->prox != NULL; p = p->prox){
    if(!strcmp(p->prox->al.nome, buf)){
      temp = p->prox;
      p->prox = temp->prox;
      free(temp);
      return 1;
    }
  }

  return 0;
}

int ConsultaTabela(TabelaHash *t, char buf[], Aluno *a){
  unsigned int pos = 0;
  Hash *temp;

  pos = HashXOR(buf);
 
  /* Compara o nome desejado com os nomes da lista */
  for(temp = &t[pos]; temp->prox != NULL; temp = temp->prox){
    if(!strcmp(temp->prox->al.nome, buf))
      (*a) = temp->prox->al;
      return 1;
  }
  
  return 0;
}

int NumeroAlunosTabela(TabelaHash *t){
  int i, cont = 0;
  Hash *temp;

  /* Conta o numeros de alunos existentes */
  for(i = 0; i < 13; i++){
    temp = &t[i];
    if(temp->prox != NULL){
      if(temp->prox->al.ra != -1){
	cont++;
	temp = temp->prox;
	while(temp->prox != NULL){
	  cont++;
	  temp = temp->prox;
	}
      }
    }
  }
  
  return cont;
}

void ImprimeTabela(TabelaHash *t){
  int i;
  Hash *temp;

  /* Procura alunos existentes e os imprime */
  for(i = 0; i < 13; i++){
    temp = &t[i];
    if(temp->prox != NULL){
      if(temp->prox->al.ra != -1){
		printf("(%d) %d \"%s\"\n", i, temp->prox->al.ra, temp->prox->al.nome);
		temp = temp->prox;
		while(temp->prox != NULL){
	  	  printf("(%d) %d \"%s\"\n", i, temp->prox->al.ra, temp->prox->al.nome);
	  	  temp = temp->prox;
		}
      }
    }
  }
}

void LiberaTabela(TabelaHash *t){
  int i;
  Hash *pont, *temp;

  /* Libera os alunos da lista */
  for(i = 0; i < 13; i++){
    pont = &t[i];
    /* Ponteiro aponta para o primeiro elemento da lista */
    pont = pont->prox;
    /* Desaloca elementos da lista */
    while(pont != NULL) {
	  temp = pont;
      pont = pont->prox;
      free(temp);
    }
  }

  /* Libera o vetor inicial de hashing */
  free(t);

}

unsigned int HashXOR(char nome[]){
  unsigned int pos = 0;
  int i = 0;

  /* Calcula a posicao pelo metodo XOR */
  while(nome[i] != '\0'){
    pos ^= nome[i];	
    i++;
  }
  /* Calcula o resto da divisao por 13 */
  pos = pos%13;
  
  return pos;
}
