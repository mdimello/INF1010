#include <stdlib.h>
#include <stdio.h>
#include "arvb23.h"

#define EMPTY -1

struct _arvb23
{
	/* chaves: kp<kg, se kg existir. Se kg = -1, significa que ele não existe. */
	int      kp;
	int      kg; 

	ArvB23  *pai;

	ArvB23  *esq;
	ArvB23  *mid;
	ArvB23  *dir;
};



static ArvB23* a23CriaNo( ArvB23* esq, ArvB23* mid, ArvB23* dir,int kp, int kg )
{
	ArvB23* no = ( ArvB23* ) malloc( sizeof( ArvB23 ) );

	no->kp = kp; 
	no->kg = kg;

	no->pai = NULL;

	no->esq = esq; 	
	no->mid = mid;
	no->dir = dir;

	if( no->esq )
	{
		no->esq->pai = no;
	}
	if( no->mid )
	{
		no->mid->pai = no;
	}
	if( no->dir )
	{
		no->dir->pai = no;
	}

	return no;
}



static void a23ReusaNo( ArvB23* no,  ArvB23* esq, ArvB23* mid, ArvB23* dir, int kp, int kg ) 
{
	no->kp = kp;
	no->kg = kg;

	no->esq = esq; 	
	no->mid = mid; 
	no->dir = dir;

	if( no->esq )  
	{
		no->esq->pai = no;
	}
	if( no->mid )
	{
		no->mid->pai = no;
	}
	if( no->dir )  
	{
		no->dir->pai = no;
	}
}




ArvB23* a23Cria( int chave )
{
	return a23CriaNo( NULL, NULL, NULL, chave, EMPTY );
}



ArvB23* a23Libera( ArvB23* raiz )
{
	if( raiz->esq != NULL )
	{
		a23Libera( raiz->esq );
	}

	if( raiz->mid != NULL )
	{
		a23Libera( raiz->mid );
	}

	if( raiz->dir != NULL )
	{
		a23Libera( raiz->dir );
	}

	free( raiz );

	return NULL;
}



ArvB23* a23Busca(ArvB23* raiz, int chave)
{
	if( raiz == NULL )
	{
		return NULL;
	}

	if( raiz->kp > chave )
	{
		return a23Busca( raiz->esq, chave );
	}
	else if( raiz->kp < chave )
	{
		if( raiz->kg == EMPTY )
		{
			return a23Busca( raiz->mid, chave );
		}
		else
		{
			if( raiz-> kg > chave )
			{
				return a23Busca( raiz->mid, chave );
			}
			else if( raiz-> kg < chave )
			{
				return a23Busca( raiz->dir, chave );
			}
			else
			{
				return raiz;
			}
		}
	}
	else
	{
		return raiz;
	}
}



static ArvB23* insereChave( ArvB23* no, int kn, ArvB23* menor, ArvB23* maior, ArvB23* raiz )
{
	if( no->kg == EMPTY )
	{
		if( kn < no->kp )
		{
			no->kg = no->kp;
			no->kp = kn;
			no->dir = no->mid;
			no->mid = maior;
			no->esq = menor;
			if( maior != NULL )
			{
				maior->pai = no;
			}

			if( menor != NULL )
			{
				menor->pai = no;
			}
		}
		else
		{
			no->kg = kn;
			no->dir = maior;
			no->mid = menor;
			if( maior != NULL )
			{
				maior->pai = no;
			}

			if( menor != NULL )
			{
				menor->pai = no;
			}
		}
	}
	else
	{
		if( kn < no->kp )
		{
			int chaveKp = no->kp;
			ArvB23* pai = no->pai;
			ArvB23* novo = a23CriaNo( no->mid, no->dir, NULL, no->kg, EMPTY );
			a23ReusaNo( no, menor, maior, NULL, kn, EMPTY );
			if( pai != NULL )
			{
				raiz = insereChave( pai, chaveKp, no, novo, raiz );
			}
			else
			{
				raiz = a23CriaNo( no, novo, NULL, chaveKp, EMPTY );
				no->pai = raiz;
				novo->pai = raiz;
			}
		}
		else if( kn < no->kg ) 
		{
			int chaveKp = kn;
			ArvB23* pai = no->pai;
			ArvB23* novo = a23CriaNo( maior, no->dir, NULL, no->kg, EMPTY );
			a23ReusaNo( no, no->esq, menor, NULL, no->kp, EMPTY );
			if( pai != NULL )
			{
				raiz = insereChave( pai, chaveKp, no, novo, raiz );
			}
			else
			{
				raiz = a23CriaNo( no, novo, NULL, chaveKp, EMPTY );
				no->pai = raiz;
				novo->pai = raiz;
			}
		}
		else 
		{
			int chaveKp = no->kg;
			ArvB23* pai = no->pai;
			ArvB23* novo = a23CriaNo( menor, maior, NULL, kn, EMPTY );
			a23ReusaNo( no, no->esq, no->mid, NULL, no->kp, EMPTY );
			if( pai != NULL )
			{
				raiz = insereChave( pai, chaveKp, no, novo, raiz );
			}
			else
			{
				raiz = a23CriaNo( no, novo, NULL, chaveKp, EMPTY );
				no->pai = raiz;
				novo->pai = raiz;
			}
		}
	}

	return raiz;
}



