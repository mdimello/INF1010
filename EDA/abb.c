#include <stdio.h>
#include <stdlib.h>

#include "abb.h"



struct _abb 
{
   float info;
   Abb* pai;
   Abb* esq;
   Abb* dir;
};



Abb* abb_cria( void ) 
{
	return NULL;
}



static Abb* abb_create_node( Abb* father, float info )
{
	Abb* node = ( Abb* ) malloc( sizeof( Abb ) );
	node->info = info;
	node->esq  = NULL;
	node->dir  = NULL;

	node->pai  = father;

	return node;
}



Abb* abb_insere( Abb* r, float info )
{
	if( r == NULL )
		return abb_create_node( r, info );
	else if( r->info > info )
	{
		if( r->esq != NULL )
			r->esq = abb_insere( r->esq, info );
		else
			r->esq = abb_create_node( r, info );
	}
	else if( r->info < info )
	{
		if( r->dir != NULL )
			r->dir = abb_insere( r->dir, info );
		else
			r->dir = abb_create_node( r, info );
	}

	return r;
}

void abb_mostra_arvore( char* titulo, Abb* raiz )
{
	if( raiz == NULL )
	{
		printf( " . " );
		return;
	}

	if( raiz->pai == NULL )
		printf( "%s", titulo );
	
	printf( " < " );
	printf( "%.0f", raiz->info );
	abb_mostra_arvore( titulo, raiz->esq );
	abb_mostra_arvore( titulo, raiz->dir );

	printf( " > " );
}

Abb* abb_busca( Abb* r, float info )
{
	if( ! r )
	{
		return NULL;
	}

	else if( r->info > info )
	{
		return abb_busca( r->esq, info );
	}
	else if( r->info < info )
	{
		return abb_busca( r->dir, info );
	}
	else
		return r;
}

float abb_info( Abb* no ) 
{
	return no->info;
}

void abb_mostra_ordem( char* titulo, Abb* raiz )
{
	if( ! raiz )
	{
		return;
	}

	if( ! raiz->pai )
	{
		printf( "%s", titulo );
	}
	
	abb_mostra_ordem( titulo, raiz->esq );
	printf( "%.0f, ", raiz->info );
	abb_mostra_ordem( titulo, raiz->dir );
}

Abb* abb_libera( Abb* a )
{
	if( a-> esq != NULL )
	{
		abb_libera( a->esq );
	}
	if( a->dir != NULL )
	{
		abb_libera( a->dir );
	}

	free( a );

	return NULL;
}


Abb* abb_retira( Abb* r, float info )
{
	if( r == NULL )
		return NULL;
	else if( r->info > info )
		r->esq = abb_retira( r->esq, info );
	else if( r->info < info )
		r->dir = abb_retira( r->dir, info );
	else
	{
		if( r->esq == NULL && r->dir == NULL )
		{
			free( r );
			r = NULL;
		}
		else if( r->esq == NULL )
		{
			Abb* t = r;
			r = r->dir; 
			r->pai = t->pai; 
			free( t );
		}
		else if( r->dir == NULL )
		{
			Abb* t = r;
			r = r->esq; 
			r->pai = t->pai; 
			free( t );
		}
		else
		{
			Abb *suc = r->dir;
			while( suc->esq != NULL )
				suc = suc->esq;

			r->info = suc->info;
			suc->info = info;

			if( suc->pai->esq == suc )
				suc->pai->esq = suc->dir;
			else
				suc->pai->dir = suc->dir;

			if( suc->dir != NULL )
				suc->dir->pai = suc->pai;

			free( suc );
		}
	}
	return r;
}


Abb* abb_min( Abb* r ) 
{
	if( r == NULL )
		return NULL;

	while( r->esq != NULL )
		r = r->esq;

	return r;
}

Abb* abb_prox( Abb* r ) 
{
	Abb* p;

	if( r == NULL )
		return NULL;
	else if( r->dir != NULL )
		return abb_min( r->dir );
	else
	{
		p = r->pai;
		while( p != NULL && r == p->dir )
		{
			r = p;
			p = p->pai;
		}

		return p;
	}

	return NULL;
}



static int respeita_ordem(Abb* r) 
{
	if( r == NULL )  
		return 1;
	else 
	{
		if( ( r->esq != NULL ) && ( r->info < r->esq->info ) ) 
			return 0;
		if( ( r->dir != NULL ) && ( r->info > r->dir->info ) ) 
			return 0;

		return respeita_ordem( r->esq ) && respeita_ordem( r->dir );
	}
}

static int respeita_pai(Abb* r) 
{
	if( r == NULL ) 
		return 1;
	else if( (r->esq != NULL && r->esq->pai != r) || ( r->dir != NULL && r->dir->pai != r ) ) 
		return 0;
	else 
		return respeita_pai( r->esq ) && respeita_pai( r->dir );
}

int abb_testa(Abb* r)
{
	return respeita_ordem( r ) && respeita_pai( r );
}