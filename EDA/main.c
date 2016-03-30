#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "hash.h"

void limpa( char* p, char* q )
{
	while( *p != '\0' )
	{
		if( *p >= 'A' && *p <= 'Z' )  
		{
			*q = *p + 'a' - 'A'; /* letras maiusculas viram minusculas */
			p++; 
			q++;
		}
		else if( *p >= 'a' && *p <= 'z' ) 
		{
			*q = *p;
			p++; 
			q++;
		}
		else 
		{
			/* nao e'um caractere, ignore */
			p++;
		}
	}

	*q = '\0';
}

int main( ) 
{
	TabelaHash* tabela = htCria( 2000 );

	char  palavra[80];

	char referencia[80];

	long int npalavras = 0;

	FILE* fp = fopen( "texto.txt", "rt" );

	if (fp == NULL) 
	{ 
		printf("Arquivo texto. txt nao encontrado.\n"); 
		return 1; 
	}
	else 
	{
		while( fscanf( fp, " %s", palavra ) == 1 ) 
		{
			limpa( palavra, referencia );

			if ( strlen( referencia ) > 1 ) 
			{ 
				htInsere( tabela, referencia );
				npalavras++;
			}
		} 
	}

	printf( "Numero de palavras no texto = %d\n", npalavras );
	printf( "Numero de palavras diferentes = %d\n", htNumeroPalavras( tabela ) );
	printf( "Numero de colisões = %d\n", htNumeroColisoes( tabela ) );
	htSalvaCSV( tabela, "hash_table_mqueiroz.csv" );

	tabela = htLibera( tabela );

	fclose( fp );

	return 0;
}