#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define NPAL 64



struct _palavra
{
	int n;
	char pal[ NPAL ];
	struct _palavra* prox; 
};



typedef struct _palavra Palavra;



struct _hash
{
	int size;
	Palavra** table;
};



/* cria uma tabela hash de "tamanho"  */
TabelaHash* htCria( int tamanho )
{
	int i = 0;
	TabelaHash* hash = NULL;

	if( tamanho < 1 )
	{
		return NULL;
	}

	hash = ( TabelaHash* ) malloc( sizeof( TabelaHash ) );
	if( ! hash )
	{
		return NULL;
	}

	hash->size = tamanho;
	hash->table = ( Palavra ** ) malloc( tamanho * sizeof( Palavra * ) );
	if( ! hash->table )
	{
		return NULL;
	}

	for( i = 0; i < tamanho; i++ )
	{
		hash->table[i] = NULL;
	}
	
	return hash;
}



static int hash ( int size, char* s )
{
	unsigned int i = 0;
	unsigned int hash = 0;
    for( i = 0; s[i] != '\0'; i++) 
	{
        hash = ((hash << 5) + hash) + s[i];     
    } 

    return hash % size;
}



/* insere uma palavra na tabela   */
void htInsere( TabelaHash* tabela, char* palavra )
{
	int h = hash( tabela->size, palavra );

	Palavra* p = tabela->table[h];
	while( p != NULL ) 
	{
		if( strcmp( p->pal, palavra ) == 0 )
		{
			p->n++;
			break;
		}

		p = p->prox;
	}

	if( p == NULL ) 
	{ 
		/* não encontrou o elemento */
		/* insere novo elemento no início da lista */
		p = ( Palavra *) malloc( sizeof( Palavra ) );

		p->n = 1;
		strcpy( p->pal, palavra );
		p->prox = tabela->table[h];

		tabela->table[h] = p;
	}
}



/* busca uma palavra */
void* htBusca( TabelaHash* tabela, char* palavra )
{
	int h = hash( tabela->size, palavra );

	Palavra* p = tabela->table[ h ];
	while( p != NULL ) 
	{
		if ( strcmp( tabela->table[ h ]->pal, palavra ) == 0 )
		{
			return tabela->table[h];
		}

		p = p->prox;
	}

	return NULL;
}



static void lstLibera( Palavra* p )
{
	if( ! p )
	{
		return;
	}

	if( p->prox )
	{
		lstLibera( p->prox );
	}

	free( p );
}



/* libera a tabela */
TabelaHash* htLibera( TabelaHash* tabela )
{
	int i = 0;

	for( i = 0; i < tabela->size; i++ )
	{
		lstLibera( tabela->table[i] );
	}

	free( tabela );

	return NULL;
}



/* retorna o numero de palavras distintas armazenadas */
int htNumeroPalavras( TabelaHash* tabela )
{
	int i = 0;
	int cont = 0;;

	for( i = 0; i < tabela->size; i++ )
	{
		Palavra* p = tabela->table[i];
		while( p != NULL ) 
		{
			cont++;
			p = p->prox;
		}
	}

	return cont;
}



/* retorna o numero de colisoes na tabela hash*/
int htNumeroColisoes(TabelaHash* tabela)
{
	int i = 0;
	int cont = 0;;

	for( i = 0; i < tabela->size; i++ )
	{
		Palavra* p = tabela->table[i];
		while( p != NULL ) 
		{
			if( p->prox != NULL )
			{
				cont++;
			}
			p = p->prox;
		}
	}

	return cont;
}



/*
 * Salva as palavras e o numero de ocorrencias num
 * arquivo texto no formato Coma Separated Value (csv).
*/
void htSalvaCSV( TabelaHash* tabela, char* filename )
{
	int i = 0;
	FILE *f = fopen( filename, "w");
	if( f == NULL )
	{
		return;
	}

	fprintf( f,"palavra,num\n");
	
	for( i = 0; i < tabela->size; i++ )
	{
		Palavra* p = tabela->table[i];
		while( p != NULL ) 
		{
			fprintf( f, "%s,%d\n", p->pal, p->n );
			p = p->prox;
		}
	}


	fclose(f);
}