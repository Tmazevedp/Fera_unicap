#include<stdio.h>
#include<string.h>
#include "Types.h"

void inicializar_arvore(TNo **abb) {
	*abb = NULL;
}


void inserir_arvore(TNo **abb, char matric[]) {

	if (*abb == NULL) {
		*abb = (TNo*)malloc(sizeof(TNo));
		strcpy((*abb)->matricula, matric);
		(*abb)->dir = NULL;
		(*abb)->esq = NULL;
		(*abb)->indice++;
	}
	else {
		if (strcmp((*abb)->matricula, matric)) {
			printf("A matricula ja existe! Digite Novamente a matricula:");
			return;
		}
		else {
			if (strcmp(matric, (*abb)->matricula) < 0) {
				inserir_arvore((*abb)->esq, matric);
			}
			else {
				inserir_arvore((*abb)->dir, matric);
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