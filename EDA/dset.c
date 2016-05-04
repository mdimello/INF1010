#include <stdio.h>
#include <stdlib.h>
#include "dset.h"



struct _dset
{
	int  n;
	int* vet;
};



DSet* dsCreate (int n){
	int i;

	DSet* dset = ( DSet* ) malloc(     sizeof( DSet ) );
	dset->vet  =  ( int* ) malloc( n * sizeof( int  ) );

	dset->n = n;
	for( i = 0; i < n; i++ )
	{
		dset->vet[i] = -1;
	}
	return dset;
}



int dsFind( DSet* dset, int elem )
{
	int p;
	int r = elem;
	while( dset->vet[r] >= 0 )
	{
		r = dset->vet[r];
	}

	while( dset->vet[elem] >= 0 )
	{
		p = dset->vet[elem];
		dset->vet[elem] = r;
		elem = p;
	}

	return r;
}



int dsUnion( DSet* dset, int elem1, int elem2 ) 
{
	elem1 = dsFind( dset, elem1 );
	elem2 = dsFind( dset, elem2 );

	if( elem1 == elem2 )
	{
		return elem1;
	}

	if( dset->vet[elem1] <= dset->vet[elem2] )
	{
		dset->vet[elem1] += dset->vet[elem2];
		dset->vet[elem2] = elem1;
		return elem1;
	}
	else
	{
		dset->vet[elem2] += dset->vet[elem1];
		dset->vet[elem1] = elem2;
		return elem2;
	}
}



int dsNSets( DSet* dset ) 
{
	int i;
	int count = 0;

	for( i = 0; i < dset->n; i++ )
	{
		if( dset->vet[i] < 0 )
		{
			count++;
		}
	}

	return count;
}



void dsShow( char* title, DSet* dset )
{
	int i;
	printf( "%s", title );
	for( i = 0; i < dset-> n; i++ )
	{
		printf("%d ",dset->vet[i]);
	}

	printf("\n");
}