#include<stdio.h>
#include "Types.h"

void cadastrar(FILE *arq,TNo **Abb);
void alterar_aluno(FILE *arq, TNo *Abb);
void buscar_aluno(char matricula[], FILE *arq, TNo *Abb);
void remover_cadastro(TNo *Abb, char matric[], FILE *arq);

