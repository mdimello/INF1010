#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

struct _heap 
{
	int max;           /* tamanho maximo do heap */
	int pos;           /* proxima posicao disponivel no vetor */
	float* prioridade; /* vetor das prioridades */
};



Heap* heap_cria( int max )
{
	Heap* heap = ( Heap* ) malloc( sizeof( Heap ) );
	if( ! heap )
	{
		return NULL;
	}

	heap->max = max;
	heap->pos = 0;
	heap->prioridade = ( float* ) malloc( max * sizeof( float ) );

	return heap;
}



Heap* heap_libera( Heap* h )
{
	if( h )
	{
		free( h->prioridade );
		free( h );
	}

	return NULL;
}



static void troca( int a, int b, float* v )
{
	float f = v[ a ];
	v[ a ]  = v[ b ];
	v[ b ]  = f;
}



static void corrige_acima( Heap* heap, int pos )
{
	while( pos > 0 )
	{
		int pai = ( pos - 1 ) / 2;

		if( heap->prioridade[ pai ] < heap->prioridade[ pos ] )
		{
			troca( pos, pai, heap->prioridade );
		}
		else
		{
			break;
		}

		pos = pai;
	}
}


int heap_insere(Heap* heap, float prioridade)
{
	if( ! heap )
	{
		return 1;
	}

	if( heap->pos < heap->max )
	{
		heap->prioridade[ heap->pos ] = prioridade;
		corrige_acima( heap, heap->pos );
		heap->pos++;

		return 0;
	}

	return 1;
}



static void corrige_abaixo( Heap* heap, int pai )
{
	while( 2*pai+1 < heap->pos )
	{
		int filho_esq=2*pai+1;
		int filho_dir=2*pai+2;
		int filho;

		if( filho_dir >= heap->pos ) 
		{
			filho_dir=filho_esq;
		}

		if( heap->prioridade[ filho_esq ] > heap->prioridade[ filho_dir ] )
		{
			filho=filho_esq;
		}
		else
		{
			filho=filho_dir;
		}

		if( heap->prioridade[ pai ] < heap->prioridade[ filho ] )
		{
			troca( pai, filho, heap->prioridade );
		}
		else
		{
			break;
		}

		pai=filho;
	}
}



float heap_remove( Heap* heap )
{
	if( heap->pos > 0 ) 
	{
		float topo = heap->prioridade[ 0 ];
		heap->prioridade[ 0 ] = heap->prioridade[ heap->pos-1 ];
		heap->pos--;

		corrige_abaixo( heap, 0 );

		return topo;
	}

	return -1;
}



void heap_show( Heap* h, char* title )
{
	int i;

	printf( "%s={", title );

	for( i=0; i < h->pos; i++ )
	{
		printf( "%g,", h->prioridade[ i ] );
	}

	printf( "}\n" );
}


/*
 * Ordena uma sub arvore do heap:
 * Similar à função corrige_abaixo.
 * 
 * Complexidade f(H) onde H = log n
 * O( H ) = O( log n )
 * 
 * @param pai - posicao da raiz da sub arvore a ser ordenada.
 * @param n   - numerno de elementos.
 * @param v   - vetor contendo os elementos.
 */