ArvB23* a23Insere( ArvB23* raiz, int chave )
{
	ArvB23* no = raiz;

	/* Desce ate o no correto, se a chave ja existir para. */
	while( no->esq != NULL ) 
	{
		if( chave == no->kp )
		{
			/* a chave ja esta na arvore */
			return raiz;
		}
		else if( chave < no->kp )
		{
			no = no->esq;
		}
		else if( no->kg == EMPTY ) 
		{
			no = no->mid;
		}
		else if( chave == no->kg )
		{
			/* a chave ja esta na arvore */
			return raiz;
		}
		else if( chave < no->kg ) 
		{
			/* no->kp < chave < no->kg  */
			no = no->mid;
		}
		else
		{
			/* chave > no->kg  */
			no = no->dir;
		}
	}

	if( no->kp == chave || no->kg == chave )
	{
		/* chave ja esta na arvore */
		return raiz;
	}

	raiz = insereChave( no, chave, NULL, NULL, raiz );

	return raiz;
}



static ArvB23* a23RemoveBuraco( ArvB23* no, ArvB23* filho, ArvB23* raiz )
{
	ArvB23* pai = no->pai;
	ArvB23* esq;
	ArvB23* mid;
	ArvB23* dir;

	if( no == raiz )
	{
		return filho;
	}

	esq = pai->esq;
	mid = pai->mid;
	dir = pai->dir;
	
	if( no->pai->kg == EMPTY )
	{
		/* pai tem 2 nos */
		if( no == esq )
		{
			/* no quebrado vem da esquerda */
			if( mid->kg == EMPTY )
			{
				/* irmao tem 2 nos */
				/* case 1 */
				a23ReusaNo( mid, filho, mid->esq, mid->mid, pai->kp, mid->kp );
				pai->kp  = EMPTY;

				raiz = a23RemoveBuraco( pai, mid, raiz );
			}
			else
			{
				/* irmao tem 3 nos */
				/* case 2 */
				a23ReusaNo( esq,    filho, mid->esq, NULL, pai->kp, EMPTY );
				a23ReusaNo( pai, pai->esq, pai->mid, NULL, mid->kp, EMPTY );
				a23ReusaNo( mid, mid->mid, mid->dir, NULL, mid->kg, EMPTY );
			}
		}
		else
		{
			/* no quebrado vem do meio */
			if( esq->kg == EMPTY )
			{
				/* irmao tem 2 nos */
				/* case 1 */
				a23ReusaNo( esq, esq->esq, esq->mid, filho, esq->kp, pai->kp );
				pai->kp  = EMPTY;

				raiz = a23RemoveBuraco( pai, esq, raiz );
			}
			else
			{
				/* irmao tem 3 nos */
				/* case 2 */
				a23ReusaNo( mid, esq->dir,    filho, NULL, pai->kp, EMPTY );
				a23ReusaNo( pai, pai->esq, pai->mid, NULL, esq->kg, EMPTY );
				a23ReusaNo( esq, esq->esq, esq->mid, NULL, esq->kp, EMPTY );
			}

		}
		
	}
	else
	{
		/* pai tem 3 nos */
		if( no == pai->esq )
		{
			/* no quebrado vem da esquerda */
			if( pai->mid->kg == EMPTY )
			{
				/* irmao tem 2 nos */
				/* case 3 */
				a23ReusaNo( mid, filho, mid->esq, mid->mid, pai->kp, mid->kp );
				a23ReusaNo( pai,   mid,      dir,     NULL, pai->kg,   EMPTY );
			}
			else
			{
				/* irmao tem 3 nos */
				a23ReusaNo( esq,    filho, mid->esq,     NULL, pai->kp,   EMPTY );
				a23ReusaNo( pai, pai->esq, pai->mid, pai->dir, mid->kp, pai->kg );
				a23ReusaNo( mid, mid->mid, mid->dir,     NULL, mid->kg,   EMPTY );
			}
		}
		else if( no == pai->dir )
		{
			/* no quebrado vem da direita */
			if( pai->mid->kg == EMPTY )
			{
				/* irmao tem 2 nos */
				/* case 3 */
				a23ReusaNo( mid, mid->esq, mid->mid, filho, mid->kp, pai->kg );
				a23ReusaNo( pai,      esq,      mid,  NULL, pai->kp,   EMPTY );
			}
			else
			{
				/* irmao tem 3 nos */
				a23ReusaNo( dir, mid->dir,    filho,     NULL, pai->kg,   EMPTY );
				a23ReusaNo( pai, pai->esq, pai->mid, pai->dir, pai->kp, mid->kg );
				a23ReusaNo( mid, mid->esq, mid->mid,     NULL, mid->kp,   EMPTY );
			}
		}
		else
		{
			/* no quebrado vem do meio */
			if( pai->dir->kg == EMPTY )
			{
				/* irmao tem 2 nos */
				/* case 3 */
				a23ReusaNo( dir, filho, dir->esq, dir->mid, pai->kg, dir->kp );
				a23ReusaNo( pai,   esq,      dir,     NULL, pai->kp,   EMPTY );
			}
			else
			{
				/* irmao tem 3 nos */
				a23ReusaNo( mid,    filho, dir->esq, NULL, pai->kg,   EMPTY );
				a23ReusaNo( pai,      esq,      mid,  dir, pai->kp, dir->kp );
				a23ReusaNo( dir, dir->mid, dir->dir, NULL, dir->kg,   EMPTY );
			}
		}
	}

	return raiz;
}



