/* Trablho 3: OBRIGATORIO e vale 20% da nota do P3 */
/* Entrega na 4a feira, dia 25.  */

/* implemente o arquivo grafo.c cuja interface e':  */

typedef struct _grafo Grafo;

Grafo*   grafoCria(int nv, int na, int orientado);
Grafo*   grafoLe( char* filename );
Grafo*   grafoLibera(Grafo* grafo);
void     grafoMostra(char* title, Grafo* grafo);
void     grafoPercorreProfundidade(Grafo * grafo, int no_inicial);
void     grafoPercorreLargura(Grafo * grafo, int no_inicial);
void     grafoMostraDijkstra(Grafo* grafo, int no_origem);
void     grafoMostraKruskal(Grafo* grafo);

/* formato do arquivo de teste.  grafo  
6       ! numero de nos 
5       ! numero de arestas 
0 | 1   ! 0 = nao dirigido
0 1 20  ! aresta:  noi noj peso 
1 2 30  
1 3 25
3 4 15
4 5 10
*/