static void max_heapify( int pai, int n, float *v )
{
	/*
	 * Considerando um heap como uma árvore binária armazenada em um vetor, 
	 * onde o primeiro elemento está na posição 0, inferimos que os filhos 
	 * de um pai numa posição i podem ser encontrados nas posições:
	 * 2 * i + 1 (filho da esquerda)
	 * 2 * i + 2 (filho da direita).
	 */ 
	int esq =  2 * pai + 1;
	int dir =  2 * pai + 2;

	int maior;

	if( esq < n && v[ esq ] > v[ pai ] )
	{
		/* O filho da esquerda é maior que o pai. */
		maior = esq;
	}
	else
	{
		/* O pai é maior que o filho da esquerda. */
		maior = pai;
	}


	if( dir < n && v[ dir ] > v[ maior ] )
	{
		/* O filho da direita é maior que o pai e o filho da esquerda. */
		maior = dir;
	}

	if( maior != pai )
	{
		/* 
		 * Se o maior nó não for o pai, para mantermos a propriedade que diz que 
		 * o pai sempre deve ser maior que seus filhos, devemos troca-lo com o 
		 * maior de seus filhos. 
		 */
		troca( maior, pai, v );

		/* 
		 * Vamos supor que a função receba como parâmetro a sub árvore abaixo.
		 * Para ordená-la começamos verificando que o pai = 7 possui 2 nós:
		 * Esquerda = 9; Direita = 6; Observamos que o nó da direita é o maior 
		 * filho e que também é maior que o pai. Logo eles devem ser trocados.
		 * Após a troca observamos que o heap ainda não está ordenado, e para
		 * corrigir chamamos novamente a função porém somente para a sub árvore 
		 * que aprezenta o problema. No pior caso, onde a função terá que ser 
		 * chamada recursivamente até um nó de altura 0, a função será chamada
		 * h vezes, onde h é a altura da sub árvore.
         *
		 *  h = 2         7            9
		 *               / \          / \
		 *  h = 1       9   6  ==>   7   6
		 *             /            /
		 *  h = 0     8            8
		 *
		 *  f( h )
		 */
		max_heapify( maior, n, v );
	}
}


/**
 * Transforma um vetor em heap ordenado.
 *
 * H = log n
 * Numero de nos em h <= 2^[ (logn-h)-1 ]
 * Numero de nos em h <= [ 2^(log n) / 2^(h+1) ]
 * Numero de nos em h <= [ n / 2^(h+1) ]
 *
 * Para percorrer todos os nós da árvore:
 * sum{ [ n/2^(h+1) ] * O(H) } 0..log n
 * O{ n * sum[ h / 2^(h+1) ] 0..log n }
 * O[ n * sum( h / 2^h ) 0..infinito  }
 * Sabemos que sum( h / 2^h ) 0..infinito converge para 2, logo:
 * O( n )
 *
 * Complexidade O(n)
 *
 * @param n - numero de elementos.
 * @param v - vetor contendo os elementos.
 * @return max heap
 */
Heap* heap_monta(int n, float* v )
{
	int i;

	Heap* heap = ( Heap* ) malloc( sizeof( Heap ) );
	if( ! heap )
	{
		return NULL;
	}
	heap->max = n;
	heap->pos = 0;
	heap->prioridade = ( float * ) malloc( n * sizeof( float ) );
	for( i = 0; i < n; i++ )
	{
		heap->prioridade[i] = v[i];
	}

	/* 
	 * Utilizando a propriedade do heap que diz que um heap é uma 
	 * árvore binária completa, descobrimos que o último nó com filhos 
	 * é o que está na posição ( n / 2 ) - 1 e que todos os nós com posições 
	 * menores possuem filhos. Para ordenar o heap, o percorremos ordenando 
	 * todos os nós com filhos, de baixo para cima.
	 */
	for( i = ( n / 2 ) - 1; i >= 0; i-- )
	{
		/*
		 * O(H)
		 */
		//max_heapify( i, n, heap->prioridade );

		corrige_abaixo( heap, i );
	}

	heap->max = n;
	heap->pos = n;
	heap->prioridade = v;

	return heap;
}



/*
 * Ordena os elementos de um vetor.
 *
 * Complexidade O(n) * O( log n )
 * Complexidade O(n log n)
 *
 * @param n - numero de elementos.
 * @param v - vetor contendo os elementos.
 */
void heap_sort( int n, float* v )
{
	/* 
	 * Cria um max heap com os elementos do vetor 
	 * Complexidade O(n)
	 */
	Heap* max = heap_monta( n, v );

	int i;

	/*
	 * Pega um vetor e após ordena-lo troca a primeira posição com a última,
	 * ou seja, bota o maior elemento na última posição, que é onde deveria
	 * estar em uma ordenação crescente.
	 *
	 * Repete o processo n vezes até que os n elementos estejam organizados.
	 */
	for( i = n; i > 1; i-- )
	{
		/* 
		 * Complexidade O( log n )
		 */
		max_heapify( 0, i, v );

		troca( 0, i - 1, v );
	}
}