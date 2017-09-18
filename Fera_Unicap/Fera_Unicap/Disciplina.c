#include<stdio.h>
#include<string.h>
#include"Types.h"
#include"Abb.h"
#include "Validacao.h"

void cadastrar_disciplina(FILE *arq, TNo **Abb,int pos_cad) {
	TDisciplina d;
	int i, flag=0,status;
	char str[6],string_nome[100];
	validar_cod_disciplina(str[6]);
	i = buscar(*Abb, str);
	strcpy(d.codigo_disciplina, str);
	if (i != 0) {
		validar_nome_disciplina(string_nome);
		strcpy(d.codigo_disciplina, string_nome);
		printf("Digite a sala onde ocorrerao as aulas:\n");
		scanf("%d", &d.sala);
		printf("Digite a quantidade total de vagas da Disciplina:\n");
		scanf("%d", &d.qtd_vagas);
		d.qtd_vaga_ocupadas = 0;
		printf("Digite o Horario da Disciplina:");
		scanf("%s", &d.horario);
		scanf("%s", &d.horario);
		fseek(arq, sizeof(TDisciplina), 2);
		status = fwrite(&d, sizeof(TDisciplina), 1, arq);
		if (status != 1) {
			printf("Erro ao gravar!\n");
			return;
		}
		else {
			printf("Cadastro salvo com sucesso!!\n");
			inserir_arvore(*Abb, str,pos_cad);
		}
	}
}

void alterar_disciplina(FILE *arq, TNo *Abb) {
	char codigo[7], valid;
	int pos, status;
	TDisciplina d;
	printf("Digite o codigo da disciplina que deseja alterar:\n");
	gets(codigo);
	pos = buscar(Abb, codigo);
	if (pos == 0) {
		printf("O codigo da disciplina nao exite!!\n");
	}
	else {
		printf("Encontramos o codigo da desciplina!! =)\n");
		fseek(arq, pos*sizeof(TDisciplina), 0);
		status = fread(&d, sizeof(TDisciplina), 1, arq);
		if (status != 1) {
			printf("Erro na leitura!\n");
		}
		else {
			printf("Deseja alterar o Nome da Disciplina?(S/N)\n");
			scanf("%c", &valid);
			scanf("%c", &valid);
			if (valid == 'S' || valid == 's') {
				printf("Digite o novo nome:\n");
				//Verificar o nome da disciplina
				fflush(stdin);
				gets(d.nome_disciplina);
			}
			printf("Deseja alterar a sala da Disciplina?(S/N)\n");
			scanf("%c", &valid);
			scanf("%c", &valid);
			if (valid == 'S' || valid == 's') {
				printf("Digite a nova sala:\n");
				fflush(stdin);
				gets(d.sala);
			}
			printf("Deseja alterar a Quantidade de vagas?(S/N)\n");
			scanf("%c", &valid);
			scanf("%c", &valid);
			if (valid == 'S' || valid == 's') {
				printf("Digite a nova Quantidade de vagas da Turma:\n");
				fflush(stdin);
				gets(d.qtd_vagas);
			}
			fseek(arq, sizeof(TDisciplina), 1);
			status = fwrite(&d, sizeof(TDisciplina), 1, arq);
			if (status != 1) {
				printf("Erro na gravacao! =(\n");
			}
			else {
				printf("Disciplina alterada com sucesso!=)\n");
			}
		}
	}
}

void buscar_disciplina(FILE *arq, TNo *Abb) {
	char codigo[7];
	int pos, status, vagas_disponivel;
	TDisciplina d;
	printf("Digite o codigo de matricula que deseja exibir:\n");
	gets(codigo);
	pos = buscar(Abb, codigo);
	if (pos == 0) {
		printf("O codigo de disciplina nao existe.\n");
	}
	else {
		fseek(arq, pos*sizeof(TDisciplina), 0);
		status = fread(&d, sizeof(TDisciplina), 1, arq);
		if (status != 1) {
			printf("Erro na leitura do arquivo.\n");
			return;
		}
		else {
			vagas_disponivel = d.qtd_vagas - d.qtd_vaga_ocupadas;
			printf("Nome: %s\nHorario da Disciplina: %s\nSala:%d\nQuantidade de vagas Disponiveis: %d\n", d.nome_disciplina, d.horario, d.sala, vagas_disponivel);
		}
	}
}

void remover_disciplina(TNo **Abb, char matric[], FILE *arq) {
	int pos, status;
	TDisciplina d;
	pos = buscar(Abb, matric);
	if (pos == 0) {
		printf("Nao exite esse aluno com esta matricula! =(\n");
	}
	else {
		fseek(arq, pos*sizeof(TDisciplina), 0);
		status = fread(&d, sizeof(TDisciplina), 1, arq);
		if (status != 1) {
			printf("Erro na leitura no arquivo! =(\n");
		}
		else {
			if (d.qtd_vaga_ocupadas == 0) {
				d.status = 1;
				status = fwrite(&d, sizeof(TDisciplina), 1, arq);
				if (status != 1) {
					printf("Erro ao escrever no arquivo\n");
				}
				else {
					printf("Disciplina removida com sucesso\n");
					remover_arvore(&Abb, matric);
				}
			}
			else {
				printf("A disciplina nao pode ser removida por causa que existe %d alunos na turma!", d.qtd_vaga_ocupadas);
			}
		}
	}
}

void manutencao_disciplina(FILE* arq) {
	FILE* arq_novo;
	TDisciplina flag;
	int status;
	arq_novo = fopen("temp.bin", "w+b");
	if (arq_novo == NULL) {
		printf("Erro ao abrir o arquivo");
		return;
	}
	else {
		fseek(arq_novo, sizeof(TDisciplina), 0);
		fseek(arq, sizeof(TDisciplina), 0);
		status = fread(&flag, sizeof(TDisciplina), 1, arq);
		while (!feof(arq) || status != 1) {
			if (flag.status == 1) {
				fwrite(&flag, sizeof(TDisciplina), 1, arq_novo);
			}
			status = fread(&flag, sizeof(TDisciplina), 1, arq);
		}
		if (!fclose(arq_novo)) {
			printf("Erro ao fechar o arquivo");
			return;
		}
		if (!fclose(arq)) {
			printf("Erro ao fechar o arquivo");
			return;
		}
		remove("matricula.bin");
		rename("temp.bin", "matricula.bin");
	}

}
