#include<stdio.h>
#include"Types.h"

void cadastrar_disciplina(FILE *arq, TNo **Abb,int pos_cad);
void alterar(FILE *arq, TNo *Abb);
void buscar_disciplina(FILE *arq, TNo *Abb);
void remover_disciplina(TNo **Abb, char matric[], FILE *arq);
void manutencao_disciplina(FILE* arq);