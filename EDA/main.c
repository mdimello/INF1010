#include <stdio.h>
#include "heap.h"


int main(void) {
    int i,n=8;
	float info;
	float v[]={25, 48, 37, 48, 57, 86, 33, 92};
	float vMax[]={25, 48, 37, 48, 57, 86, 33, 92};
	float vSort[] = {92,57, 86, 48, 25, 37, 33, 48 };
	Heap* heap = heap_cria(8);
	Heap* max_heap = heap_monta( n, vMax );

	heap_show( max_heap, "max heap=");

	heap_sort( n, vSort );
	printf( "heap sort = {" );
	for( i = 0; i <  n; i++ )
	{
		printf( " %.0f,", vSort[i] );
	}
	printf( " }\n" );

	for (i=0;i<n;i++) {
		heap_insere(heap,v[i]);
		printf("insere %g, ", v[i]);
		heap_show(heap, "heap=");
	}

	do{
		info = heap_remove(heap);
		printf("remove %g ", info);
		heap_show(heap, "heap=");
	}   while(info>0);

	heap=heap_libera(heap);
	return 0;
}