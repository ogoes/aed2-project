#ifndef DATA_H
#define DATA_H
#include <stdlib.h>
#include <string.h>
#include "code.h"


typedef struct dict {
	char value;
	unsigned long int qtde; //quantidade de vezes que a carac se repete

	struct dict* left;
	struct dict* right;

} Dict;


typedef struct {
	Dict** dict;
	int qtde; //quantidade de caracs
	Map* map;
} Global;

int inDict(Global* global, char carac);
void addDict(Global* global, char carac);
void oneMore(Global* global, char carac);
void readCarac(Global* global, char carac);
void mostra(Global* global);
Global* newGlobal();
void finishRead(Global* global);
void freeG(Global* global);
void treeGlobal(Global* global);
void addMaps(Global* global, Dict* node, char word[]);


int inDict(Global* global, char carac) { // verifica se o carac já está em dict
	if (global->qtde == 0) return 0;
	int i = 0;
	while (i < global->qtde) {
		if (carac == global->dict[i]->value) {
			return 1;
		}
		++i;
	}

	return 0;
}

void addDict(Global* global, char carac) { // adiciona caracs ao dicionario
	Dict** aux = global->dict;
	
	global->dict = (Dict** ) calloc (global->qtde + 1, sizeof(Dict*));
	int i = 0;

	while (i < global->qtde) {
		global->dict[i] = aux[i];
		++i;
	}
	free(aux);


	global->dict[i] = (Dict* ) malloc(sizeof(Dict));
	global->dict[i]->value = carac;
	global->dict[i]->qtde = 1;
	global->dict[i]->left = NULL;
	global->dict[i]->right = NULL;
	global->qtde += 1;
}

void oneMore(Global* global, char carac) { // contabiliza mais um para o carac
	int i = 0;

	while (i < global->qtde) {
		if (carac == global->dict[i]->value)
			global->dict[i]->qtde += 1;

		++i;
	}
}

void readCarac(Global* global, char carac) {
	if (inDict(global, carac)) {
		oneMore(global, carac);
	}
	else {
		addDict(global, carac);
	}
}

void mostra(Global* global) {
	int i = 0;

	while (i < global->qtde) {
		printf("L: %c -- Q: %i\n", global->dict[i]->value, global->dict[i]->qtde);
		++i;
	}
	printf("quantidade de letras: %i\n", global->qtde);
}

Global* newGlobal() {
	Global* G = (Global*) malloc (sizeof(Global));


	G->dict = NULL;
	G->qtde = 0;

	return G;
}

void finishRead(Global* global) {
	int i = 0;
	int j;


	while (i < global->qtde-1) {
		j = i + 1;
		while (j > 0 && global->dict[j-1]->qtde > global->dict[j]->qtde) {
			Dict* aux = global->dict[j-1];
			global->dict[j-1] = global->dict[j];
			global->dict[j] = aux;
			--j;
		}
		++i;
	}
	global->map = criaMap(global->qtde);
	treeGlobal(global);
	addMaps(global, global->dict[0], "");
	// print(global->map);
	// freeG(global);
}	

void freeN(Dict* node) {
	if (node) {	
		freeN(node->left);
		freeN(node->right);
		free(node);
	}
}
void freeG(Global* global) {

	freeN(global->dict[0]);
	free(global->dict);
	free(global);
}

void diminuiDict(Global* global) {
	Dict** Aux = (Dict**) calloc (global->qtde-1, sizeof(Dict*));

	int i = 1;
	while (i < global->qtde) {
		Aux[i-1] = global->dict[i];
		++i;
	}
	global->qtde -= 1;
	global->dict = Aux;
}

char* concatena(char* string, char str[]) {
	char* aux = string;
	string = (char*) calloc (strlen(string)+2, sizeof(char));

	int i = 0;
	int tam = strlen(aux);
	while (i < tam) {
		string[i] = aux[i];
		++i;
	}
	string[i] = str[0];

	return string;
}

void addMaps(Global* global, Dict* node, char word[]) {
	
	if (!node->left && !node->right) {
		// printf("%c -- %s\n", node->value, word);
		addAtr(global->map, node->value, word);
		return;
	}
	
	char* left = word;
	char* right = word;


	left = concatena(left, "0");
	right = concatena(right, "1");

	addMaps(global, node->left, left);
	addMaps(global, node->right, right);

}

void treeGlobal(Global* global) {
	Dict* root = (Dict*) malloc (sizeof(Dict));
	root->value = '*';

	if (global->qtde > 1) {	
		Dict** aux = global->dict;
		root->left = aux[0];
		root->right = aux[1];
		root->qtde = aux[0]->qtde + aux[1]->qtde;
		
		diminuiDict(global);
		aux = global->dict;
		aux[0] = root;
		int i = 0;

		while (i < global->qtde-1 ) {

			if (aux[i]->qtde > aux[i+1]->qtde) {
				Dict* eee = aux[i];
				aux[i] = aux[i+1];
				aux[i+1] = eee;
			}
			++i;
		}

		

		treeGlobal(global);
	}
	else {
		free(root);
	}
}




#endif