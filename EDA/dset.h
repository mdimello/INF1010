typedef struct _dset DSet ;

/* Cria uma particao dinamica (Dynamic Set) com n elementos dijuntos: 0,1,..,n-1. */
DSet* dsCreate (int n);

/* faz a uniao dos sets que contem os elementos 1 e 2 */
int dsUnion(DSet* dset, int elem1, int elem2);

/* acha o representante do elemento */
int dsFind (DSet* dset, int elem);

/* calcula qo numero de conjuntos dijuntos */
int dsNSets(DSet* dset);

/* mostra */
void dsShow (char* title, DSet* dset);