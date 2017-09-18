#include<stdio.h>
#include "Types.h"

void cadastrar(FILE *arq, TNo **Abb,int pos);
void alterar_aluno(FILE *arq, TNo *Abb);
void buscar_aluno(FILE *arq, TNo *Abb);
void remover_cadastro(TNo *Abb, FILE *arq);
void manutencao_aluno(FILE *arq);


