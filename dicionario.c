//Eduardo Tristao - 4219 / Marcus Vinicius - 4240 / Luis Henrique - 4254

#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista2* cria_lista(){
    Lista2 *li;
    li = (Lista2*) malloc(sizeof(struct lista2));
    li->dados[0].ver = 0;
    if(li!=NULL)
        li->qntd=0;
    return li;
}
int lista_cheia(Lista2 *li){
    if(li == NULL)
        return -1;
    return (li->qntd == 5);
}
void libera_lista(Lista2 *li){
    free(li);
}
void insere_lista(Lista2 *li, char nome[50]){
    if(lista_cheia(li))
        return;
    li->dados[0].ver =1;
    strcpy(li->dados[li->qntd].palavra, nome);
    li->qntd++;
    return;
}
char *atravessa_lista(Lista2 *li){
    int n;
    if(li->dados[0].ver != 1) {
        printf("nenhum resultado encontrado\n");
        return NULL;
    }
    else {
        printf("Voce quis dizer: \n");
        printf("0 - Quero dizer a minha palavra mesmo\n");
        for (int i = 1; i < li->qntd; i++) {
            printf("%d- %s \n", i , li->dados[i].palavra);
        }
        scanf("%d", &n);
        if(n != 0)
            return li->dados[n].palavra;
        else{
            return NULL;
        }
    }
}
struct Node* newNode(char data){
    struct Node* temp = (struct Node*) malloc(sizeof( struct Node ));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}
void insere_tst(struct Node** root, char *word){
    if (!(*root))
        *root = newNode(*word);
    if ((*word) < (*root)->data)
        insere_tst(&( (*root)->left ), word);
    else if ((*word) > (*root)->data)
        insere_tst(&( (*root)->right ), word);
    else
    {
        if (*(word+1))
            insere_tst(&( (*root)->eq ), word+1);
        else
            (*root)->isEndOfString = 1;
    }
}
void traverseTSTUtil(struct Node* root, char* buffer, int depth)
{
    if (root)
    {
        traverseTSTUtil(root->left, buffer, depth);
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }
        traverseTSTUtil(root->eq, buffer, depth + 1);
        traverseTSTUtil(root->right, buffer, depth);
    }
}

void imprimteTST(struct Node* root)
{
    char buffer[50];
    traverseTSTUtil(root, buffer, 0);
}

//funcao que atravessa as subarvores de uma dada raiz e insere as palavras em uma lista estática
Lista2 *atravessa_tst(struct Node* root, char* buffer, int depth,Lista2 *li, char nova_palavra[50]) {
    if (root) {
        buffer[depth] = root->data;
        atravessa_tst(root->left, buffer, depth,li,nova_palavra);
        if (root->isEndOfString) {
            char palavraaux[50];
            //copia a palavra original para um char axuliar
            strcpy(palavraaux, nova_palavra);
            buffer[depth + 1] = '\0';
            nova_palavra[strlen(nova_palavra)-1] = '\0';
            //junta o buffer com a palavra original para inserir na lista
            strcat(nova_palavra, buffer);
            insere_lista(li, nova_palavra);
            //a palavra original volta a ser ela mesma
            strcpy(nova_palavra, palavraaux);
        }
        atravessa_tst(root->eq, buffer, depth + 1,li,nova_palavra);
        atravessa_tst(root->right, buffer, depth,li,nova_palavra);
        return li;
    }
}
//funcao para achar a raiz da palavra
struct Node* searchTST(struct Node *root, char *word){
    //se a palavra nao estiver no dicionario retorna null para tratamento
    if (!root) {
        return NULL;
    }
    if (*word < (root)->data)
        return searchTST(root->left, word);
    else if (*word > (root)->data)
        return searchTST(root->right, word);
    else
    {
        if (*(word+1) == '\0')
            //retorna a raiz da palavra para a traverse
                return root;
        }
        return searchTST(root->eq, word+1);
}

char ** auto_complete(struct Node* root, char fpalavra[50]){
    //inicia o buffer,as palavras que serao utilizadas e a estrutura da lista
    char buffer[50];
    Lista2 *li;
    char palavra[50];
    //cria um ponteiro de char para array de char e os auxiliares para guardarem a palavra original
    char *resultado = palavra, *teste, *resultadoaux, palavraaux[50];
    //resultado = fpalavra;
    strcpy(resultado,fpalavra);
    strcpy(palavra, resultado);
    strcpy(palavraaux, palavra);
    resultadoaux = palavraaux;
    li = cria_lista();
    //se a palavra nao estiver no dicionario ele reduz ela ate achar alguma
    while(searchTST(root, palavra) == NULL){
        palavra[strlen(palavra)-1] = '\0';
    }
    //acha a raiz, as subarvores e insere elas na lista
    li = atravessa_tst((searchTST(root, resultado)), buffer, 0,li, resultado);
    /*teste= atravessa_lista(li);
    if(teste != NULL)
        strcpy(resultado, teste);
    if(teste == NULL)
        return resultadoaux;*/
    if (li->dados[0].ver != 1) return NULL;
    char ** sugestoes = (char**) malloc(sizeof(char*)*5);
    for (int i = 0; i < 5; i++) sugestoes[i] = (char*) malloc(sizeof(char)*50);
    for (int i = 0; i < 5; i++) strcpy(sugestoes[i], li->dados[i].palavra);
    libera_lista(li);
    return sugestoes;
}

