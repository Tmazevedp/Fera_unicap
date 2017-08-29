#include <stdio.h>
#include <string.h>
#include "Types.h"
#include "Abb.h"

void cadastrar(FILE *arq, TNo **Abb) {
	TAluno c;
	int status;
	printf("Digite a Matricula do Aluno:\n");
	gets(c.matricula);
	//FALTA VERIFICAR O DIGITO VERIFICADOR DE MATRICULA
	inserir_arvore(*Abb, c.matricula);
	printf("Digite o nome:\n");
	gets(c.nome);
	//FALTA VALIDAR O NOME
	c.media = 0;
	printf("Digite o seu email:\n");
	gets(c.email);
	// FALTA VALIDAR O EMAIL
	printf("Digite o seu Telefone:\n");
	gets(c.telefone);
	// FALTA VALIDAR O TELEFONE
	c.qtd_materias = 0;
	if (arq == NULL) {
		fseek(arq, sizeof(TAluno), 0);
	}
	else {
		fseek(arq, sizeof(TAluno), 2);
	}
	status = fwrite(&c, sizeof(TAluno), 1, arq);
	if (status == 1) {
		printf("Aluno cadastrado com Sucesso!!\n");
	}
	else {
		printf("Erro ao cadastrar o aluno no Arquivo! =( \n");
	}
}

void alterar_aluno(FILE *arq, TNo *Abb) {
	TAluno c;
	int ind, status;
	char matr[10], valid;
	printf("Digite a matricula:\n");
	gets(matr);
	ind = buscar(Abb, matr);
	if (ind != 0) {
		printf("Encontramos o Aluno com a matricula %s\n", matr);
		fseek(arq, ind*sizeof(TAluno), 0);
		status = fread(&c, sizeof(TAluno), 1, arq);
		if (status != 1) {
			printf("Erro de leitura!\n");
		}
		else {
			printf("Deseja alterar o Nome?(S/N)\n");
			scanf("%c", &valid);
			scanf("%c", &valid);
			if (valid == 'S' || valid == 's') {
				printf("Digite o novo nome:\n");
				fflush(stdin);
				gets(c.nome);
			}
			printf("Deseja alterar o E-mail?(S/N)\n");
			scanf("%c", &valid);
			scanf("%c", &valid);
			if (valid == 'S' || valid == 's') {
				printf("Digite o novo E-mail:\n");
				fflush(stdin);
				gets(c.email);
				// FALTA VERIFICAR O E-MAIL
			}
			printf("Deseja alterar o Telefone?(S/N)\n");
			scanf("%c", &valid);
			scanf("%c", &valid);
			if (valid == 'S' || valid == 's') {
				printf("Digite o novo Telefone:\n");
				fflush(stdin);
				gets(c.telefone);
			}
			printf("Deseja alterar a Media?(S/N)\n");
			scanf("%c", &valid);
			scanf("%c", &valid);
			if (valid == 'S' || valid == 's') {
				printf("Digite a sua nova Media:\n");
				fflush(stdin);
				gets(c.media);
			}
			fseek(arq, -sizeof(TAluno), 1);
			status = fwrite(&c, sizeof(TAluno), 1, arq);
			if (status != 1) {
				printf("Erro de gravacao!\n");
			}
			else {
				printf("Aluno alterado com sucesso! =)\n");
			}
		}

	}
	else {
		printf("Nao encontramos o Aluno! =(\n");
	}
}

void buscar_aluno(char matricula[], FILE *arq, TNo *Abb) {
	int pos, status;
	TAluno c;
	pos = buscar(Abb, matricula);
	if (pos == 0) {
		printf("Nao existe esse Aluno com esta matricula");
	}
	else {
		fseek(arq, pos*sizeof(TAluno), 0);
		status = fread(&c, sizeof(TAluno), 1, arq);
		if (status != 1) {
			printf("Erro na leitura do registro\n");
			return;
		}
		else {
			printf("Registro lido com sucesso!!\n");
			printf("Nome: %s\nE-mail: %s\nTelefone: %s\nMedia: %s\nQuantidade de Disciplinas: %s", c.nome, c.email, c.telefone, c.media, c.qtd_materias);
		}
	}
}

void remover_cadastro(TNo *Abb, char matric[],FILE *arq) {  // 0 -> Ativo | 1 -> Desativo
	int pos,status;
	TAluno c;
	pos = busca(Abb, matric);
	if (pos == 0) {
		printf("Nao existe esse aluco com esta matricula!=( \n");
	}
	else {
		fseek(arq, pos*sizeof(TAluno), 0);
		status = fread(&c, sizeof(TAluno), 1, arq);
		if (status != 1) {
			printf("Erro na leitura\n");
		}
		else {
			if(c.qtd_materias != 0){
				printf("O aluno nao pode ser removido, devido que se encontra em alguma materia\n");
				return;
			}
			else {
				c.status = 1;
				fseek(arq, -sizeof(TAluno), 1);
				status = fwrite(&c, sizeof(TAluno), 1, arq);
				if (status != 1) {
					printf("Erro em Remover o Aluno!\n");
				}
				else {
					printf("Aluno removido com sucesso!\n");
				}
			}
		}
	}
}