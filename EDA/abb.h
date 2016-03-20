typedef struct _abb Abb;

Abb* abb_cria(void);

/* Insere a informacao na ordem correta */
Abb* abb_insere(Abb* raiz,float info);

/* imprime a estrutura da abb */
void abb_mostra_arvore(char* titulo, Abb* raiz);

/* Retorna um ponteiro para o no que tem a informacao. */
Abb* abb_busca(Abb* raiz, float info);

/* Retorna a informacao de um nó */
float abb_info(Abb* no);

/* imprime as informacoes que estao nos nós da abb em ordem */
void abb_mostra_ordem(char* titulo, Abb* raiz);

/* testa se algum nó da abb esta errado */
int abb_testa(Abb* raiz);

/* Desaloca todos os nós da arvore */
Abb* abb_libera(Abb* a);

/* Retira o nó que tem esta informacao */
Abb* abb_retira(Abb* raiz, float info);

/* Retorna um ponteiro para o menor elemento da arvore */
Abb* abb_min (Abb* raiz);

/* Retorna um ponteiro para o sucessor do nó dado */
Abb* abb_prox(Abb* no);