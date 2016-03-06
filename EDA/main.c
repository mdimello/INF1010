#include <stdlib.h>
#include <stdio.h>
#include "myList.h"


void printList( List* list )
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


int main( void )
{
	List* list = lstCreate( );
	int value;
	int code;

	printList( list );
	lstQueue( list, 2 );
	lstQueue( list, 3 );
	lstQueue( list, 4 );
	lstPush( list, 1 );
	printList( list );
	code = lstPop( list, &value );
	if( code == 0 )
		printf( "Pop: %d\n", value );

	
	list = lstDestroy( list );
	printList( NULL );

	system("pause");
	return 0;
}