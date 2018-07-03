#ifndef CODE_H
#define CODE_H
#include <stdlib.h>
#include <string.h>


int IN = 0;

typedef struct {
	char carac;
	char code[30];
	int qtdeC;
} Code;

typedef struct {
	Code* codes;
	int qtde;
} Map;


Map* criaMap(int qtde) {
	Map* M = (Map*) malloc(sizeof(Map));
	M->qtde = qtde;
	M->codes = (Code*) calloc(qtde, sizeof(Code));
	return M;
}

void addAtr(Map* M, char carac, char* code) {
	int i = IN;


	if (i < M->qtde) {

		M->codes[i].carac = carac;
		M->codes[i].qtdeC = strlen(code);
		// M->codes[i].code = (char*) calloc(strlen(code)+1, sizeof(char));
		// M->codes[i].code = code;
		strcpy(M->codes[i].code, code);

		IN++;
	}
}

void print(Map* M) {
	int i = 0;

	while (i < M->qtde) {
		printf("%c -- %s\n", M->codes[i].carac, M->codes[i].code);
		++i;
	}
}

Map* addMap(Map* M, Code co) {
	if (M) {
		Code* aux = M->codes;
		M->codes = (Code*) calloc(M->qtde+1, sizeof(Code));
		int i = 0;
		while (i < M->qtde) {
			M->codes[i] = aux[i];
			++i;
		}
		free(aux);
		M->codes[M->qtde] = co;
		M->qtde++;
		return M;
	}
}



#endif