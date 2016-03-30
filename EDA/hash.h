#ifndef   INF1010_HASH_H_
#define   INF1010_HASH_H_ 

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _hash TabelaHash;

/* cria uma tabela hash de "tamanho"  */
TabelaHash* htCria(int tamanho);

/* insere uma palavra na tabela   */
void htInsere(TabelaHash* tabela, char* palavra);

/* busca uma palavra */
void* htBusca(TabelaHash* tabela, char* palavra);

/* libera a tabela */
TabelaHash* htLibera(TabelaHash* tabela);

/* retorna o numero de palavras distintas armazenadas */
int htNumeroPalavras(TabelaHash* tabela);

/* retorna o numero de colisoes na tabela hash*/
int htNumeroColisoes(TabelaHash* tabela);

/* escreve num arquivo csv (Excel) uma tabela em que cada linha contem 
 * indice da tabela hash; palavra; numero de ocorrencias;  */
void htSalvaCSV(TabelaHash* tabela, char* filename);


#ifdef __cplusplus
}
#endif

#endif