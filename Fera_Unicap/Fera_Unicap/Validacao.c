#include <stdio.h>
#include <string.h>
#include "Types.h"
#include "Aluno.h"
#include "Disciplina.h"

// Modulo Disciplina

int validar_cod_disciplina(char str[6]) {
	int i, flag = 0, j = 0;
	char str_aux[2], str_aux2[3];
	printf("Digite o codigo da Disciplina:\n");
	gets(str);
	if (strlen(str) == 6) {
		for (i = 0;i < 3;i++) {
			strcpy(str_aux[i], str[i]);
		}

		for (i = 3;i < 7;i++) {
			strcpy(str_aux2[j], str[i]);
			j++;
		}
		i = 0;
		while (flag != 1) { // Testar se os Tres primeiros digitos do codigo sao Letras
			if ((str_aux[i] >= 65 && str_aux[i] <= 90) || (str_aux[i] >= 97 && str_aux[i] <= 122)) {
				i++;
				if (i == 3) {
					flag = 1;
				}
			}
			else {
				printf("Codigo de disciplina Invalido!\n");
				return 0;
			}
		}
		flag = 0;
		j = 0;
		while (flag != 1) {   // Testar se os quatro ultimos digitos do codigo são Numeros
			if (str_aux2[i] >= 48 && str_aux2[i] <= 57) {
				i++;
				if (i == 4) {
					flag = 1;
				}
			}
			else {
				printf("Codigo de disciplina Invalido!\n");
				return 0;
			}
		}
		for (i = 0;i < 3;i++) { // Passando as Trs primeras letras para Maiusculo
			toupper(str_aux[i]);
		}

		for (i = 0;i < 3;i++) { // Copiando a parte do codgo de disciplina para a string original já formatada com o a letra em maiusculo
			strcpy(str[i], str_aux[i]);
		}
		j = 3;
		for (i = 0;i < 4;i++) {
			strcpy(str[j], str_aux2[i]);
			j++;
		}
		return 1;
	}
}

void validar_nome_disciplina(char str[100]) {
	int i=0,flag=0;
	printf("Digite o nome da disciplina:\n");
	gets(str);
	while (flag != 1) { // Verifica se o nome da diciplina tem apenas letra e espaços
		if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || str[i] == ' ') {
			i++;
			if (str[i] == '\0') {
				flag = 1;
			}
		}
		else {
			printf("Nome de disciplina Invalido!\n");
			return;
		}

	}
}		