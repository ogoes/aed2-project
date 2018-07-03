#ifndef ARQ_H
#define ARQ_H

#include "data.h"
#include "code.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* read;
FILE* write;

int indices = 0;
char codes32[33];
char buffer[33];

int qtdeBits(unsigned int A) {
	int i = 0;

	while (A > 0) {
		++i;
		A /= 2;
	}
	return i;
}

char* invertString(char code[]) {
	char* invertido = (char*) calloc(33, sizeof(char));
	int j = 0;
	int i = strlen(code)-1;

	while (i >= 0) {
		invertido[j] = code[i];
		--i;
		++j;
	}

	return invertido;
}


void limpaString (int tam) {
	int i = tam-1;
	while (i >= 0) {
		codes32[i] = '\0';
		--i;
	}
}


unsigned long int binaryToInt(char* string) {
	int tam = strlen(string);
	unsigned long res = 0;

	if (string[0] == '1') {
		res = res | 1;
	}

	int i = 1;
	while (i < tam) {
		res = res << 1;
		if (string[i] == '1') {
			res = res | 1;
		}
		++i;
	}

	return res;
}


void mergeCodes(char code[]){
	int tam = strlen(code);
	int i = 0;

	if (buffer[0] != '9') {
		int buf = strlen(buffer);
		while (i < buf && indices < 32) {
			codes32[indices] = buffer[i];
			++i; ++indices;
		}
	}


	i = 0;
	while (i < tam && indices < 32) {
		codes32[indices] = code[i];
		++i; ++indices;
	}

	int j = 0;
	while (i < tam+1) {
		buffer[j] = code[i];
		++i, ++j;
	}

}







void escreve(Map* M) {
	unsigned int A;
	int i = 0;

	while (i < M->qtde) {
		fwrite(&M->codes[i], sizeof(Code), 1, write);
		++i;
	}
	Code Co;
	Co.qtdeC = -1;
	fwrite(&Co, sizeof(Code), 1, write);

	fseek(read, 0, SEEK_SET);
	
	buffer[0] = '9';
	char C = fgetc(read);
	while (!feof(read)) {
		i = 0;
		while (i < M->qtde) {
			if (C == M->codes[i].carac) {	
				// printf("%s\n", M->codes[i].code);
				mergeCodes(M->codes[i].code);
				// buffer[0] = '9';
			}

			++i;
		}

		
		if (indices == 32) {
			indices = 0;
			// printf("%s\n", codes32);
			A = binaryToInt(codes32);
			limpaString(strlen(codes32));
			fwrite(&A, 4, 1, write);
		}
		
		C = fgetc(read);
	}
	A = binaryToInt(codes32);
	// printf("%s\n", codes32);
	
	fwrite(&A, 3, 1, write);
	limpaString(strlen(codes32));
}
void begin() {
	Global* G = newGlobal();

	int i = 0;
	char C = fgetc(read);
	while (!feof(read)) {
		++i;
		readCarac(G, C);
		C = fgetc(read);
	}
	if (i > 0) {
		finishRead(G);
		escreve(G->map);
	}
}


void init(char const Read[], char const Write[]) {
	read = fopen(Read, "r");

	if (!read) {
		printf("Erro em abrir arquivo de leitura %s\n", Read);
		return;
	}
	write = fopen(Write, "r");
	if (write) {
		fclose(write);
		char rm[10] = {'r', 'm', ' '};
		strcat(rm, Write);
		system(rm);
	} 

	write = fopen(Write, "wb");
	begin();
	return;
}
















#endif 