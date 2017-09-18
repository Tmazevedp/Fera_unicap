#ifndef ESTRUTURAS
#define ESTRUTURAS	
typedef struct aluno {
	char matricula[10];
	char nome[100];
	char email[50];
	char telefone[11];
	int status;
	int qtd_materias;
	float media;
}TAluno;

typedef struct disciplina {
	char codigo_disciplina[10];
	char nome_disciplina[100];
	int sala;
	int qtd_vagas;
	char horario;
	int qtd_vaga_ocupadas;
	int status;
}TDisciplina;

typedef struct arvore {
	int indice;
	char matricula[11];
	struct arvore *esq;
	struct arvore *dir;
}TNo;
#endif

