//Eduardo Tristao - 4219 / Marcus Vinicius - 4240 / Luis Henrique - 4254

#include "indice_invertido.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

struct No* NovoNo(char palavra){
    struct No* temp = (struct No*) malloc(sizeof( struct No ));
    temp->palavra = palavra;
    temp->fim = 0;
    temp->esq = temp->meio = temp->dir = NULL;
    return temp;
}

void insere(struct No** raiz, char *palavra, int id){
    int j = 1;
    if (!(*raiz))
        *raiz = NovoNo(*palavra);
    if ((*palavra) < (*raiz)->palavra)
        insere(&( (*raiz)->esq ), palavra, id);
    else if ((*palavra) > (*raiz)->palavra)
        insere(&( (*raiz)->dir ), palavra, id);
    else
    {
        if (*(palavra+1))
            insere(&((*raiz)->meio), palavra+1, id);
        else {
            //se a palavra já existe na arvore ele soma mais um na quantidade
            //e tambem prepara o proximo indice pra receber mais um id
            if(pesquisaTST(*raiz, palavra) == 1){
                (*raiz)->qntd[id] += 1;
                (*raiz)->id_doc[id] = id;
                return;
            }
                //se a palavra ainda não existe ele cria adiciona a quantidade da palavra no indice id
                //e tambem prepara o proximo indice pra receber mais um id
            else{
                for(j ; j<MAX ; j++){
                    (*raiz)->qntd[j] = 0;
                    (*raiz)->id_doc[j] = 0;
                }
                (*raiz)->qntd[id] = 1;
                (*raiz)->id_doc[id] = id;
                (*raiz)->fim = 1;
            }
        }
    }
}

//a funcao recursiva pra atravessar a tst
void AtravessaTSTUtil(struct No* raiz, char* buffer, int profundidade){
    if (raiz)
    {

        AtravessaTSTUtil(raiz->esq, buffer, profundidade);

        //guarda a palavra em buffer
        buffer[profundidade] = raiz->palavra;
        if (raiz->fim)
        {
            buffer[profundidade+1] = '\0';
            int i = 0;
            int j = 0;
            printf( "%s: ", buffer);
            for (i; i<5; i++){
                if(raiz->qntd[i]==0)
                    continue;
                else
                    printf("qntd = %d id = %d || ", raiz->qntd[i], raiz->id_doc[i]);
            }
            printf("\n");
        }
        AtravessaTSTUtil(raiz->meio, buffer, profundidade + 1);
        AtravessaTSTUtil(raiz->dir, buffer, profundidade);
    }
}

void atravessaTST(struct No* raiz){
    char buffer[MAX];
    AtravessaTSTUtil(raiz, buffer, 0);
}

int pesquisaTST(struct No *raiz, char *palavra)
{
    if (!raiz)
        return 0;

    if (*palavra < (raiz)->palavra)
        return pesquisaTST(raiz->esq, palavra);

    else if (*palavra > (raiz)->palavra)
        return pesquisaTST(raiz->dir, palavra);

    else
    {
        if (*(palavra+1) == '\0')
            return raiz->fim;

        return pesquisaTST(raiz->meio, palavra+1);
    }
}
