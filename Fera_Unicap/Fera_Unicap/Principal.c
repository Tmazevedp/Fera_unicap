#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aluno.h"
#include "Disciplina.h"
#include "Abb.h"
#include "Types.h"

FILE * criar_arquivo(char nome[]) {
	FILE *arq;
	arq = fopen(nome, "r+b");
	if (arq == NULL) {
		arq = fopen(nome, "w+b");
	}
	return arq;
}

int main() {
	FILE *arq_aluno, *arq_matricula, *arq_disciplina;
	char nome_arq_aluno[] = "aluno.bin", nome_arq_matricula[] = "matricula.bin", nome_arq_disciplina[] = "disciplina.bin";
	int op, i, op_aluno, pos_aluno,pos_matricula, op_disciplina;
	TNo *Abb_aluno=NULL,*Abb_disciplina=NULL;
	char cod_disciplina_remover[10];
	arq_aluno = criar_arquivo(nome_arq_aluno);
	arq_disciplina = criar_arquivo(nome_arq_disciplina);
	arq_matricula = criar_arquivo(nome_arq_matricula);
	system("date /t");
	if (arq_aluno == NULL || arq_disciplina == NULL || arq_matricula == NULL) {
		printf("Erro ao tentar criar/abrir arquivo\n");
	}
	else {
		pos_aluno = iniciar_arvore(Abb_aluno, arq_aluno);
		pos_matricula = iniciar_arvore(Abb_disciplina, arq_disciplina);
		do {
			printf("\t\t\t");
			for (i = 0; i <= 34; i++) {
				printf("#");
			}
			printf("\n");
			printf("\t\t\t#\t1 - Modulo de Aluno       #\n");
			printf("\t\t\t#\t2 - Modulo Disciplinas    #\n");
			printf("\t\t\t#\t3 - Modulo Matricula      #\n");
			printf("\t\t\t#\t4 - Sair                  #\n");
			printf("\t\t\t");
			for (i = 0; i <= 34; i++) {
				printf("#");
			}
			printf("\n");
			printf("->");
			system("color 3");
			scanf("%d", &op);
			fflush(stdin);
			if (op == 1) {
				printf("\t\t\tModulo de Aluno\t\t\t");
				printf("\n1 - Cadastrar um aluno:\n2 - Alterar um aluno\n3 - Listar um aluno\n");
				scanf("%d", &op_aluno);
				fflush(stdin);
				switch (op_aluno) {
				case 1: cadastrar(arq_aluno, &Abb_aluno,pos_aluno);
					break;
				case 2: alterar_aluno(arq_aluno, &Abb_aluno);
					break;
				case 3: buscar_aluno(arq_aluno, Abb_aluno);
					break;
				case 4: remover_cadastro(arq_aluno, &Abb_aluno);
					break;
				}
			}
			else if (op == 2) {
				printf("\t\t\tModulo de Disciplina\t\t\t");
				printf("\n1 - Cadastrar um aluno:\n2 - Alterar um aluno\n3 - Listar um aluno\n");
				scanf("%d", &op_disciplina);
				switch (op_disciplina) {
				case 1: cadastrar_disciplina(arq_disciplina, &Abb_disciplina,pos_matricula);
					break;
				case 2: alterar_disciplina(arq_disciplina, &Abb_aluno);
					break;
				case 3: buscar_disciplina(arq_disciplina, Abb_disciplina);
					break;
				case 4: printf("Digite o codigo da disciplina");
					gets(cod_disciplina_remover);
					remover_disciplina(&Abb_disciplina,cod_disciplina_remover,arq_disciplina);
					break;
				}
			}
		} while (op != 4);
	}
	manutencao_aluno(arq_aluno);
	manutencao_disciplina(arq_disciplina);
	return 0;
}