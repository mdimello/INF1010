#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "dset.h"

void testeSet( )
{
	Set* s1 = setCreate(24);
	Set* s2 = setCreate(24);
	Set *uniao, *intersecao, *diferenca;
	int i;
	
	setInsert(s1, 10); 	setInsert(s1, 15); 	setInsert(s1, 20);
	//setInsert(s1, 80); 	setInsert(s1, 90); 	setInsert(s1, 100);
	setShow("s1", s1);
	setRemove(s1, 20);
	setShow("s1 remove 20", s1);

	setInsert(s2, 15); 	setInsert(s2, 20); 	//setInsert(s2, 40);
	//setInsert(s2, 90); 	setInsert(s2, 120); 	setInsert(s2, 150);
	setShow("s2", s2);
	
	uniao = setUnion(s1, s2);  
	setShow("s1Us2", uniao);
	
	intersecao = setIntersection(s1, s2);   
	setShow("s1Is2", intersecao);
	
	diferenca = setDifference(s2, s1);   
	setShow("s2-s1", diferenca);

	s1 = setDestroy(s1);
	s2 = setDestroy(s1);
	uniao = setDestroy(uniao);
	intersecao = setDestroy(intersecao);
	diferenca = setDestroy(diferenca);
}

void testeDSet( )
{
	DSet* dset = dsCreate(6);
	dsUnion (dset,0,1);
	dsUnion (dset,2,4);
	dsUnion (dset,4,5);
	dsUnion (dset,5,3);
	dsUnion (dset,3,2);

	printf("numero de conjuntos dijuntos = %d\n",dsNSets(dset));
	dsShow("Particao\n",dset);
}

int main()
{
	testeSet( );

	//testeDSet( );

	return 0;
}