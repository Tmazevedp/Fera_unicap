#include<stdio.h>
#include"Types.h"

void inserir_arvore(TNo **abb, char matric[],int pos);
int buscar(TNo *abb, char matric[]);
void remover_arvore(TNo **raiz, char matric[10]);
void remover_no(TNo **raiz);
TNo *maior(TNo **raiz);
void destruir_arvore(TNo **raiz);
int iniciar_arvore(TNo **raiz, FILE *arq);