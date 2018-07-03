#include <stdio.h>
#include "data.h"
#include "Arq.h"


int main (int argc, char const *argv[]) {


	if (argc > 2) {
		init(argv[1], argv[2]);
	}
	else {
		printf("Informe os arquivos\n");
		printf("e.g - ./main  Leitura.txt  Escrita\n");
	}

	return 0;
}