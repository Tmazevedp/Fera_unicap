#include<stdio.h>
#include<string.h>
#include "Types.h"


void inserir_arvore(TNo **abb, char matric[], int pos) {

	if (*abb == NULL) {
		*abb = (TNo*)malloc(sizeof(TNo));
		strcpy((*abb)->matricula, matric);
		(*abb)->dir = NULL;
		(*abb)->esq = NULL;
		(*abb)->indice=pos;
	}
	else {
		if (strcmp((*abb)->matricula, matric) == 0) {
			printf("Ja existe este codigo! Digite Novamente:");
			return;
		}
		else {
			if (strcmp(matric, (*abb)->matricula) < 0) {
				inserir_arvore((*abb)->esq, matric,pos);
			}
			else {
				inserir_arvore((*abb)->dir, matric,pos);
			}
		}
	}
}

int buscar(TNo *abb, char matric[]) {
	if (abb == NULL) {
		return 0;
	}
	else {
		if (strcmp(abb->matricula, matric) == 0) {
			return abb->indice;
		}
		else {
			if (strcmp(matric, abb->matricula) < 0) {
				return buscar_aluno(abb->esq, matric);
			}
			else {
				return buscar_aluno(abb->dir, matric);
			}
		}
	}
}

TNo *maior(TNo **raiz) {
	TNo *aux;
	aux = *raiz;
	if (aux->dir == NULL) {
		*raiz = (*raiz)->esq;
		return aux;
	}
	else {
		return maior(&((*raiz)->dir));
	}
}

void remover_no(TNo **raiz) {
	TNo *pos;
	pos = *raiz;

	if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) { // Nao tem Filhos
		*raiz = NULL;
	}
	else if ((*raiz)->esq == NULL) { // Não tem filho a esquerda
		*raiz = (*raiz)->dir;
	}
	else if ((*raiz)->dir == NULL) { // Não tem filho a direita
		*raiz = (*raiz)->esq;
	}
	else {
		pos = maior(&((*raiz)->esq));
		strcpy((*raiz)->matricula, pos->matricula);
	}
	free(pos);
}

void remover_arvore(TNo **raiz, char matric[10]) {
	if (*raiz == NULL) {
		printf("Erro na remocao.\n");
	}
	else if(strcmp(matric,(*raiz)->matricula) == 0) {
		remover_no(&(*raiz));
	}
	else {
		if (strcmp(matric, (*raiz)->matricula) <= -1) {
			remover_arvore(&((*raiz)->esq),matric);
		}
		else {
			remover_arvore(&((*raiz)->dir),matric);
		}
	}
}

int iniciar_arvore(TNo **raiz, FILE *arq) {
	TAluno aluno;
	int status;
	int pos = -1;
	fseek(arq, 0, 0);
	status = fread(&aluno, sizeof(TAluno), 1, arq);
	while (1) {
		if (status != 1) {
			if (!feof(arq)) {
				printf("ERRO\N");
			}
			break;
		}
		else {
			pos++;
			inserir_arvore(raiz,aluno.matricula,pos);
		}
		status = fread(&aluno, sizeof(TAluno), 1, arq);
	}
	return pos;
}

// Destruir Arvore

void destruir_arvore(TNo **raiz) {
	if (*raiz == NULL) {
		return;
	}
	else if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
		free((*raiz));
	}
	else if ((*raiz)->esq == NULL) {
		destruir_arvore(&((*raiz)->dir));
	}
	else if ((*raiz)->dir == NULL) {
		destruir_arvore(&((*raiz)->esq));
	}
	else {
		destruir_arvore(&((*raiz)->esq));
		destruir_arvore(&((*raiz)->dir));
	}
}