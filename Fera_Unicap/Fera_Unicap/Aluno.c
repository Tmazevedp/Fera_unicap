#include <stdio.h>
#include <string.h>
#include "Types.h"
#include "Abb.h"
#include "Aluno.h"
#include<math.h>
#include<conio.h>
#include<ctype.h>

void cadastrar(FILE *arq, TNo **Abb,int pos) {
	TAluno c;
	int status, retorno;
	char teste[10];
	printf("Digite a Matricula do Aluno:\n");
	fgets(teste,9,stdin);fflush(stdin);
	retorno = buscar(*Abb, teste);
	if (retorno == 0) {
		//FALTA VERIFICAR O DIGITO VERIFICADOR DE MATRICULA
		printf("Digite o nome:\n");
		fgets(c.nome,100,arq);
		//FALTA VALIDAR O NOME
		c.media = 0;
		printf("Digite o seu email:\n");
		gets(c.email);
		// FALTA VALIDAR O EMAIL
		printf("Digite o seu Telefone:\n");
		gets(c.telefone);
		// FALTA VALIDAR O TELEFONE
		c.qtd_materias = 0;
	}
	fseek(arq, sizeof(TAluno), 2);
	status = fwrite(&c, sizeof(TAluno), 1, arq);
	if (status == 1) {
		printf("Aluno cadastrado com Sucesso!!\n");
		inserir_arvore(*Abb, c.matricula); 
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

void buscar_aluno(FILE *arq, TNo *Abb) {
	int pos, status;
	TAluno c;
	char matricula[10];
	printf("Digite a matricula:\n");
	gets(matricula);
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

void remover_cadastro(TNo *Abb, FILE *arq) {  // 0 -> Ativo | 1 -> Desativo
	int pos, status;
	TAluno c;
	char matric[10];
	printf("Digite a matricula:\n");
	gets(matric);
	pos = buscar(Abb, matric);
	if (pos == 0) {
		printf("Nao existe esse aluno com esta matricula!=( \n");
	}
	else {
		fseek(arq, pos*sizeof(TAluno), 0);
		status = fread(&c, sizeof(TAluno), 1, arq);
		if (status != 1) {
			printf("Erro na leitura\n");
		}
		else {
			if (c.qtd_materias != 0) {
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
					remover_arvore(&Abb, matric); // Remover um aluno da arvore
				}
			}
		}
	}
}

void manutencao_aluno(FILE *arq){
	FILE* arq_novo;
	TAluno flag;
	int status;
	arq_novo = fopen("temo.bin","w+b");
	if (arq_novo == NULL) {
		printd("Erro ao abrir o arquivo!\n");
	}
	else {
		fseek(arq_novo, sizeof(TAluno), 0);
		fseek(arq, sizeof(TAluno), 0);
		status = fread(&flag, sizeof(TAluno), 1, arq);
		while (!feof(arq) || status != 1) {
			if (flag.status == 1) {
				fwrite(&flag, sizeof(TAluno), 1, arq_novo);
			}
			status = fread(&flag, sizeof(TAluno), 1, arq);
		}
		if (!fclose(arq_novo)) {
			printf("Erro ao fechar o arquivo");
			return;
		}
		if (!fclose(arq)) {
			printf("Erro ao fechar o arquivo");
			return;
		}
		remove("aluno.bin");
		rename("temp.bin", "aluno.bin");
	}

}