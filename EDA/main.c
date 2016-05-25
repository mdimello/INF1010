#include <stdio.h>
#include "grafo.h"
 
int main( )
{
    Grafo* g = grafoLe( "grafo1.dat" );
	grafoMostra( "Grafo dado: ", g );
	printf("Percorrimento em largura: ");
	grafoPercorreLargura( g, 0 );
	printf("Percorrimento em profundidade: ");
	grafoPercorreProfundidade( g, 0 );
	grafoMostraDijkstra( g, 0 );
	printf( "\n" );
	grafoMostraKruskal( g );
	printf( "\n" );
	g = grafoLibera( g );

    return 0;
}