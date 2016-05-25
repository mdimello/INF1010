#include <stdlib.h>
#include <stdio.h>
#include "list.h"



typedef struct _node Node;



struct _node
{
	Type info;
	Node* next;
};



struct _list
{
	Node* first;
	Node* last;
	Node* curr;
};



List* lstCreate( void )
{
	List* list = ( List* ) malloc( sizeof( List ) );
	if( list != NULL )
	{
		list->first = NULL;
		list->last  = NULL;
		list->curr  = NULL;
	}

	return list;
}



List* lstDestroy( List* list )
{
	while( list->first )
	{
		Node* aux = list->first;
		list->first = list->first->next;
		free( aux );
	}

	list->first = NULL;
	list->last  = NULL;
	list->curr  = NULL;

	free( list );
	list = NULL;

	return list;
}



/*
 * @return - error code: 0 = no error; 1 = allocation error; 2 = list not created;
 */
int lstPush( List* list, Type info )
{
	if( list )
	{
		Node* node = ( Node* ) malloc( sizeof( Node ) );
		if( node )
		{
			node->info  = info;
			node->next  = list->first;
			list->first = node;
			if( ! list->last )
			{
				list->last = node;
			}

			return 0;
		}
	
		return 1;
	}

	return 2;
}



/*
 * @return - error code: 0 = no error; 1 = allocation error; 2 = list not created;
 */
int lstQueue( List* list, Type info )
{
	if( list )
	{
		Node* node = ( Node* ) malloc( sizeof( Node ) );
		if( node )
		{
			node->info  = info;
			node->next  = NULL;

			if( ! list->first )
			{
				list->first = node;
			}
			if( list->last )
			{
				list->last->next = node;
			}

			list->last = node;
		

			return 0;
		}
	
		return 1;
	}

	return 2;
}



/*
 * @return error code: 0 = no error; 1 = empty list; 2 = list not created;
 */
int lstPop( List* list, Type* info )
{
	if( list )
	{
		if( list->first )
		{
			Node* aux  = list->first;
			*info      = aux->info;

			list->first = list->first->next;
			
			free( aux );

			return 0;
		}
	
		return 1;
	}

	return 2;
}



/*
 * @return code: 0 = false; 1 = true; 2 = list not created;
 */
int lstIsEmpty( List* list )
{
	if( list )
	{
		if( list->first )
		{
			return 0;
		}

		return 1;
	}

	return 2;
}



/*
 * @return - error code: 0 = no error; 1 = empty list; 2 = list not created;
 */
int lstPointToFirst( List* list )
{
	if( list )
	{
		if( list->first )
		{
			list->curr = list->first;

			return 0;
		}

		return 1;
	}

	return 2;
}



/*
 * @return - error code: 0 = no error; 1 = empty list; 2 = list not created;
 */
int lstPointToNext( List* list )
{
	if( list )
	{
		if( list->first && list->curr->next )
		{
			list->curr = list->curr->next;

			return 0;
		}

		return 1;
	}

	return 2;
}



/*
 * @return - error code: 0 = no error; 1 = empty list; 2 = list not created;
 */
int lstGetCurrent( List* list, Type* info )  
{
	if( list )
	{
		if( list->first )
		{
			*info = list->curr->info;

			return 0;
		}

		return 1;
	}

	return 2;
}



int lstPrint( List* list )
{
	int code;

	if( lstIsEmpty( list ) == 1 )
	{
		printf( "Lista Vazia.\n" );
		return;
	}
	else if( lstIsEmpty( list ) == 2 )
	{
		printf( "Lista nao criada.\n" );
		return;
	}

	code = lstPointToFirst( list );
	while( code == 0 )
	{
		Type value;
		lstGetCurrent( list, &value );
		printf( "%d\n", value );

		code = lstPointToNext( list );
	}
}