#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "set.h"



struct set
{
	int set_size;  /* numero de elementos do conjunto */
	int vet_size;  /* numero de elementos no vetor de inteiros semi-positivos */
	unsigned int* vet; /* vetor de inteiros que armazena os bits que representam o conjunto */
};



/* cria um conjunto com n elementos */
Set* setCreate( int set_size )
{
	Set* set = ( Set* )malloc( sizeof( Set ) );
	if ( set != NULL )
	{
		int i;
		set->set_size = set_size;
		set->vet_size = ( int ) ceil( ( set_size / 8.0 ) * sizeof( unsigned int ) );
		set->vet = ( unsigned int* ) malloc( set->vet_size * sizeof( unsigned int ) );
		for( i = 0; i < set->vet_size; i++ )
		{
			set->vet[i] = 0;
		}
	}

	return set;
}



/* destroi (desaloca) o conjunto */
Set* setDestroy( Set* set ) 
{
	if( set ) 
	{
		if( set->vet )
		{
			free( set->vet );
		}
		free( set );
	}
	return NULL;
}



/* cria uma copia do conjunto */
Set* setCopy( Set* set )
{
	int i;

	Set *copy; 

	copy = setCreate( set->set_size );

	for( i = 0; i < set->vet_size; i++ )
	{
		copy->vet[i] = set->vet[i];
	}

	return copy;
}



/* cria uma copia do conjunto */
Set* setComplement( Set* set )
{
	int i;

	Set *copy; 

	copy = setCreate( set->set_size );

	for( i = 0; i < set->vet_size; i++ )
	{
		copy->vet[i] = ~ set->vet[i];
	}

	return copy;
}



/* insere o elemento i no conjunto */
void setInsert( Set *set, int i ) 
{
	/* busca a posição do elemento no vetor */
	int k = i / sizeof( unsigned int );

	/* máscara para inserir na posição correta do elemento */
	unsigned int mask = 1 << i % sizeof( unsigned int );

	set->vet[k] = set->vet[k] | mask;
}



/* remove o elemento i do conjunto */
void setRemove( Set *set, int i )
{
	/* busca a posição do elemento no vetor */
	int k = i / sizeof( unsigned int );

	/* máscara para remover da posição correta do elemento */
	unsigned int mask = 1 << i % sizeof( unsigned int );
	mask = ~mask;

	set->vet[k] = set->vet[k] & mask;
}



/* testa se o elemento i pertence ao conjunto */
int setIsMember( Set *set, int i )
{
	/* busca a posição do elemento no vetor */
	int k = i / sizeof( unsigned int );

	/* máscara para procurar na posição correta do elemento */
	unsigned int mask = 1 << i % sizeof( unsigned int );

	return set->vet[k] & mask ;
}



/* cria a uniao de dois conjunto que podem ter tamanhos diferentes */
/* naturalmente o numero de elementos do universo e' o do maior dos dois */
Set* setUnion( Set *set1,  Set *set2 )
{
	Set *tmp; 
	int max_set_size = set1->set_size > set2->set_size ? set1->set_size : set2->set_size;
	int i;

	tmp = setCreate( max_set_size );

	for( i = 0; i < ( ( max_set_size / 8 ) * sizeof( unsigned int ) ) + 1; i++ )
	{
		tmp->vet[i] = set1->vet[i] | set2->vet[i];
	}
	return tmp;
}



/* calcula a intersecao de dois conjuntos, a cardinalidade e' a do menor */
Set* setIntersection( Set *set1,  Set *set2 )
{
	int i;

	Set *set; 
	int set_size = set1->set_size < set2->set_size ? set1->set_size : set2->set_size;

	set = setCreate( set_size );

	for( i = 0; i < set->vet_size; i++ )
	{
		set->vet[i] = set1->vet[i] & set2->vet[i];
	}

	return set;
}



/* calcula a diferenca de set1-set2. a cardinalidade e'a de set1. */
Set* setDifference( Set *set1, Set *set2 )
{
	Set *copy = setCopy( set1 );
	Set *intersection = setIntersection( set1, set2 ); 

	int i;

	setShow( "intersect: ", intersection );


	for( i = 0; i < copy->vet_size; i++ )
	{
		copy->vet[i] = copy->vet[i] & ( ~ intersection->vet[i] );
	}

	return copy;
}



/* verifica de set2 e' um sub conjunto de set1 */
int setIsSubset( Set *set1,  Set *set2 )
{
	int i = 0;

	if( set1->set_size < set2->set_size )
	{
		return 0;	
	}

	for( i = 0; i < set2->vet_size; i++ )
	{
		if( set1->vet[i] != set2->vet[i] )
		{
			return 0;
		}
	}

	return 1;
}



/* verifica se dois conjuntos sao iguais */
int setIsEqual( Set *set1,  Set *set2 ) 
{
	int i = 0;

	if( set1->set_size != set2->set_size )
	{
		return 0;	
	}

	for( i = 0; i < set2->vet_size; i++ )
	{
		if( set1->vet[i] != set2->vet[i] )
		{
			return 0;
		}
	}

	return 1;
}



/* informa a cardilaidade do conjunto */
int setNumberOfElements( Set* set )
{
	return set->set_size;
}



/* mostra os elementos do conjunto */
void setShow( char* title, Set* set )
{
	int i;
	int first = 1;
	printf( "%s={", title );
	for( i = 0; i <= set->set_size; i++ )
	{
		if( setIsMember( set, i ) ) 
		{
			if( first ) 
			{ 
				printf( "%d", i ); 
				first = 0; 
			}
			else
			{
				printf( ",%d", i );
			}
		}
	}
	printf( "}\n" );
}