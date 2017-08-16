#ifndef ESTRUTURAS
#define ETRUTURAS	
typedef struct aluno {
	char matricula[10];
	char nome[100];
	char email[50];
	char telefone[11];
	int status;
	int qtd_materias;
	float media;
}TAluno;

typedef struct arvore {
	int indice;
	char matricula[11];
	struct arvore *esq;
	struct arvore *dir;
}TNo;
#endif

