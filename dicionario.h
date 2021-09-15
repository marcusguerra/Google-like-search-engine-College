//Eduardo Tristao - 4219 / Marcus Vinicius - 4240 / Luis Henrique - 4254

#ifndef TPAEDS2_DICIONARIO_H
#define TPAEDS2_DICIONARIO_H

#define MAXN 50

//para deixa o programa mais organizado usamos uma lista dinamica para armazenar as palavras vindas das subarvores
struct nome{
    //um verificador mostrando se a lista esta vazia ou nao
    int ver;
    char palavra[50];
};
typedef struct lista2 Lista2;

//deixamos so com 5 indices para nao ter um numero excessivo de palavras recomendadas
struct lista2{
    int qntd;
    struct nome dados[5];
};
Lista2* cria_lista();
void libera_lista(Lista2 *li);
void insere_lista(Lista2 *li,char nome[50]);
char * atravessa_lista(Lista2 *li);
int lista_cheia(Lista2 *li);

//codigo da tst adaptado do site: https://www.geeksforgeeks.org/ternary-search-tree/
struct Node{
    char data;
    unsigned isEndOfString: 1;
    struct Node *left, *eq, *right;
};

struct Node* newNode(char data);
void insere_tst(struct Node** root, char *word);
Lista2 *atravessa_tst(struct Node* root, char* buffer, int depth, Lista2 *li, char word[50]);
char ** auto_complete(struct Node* root, char fpalavra[50]);
struct Node* searchTST(struct Node *root, char *word);
void imprimteTST(struct Node* root);
void traverseTSTUtil(struct Node* root, char* buffer, int depth);


#endif //TPAEDS2_DICIONARIO_H
