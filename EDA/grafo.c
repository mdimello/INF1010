#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <assert.h>

#include "grafo.h"
#include "dset.h"

#define UNVISITED 0
#define VISITED   1

#define INFINITY -1

typedef struct _viz Viz;
struct _viz 
{
	int noj;
	float peso;
	Viz*  prox;
};



struct _grafo 
{
	int nv;           /* numero de nos ou vertices */
	int na;           /* numero de arestas */
	char orientado;   /* 0 = nao orientado */
	Viz** viz;        /* viz[i] aponta para a lista de arestas vizinhas do no i */
};



/* aux para fila e pilha */
typedef struct _sq SQ;
struct _sq 
{
	int info;
	SQ* prox;
};



static SQ* push( SQ* stack, int info )
{
	SQ* novo = ( SQ* ) malloc( sizeof( SQ ) );
	assert( novo );

	novo->info = info;
	novo->prox = stack;

	return novo;
}



static SQ* queue( SQ* queue, int info )
{
	SQ* novo = ( SQ* ) malloc( sizeof( SQ ) );
	SQ* aux = queue;
	assert( novo );

	novo->info = info;
	novo->prox = NULL;

	if( ! queue )
	{
		return novo;
	}

	while( aux->prox )
	{
		aux = aux->prox;
	}

	aux->prox = novo;

	return queue;
}



static SQ* pop( SQ* stack, int* popped_info )
{
	SQ* libera;

	if( ! stack )
	{
		*popped_info = -1;
		return NULL;
	}

	*popped_info = stack->info;
	libera = stack;

	stack = stack->prox;
	free( libera );

	return stack;
}



static int isEmpty( SQ *list )
{
	return list == NULL;
}



static Viz* criaViz( Viz* head, int noj, float peso )
{
	Viz* no = ( Viz* ) malloc( sizeof( Viz ) );
	assert( no );

	no->noj = noj;
	no->peso = peso;
	no->prox = head;

	return no;
}



/* implemente */
Grafo* grafoCria( int nv, int na, int orientado ) 
{
	int i;
	Grafo* g = ( Grafo* ) malloc( sizeof( Grafo ) );
	assert( g );

	g->orientado = orientado;
	g->nv = nv;
	g->na = na;
	g->viz = ( Viz** ) malloc( nv * sizeof( Viz* ) );
	assert( g->viz );

	for( i = 0; i < nv; i++ )
	{
		g->viz[i] = NULL;
	}

	return g;
}



Grafo* grafoLe( char* filename ) 
{
	int nv, na, orientacao, no1, no2, i = 0;
	float peso;
	Grafo* novo;

	FILE *arq = fopen( filename, "rt" );

	fscanf( arq, "%d %d %d", &nv, &na, &orientacao );
	novo = grafoCria( nv, na, orientacao );
	assert( novo );

	while( fscanf( arq, "%d %d %f", &no1, &no2, &peso ) == 3 )
	{
		novo->viz[no1] = criaViz( novo->viz[no1], no2, peso );
		if( ! orientacao )
		{
			novo->viz[no2] = criaViz( novo->viz[no2], no1, peso );
		}
	}

	return novo;
}



Grafo* grafoLibera( Grafo* grafo ) 
{
	if( grafo )
	{
		int i = 0;
		Viz* no, *aux;

		for( i = 0; i < grafo->nv; i++ )
		{
			no = grafo->viz[i];
			while( no )
			{
				aux = no->prox;
				free( no );
				no = aux;
			}
		}

		free( grafo->viz );
		free( grafo );
	}

	return NULL;
}



void grafoMostra( char* title, Grafo * grafo ) 
{
	int i;
	if( title )
	{
		printf("%s", title);
	}

	if( grafo )
	{
		printf( "NV: %d, NA: %d, %s\n", grafo->nv, grafo->na, ( grafo->orientado != 0 ? "orientado" : "nao orientado" ) );
		for( i = 0; i < grafo->nv; i++ )
		{
			Viz* viz = grafo->viz[i];
			printf( "[%d]->", i );
			while( viz )
			{
				printf( "{%d, %g}->", viz->noj, viz->peso );
				viz = viz->prox;
			}
			printf( "NULL\n" );
		}
	}
}



