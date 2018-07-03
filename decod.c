#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"


FILE* read;
FILE* write;

int readed = 0;

char buffer[33];
char* binario;

char string[33];
char lidos[3][30];
int qlidos = 0;


int qtdeBits(unsigned int A) {
	int i = 0;

	while (A > 0) {
		++i;
		A /= 2;
	}
	return i;
}


char* intToBinary(unsigned int N) {
	int resto = N;
	int i = 0;
	char* binary = (char*) calloc(33, sizeof(char));

	int tam = qtdeBits(N);

	i = 31;

	while (i >= 0) {
		if (N % 2 == 0)
			binary[i] = '0';
		else
			binary[i] = '1';
		N /= 2;
		--i;
	}

	// printf("%s\n", binary);
	return binary;
}

void limpaString (int tam) {
	int i = tam-1;
	while (i >= 0) {
		string[i] = '\0';
		--i;
	}
}
void contaTre() {
	int i = 0;
	int count = 0;
	while (i < 2) {
		if (strcmp(lidos[i], lidos[i+1]) == 0 && qlidos == 3) {
			++count;
		}
		++i;
	}

	if (count == 2) exit (0);
	else qlidos = 0;

}



void decodEscreve(Map* mapa, char bin[], char const escrita[]) {
	int i = 0;

	

	int bufTam = strlen(string);
	while (readed < 32) {
		i = 0;

		string[bufTam] = bin[readed];

		++bufTam;

		while (i < mapa->qtde) {
			if (strcmp(mapa->codes[i].code, string) == 0) {
				// printf("%c", mapa->codes[i].carac);
				contaTre();
				strcpy(lidos[qlidos], mapa->codes[i].code);
				++qlidos;
				fputc(mapa->codes[i].carac, write);
				

				

				limpaString(bufTam);
				bufTam = 0;
			}
			++i;
		}
		++readed;
	}


	readed = 0;

}


void leitura(char const leitura[], char const escrita[]) {

	
	read = fopen(leitura, "rb");
	if (!read) {
		printf("Erro em abrir o arquivo %s\n", leitura);
		exit(0);
	}

	Map* mapa = criaMap(0);
	Code code;
	fread(&code, sizeof(Code), 1, read);
	while (code.qtdeC != -1) {
		addMap(mapa, code);
		fread(&code, sizeof(Code), 1, read);
	}
	// print(mapa);
	int A;
	fread(&A, 4, 1, read);
	
	write = fopen(escrita, "w");
	if (!write) {
		printf("Erro em criar arquivo %s\n", escrita);
		exit(0);
	}


	while(!feof(read)) {
		binario = intToBinary(A);
		decodEscreve(mapa, binario, escrita);
		free(binario);
		fread(&A, 4, 1, read);
	}

	printf("\n");
}


int main(int argc, char const *argv[]) {

	if (argc != 3) {
		printf("Informe os arquivos\n");
		printf("e.g - \"%s  Leitura  Escrita.txt\"\n", argv[0]);
		exit(0);
	}
	leitura(argv[1], argv[2]);
	
	// char* binario = intToBinary(775918599);
	// printf("%s\n", binario);

	// free(binario);

	// system("du a");
	return 0;
}