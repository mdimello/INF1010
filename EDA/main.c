#include <stdio.h>
#include "abb.h"

int main() 
{
	Abb * raiz, *temp;

	raiz = abb_cria();
	raiz = abb_insere(raiz, 5);
	raiz = abb_insere(raiz, 2);
	raiz = abb_insere(raiz, 1);
	raiz = abb_insere(raiz, 3);
	raiz = abb_insere(raiz, 8);
	raiz = abb_insere(raiz, 7);
	raiz = abb_insere(raiz, 6);
	raiz = abb_insere(raiz, 9);
	printf("%s\n", abb_testa(raiz) ? "0 Arvore ok!" : "0 Arvore com defeito!");

	abb_mostra_arvore("\nEstrutura:", raiz);
	abb_mostra_ordem("\nOrdem:", raiz);

	printf( "\n" );
	temp = abb_busca(raiz, 9);
	printf("busca 9 e:  %s\n", temp ? "Achou!" : "Nao achou!");
	temp = abb_busca(raiz, 4);
	printf("busca 4 e:  %s\n", temp ? "Achou!" : "Nao achou!");

	printf("\nremove e recoloca 6");
	raiz = abb_retira(raiz,6);
	raiz = abb_insere(raiz, 6);
	printf("\n%s", abb_testa(raiz) ? "1 Arvore ok!" : "1 Arvore com defeito!");
	abb_mostra_arvore("\nEstrutura:", raiz);
	abb_mostra_ordem("\nOrdem:", raiz);

	printf("\n\nremove 5");
	raiz = abb_retira(raiz, 5);
	printf("\n%s", abb_testa(raiz) ? "1 Arvore ok!" : "1 Arvore com defeito!");
	abb_mostra_arvore("\nEstrutura:", raiz);
	abb_mostra_ordem("\nOrdem:", raiz);

	printf( "\n" );

	return 0;
}