void dfs( Grafo *grafo, int no, int *v )
{
	int i = 0;
	Viz* viz;

	printf( " %d ", no );

	v[no] = VISITED;
	viz = grafo->viz[no];
	for( ; viz != NULL; viz = viz->prox )
	{
		if( ! v[ viz->noj ] )
		{
			dfs( grafo, viz->noj, v );
		}
	}
}



void grafoPercorreProfundidade( Grafo * grafo, int no_inicial )
{
	int i;
	int *v;

	if( ! grafo )
	{
		return;
	}

	v = ( int* ) malloc( grafo->nv * sizeof( int ) );
	for( i = 0; i < grafo->nv; i++ )
	{
		v[i] = UNVISITED;
	}

	dfs( grafo, no_inicial, v );

	printf( "\n" );
}



void grafoPercorreLargura( Grafo * grafo, int no_inicial )
{
	SQ *lst = NULL;
	Viz *viz;

	int  i;
	int value;
	int *visitado;

	if( ! grafo )
	{
		return;
	}

	visitado = ( int* ) malloc( grafo->nv * sizeof( int ) );
	for( i = 0; i < grafo->nv; i++ )
	{
		visitado[i] = UNVISITED;
	}

	visitado[no_inicial] = VISITED;
	lst = push( lst, no_inicial );

	while( ! isEmpty( lst ) )
	{
		lst = pop( lst, &value );

		printf( "%d ", value );

		viz = grafo->viz[value];
		for( ; viz != NULL; viz = viz->prox )
		{
			if( ! visitado[ viz->noj ] )
			{
				visitado[ viz->noj ] = VISITED;
				lst = queue( lst, viz->noj );
			}
		}
	}

	printf( "\n" );
}



void grafoMostraDijkstra( Grafo* grafo, int source )
{
	SQ *lst = NULL;
	int node;

	Viz* viz;

	int i;
	int *dist;

	if( ! grafo )
	{
		return;
	}

	dist = ( int* ) malloc( grafo->nv * sizeof( int ) );
	for( i = 0; i < grafo->nv; i++ )
	{
		dist[i] = INFINITY;
	}

	dist[source] = 0;
	lst = push( lst, source );

	while( ! isEmpty( lst ) )
	{
		
		lst = pop( lst, &node );

		viz = grafo->viz[node];
		for( ; viz != NULL; viz = viz->prox )
		{
			if( dist[ viz->noj ] == INFINITY || dist[ viz->noj ] > viz->peso + dist[node] )
			{
				dist[ viz->noj ] = viz->peso + dist[node];
				lst = queue( lst, viz->noj );
			}
		}
	}

	for( i = 0; i < grafo->nv; i++ )
	{
		printf( "%d ", dist[i] );
	}

	printf( "\n" );
}



void grafoMostraKruskal( Grafo* grafo )
{
	DSet *dset = dsCreate( grafo->nv );
	Viz *viz;
	Viz *oldViz;

	int i;
	int src;
	int dest;
	int cost;

	while( dsNSets( dset ) > 1 )
	{
		oldViz = *grafo->viz;

		for( i = 0, cost = INT_MAX; i < grafo->nv; i++ )
		{
			viz = grafo->viz[i];
			
			while( viz )
			{
				if( viz->peso < cost )
				{
					if( grafo->orientado || ( dsFind( dset, i ) != dsFind( dset, viz->noj ) ) )
					{
						src = i;
						dest = viz->noj;
						cost = viz->peso;
						oldViz = viz;
					}
				}

				viz = viz->prox;
			}
		}

		if( dsUnion( dset, src, dest ) )
		{
			printf( "Aresta -> { %d, %d, %d }\n", src, dest, cost );
		}

		oldViz->peso = INT_MAX;
	}
}