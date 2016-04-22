#include <stdio.h>
#include "arvb23.h"


struct _arvb23 {
	int      kp, kg;   /* chaves: kp<kg, se kg existir. Se kg=-1, significa que ele não existe. */
	ArvB23  *pai;
	ArvB23  *esq;
	ArvB23  *meio;
	ArvB23  *dir;
};

void Mostra(char* titulo, ArvB23* raiz)
{
	if (titulo != NULL) printf("%s ", titulo);
	if (raiz != NULL) {
		printf("<");
		printf("%d ", raiz->kp);
		if (raiz->kg == -1) printf(" - ");
		else printf("%d", raiz->kg);
		Mostra(NULL, raiz->esq);
		Mostra(NULL, raiz->meio);
		Mostra(NULL, raiz->dir);
		printf(">");
	}
	else
		printf(".");
	if (titulo != NULL) {
		printf("\n");
	}
}




void Testa(ArvB23* no) {
	if (no == NULL) return;
	if ((no->kg == -1) && (no->esq != NULL) && (no->dir != NULL))    printf("\nNo [%d,%d] tem filho a direita.");
	if ((no->esq != NULL) && (no->meio == NULL))   printf("\nNo [%d,%d] nao tem filho a esquerda.");
	if ((no->kg != -1) && (no->kp>no->kg))    printf("\nNo [%d,%d] fora de ordem.");
	if ((no->esq) && (no->esq->pai != no))    printf("\nNo [%d,%d] filho a esquerda com ponteiro de pai errado.");
	if ((no->meio) && (no->meio->pai != no))  printf("\nNo [%d,%d] filho do meio com ponteiro de pai errado.");
	if ((no->dir) && (no->dir->pai != no))    printf("\nNo [%d,%d] filho a direita com ponteiro de pai errado.");
	if ((no->kg != -1) && (no->kp>no->kg))  printf("\nNo [%d,%d] chave da direita menor que chave da esquerda.");
	Testa(no->esq);
	Testa(no->meio);
	Testa(no->dir);
}


void imprimeOrdem(ArvB23* no) {
	if (no != NULL) {
		imprimeOrdem(no->esq);
		printf("%d ", no->kp);
		imprimeOrdem(no->meio);
		if (no->kg != -1) {
			printf("%d ", no->kg);
			imprimeOrdem(no->dir);
		}
	}
}



int main(void)
{
	ArvB23* raiz = a23Cria(5);   Mostra("cria    5 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Insere(raiz, 12);	Mostra("Insere 12 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Insere(raiz, 17);	Mostra("Insere 17 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Insere(raiz, 2);	Mostra("Insere  2 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Insere(raiz, 15);	Mostra("Insere 15 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Insere(raiz, 4); 	Mostra("Insere  4 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Insere(raiz, 6);	Mostra("Insere  6 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Insere(raiz, 7);	Mostra("Insere  7 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");

	raiz = a23Retira(raiz, 5); Mostra("\nRetira  5 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Retira(raiz, 12);  Mostra("Retira 12 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Retira(raiz, 17);  Mostra("Retira 17 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Retira(raiz, 2);   Mostra("Retira  2 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Retira(raiz, 15);  Mostra("Retira 15 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Retira(raiz, 4);   Mostra("Retira  4 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Retira(raiz, 6);   Mostra("Retira  6 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	raiz = a23Retira(raiz, 7);   Mostra("Retira  7 =", raiz); Testa(raiz); imprimeOrdem(raiz); printf("\n");
	printf("Vazia?\n");

	return 0;
}