ArvB23* a23Retira( ArvB23* raiz, int chave )
{
	ArvB23* no = raiz;
	int aux;

	no = a23Busca( no, chave );

	if( no == NULL )
	{
		return raiz;
	}

	/* desce a chave a ser retirada ate uma folha */
	while( no->esq != NULL )
	{
		if( chave == no->kp )
		{
			aux = no->kp;
			no->kp = no->mid->kp;
			no->mid->kp = aux;

			no = no->mid;
		}
		else
		{
			aux = no->kg;
			no->kg = no->dir->kp;
			no->dir->kp = aux;

			no = no->dir;
		}
	}

	if( no->kg != EMPTY )
	{
		if( chave == no->kp )
		{
			no->kp = no->kg;
			no->kg = EMPTY;
		}
		else
		{
			no->kg = EMPTY;
		}
	}
	else
	{
		no->kp = EMPTY;
		raiz = a23RemoveBuraco( no, no->esq, raiz );
	}

	return raiz;
}



ArvB23* a23Mostra( char* titulo, ArvB23* raiz )
{
	if( titulo != NULL ) 
	{
		printf( "%s ", titulo );
	}

	if( raiz != NULL ) 
	{
		printf( "<" );
		printf( "%d ", raiz->kp );
		if ( raiz->kg == EMPTY ) 
		{
			printf( " - " );
		}
		else 
		{
			printf( "%d", raiz->kg );
		}

		a23Mostra( NULL, raiz->esq );
		a23Mostra( NULL, raiz->mid );
		a23Mostra( NULL, raiz->dir );

		printf( ">" );
	} 
	else
	{
		printf( " . " );
	}

	if ( titulo != NULL )
	{
		printf( "\n" );
	}

	return raiz;
}