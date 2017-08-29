#include <stdio.h>
#include "Aluno.h"

FILE * criar_arquivo(char nome[]) {
	FILE *arq;
	arq = fopen(nome, "r+b");
	if (arq == NULL) {
		arq = fopen(nome, "w+b");
	}
	return arq;
}

int main() {
	FILE *arq_aluno,*arq_matricula,*arq_disciplina;
	char nome_arq_aluno[] = "aluno.bin",nome_arq_matricula[]= "matricula.bin",nome_arq_disciplina[] = "disciplina.bin";
	int op,i;
	arq_aluno = criar_arquivo(nome_arq_aluno);
	arq_disciplina = criar_arquivo(nome_arq_disciplina);
	arq_matricula = criar_arquivo(nome_arq_matricula);
	if (arq_aluno == NULL || arq_disciplina == NULL || arq_matricula == NULL) {
		printf("Erro ao tentar criar/abrir arquivo\n");
	}
	else{
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
			system("color 0A");
			scanf("%d", &op);
			if (op == 1) {
				
			}
		} while (op != 4);
	}
	return 0;
}