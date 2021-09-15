//Eduardo Tristao - 4219 / Marcus Vinicius - 4240 / Luis Henrique - 4254

#include <stdio.h>
#include <stdlib.h>
#include "listaencadeada.h"

//inicia uma lista vazia
void iniciaLista(Lista * lista)
{
    lista->celPrim = (tipoCel*) malloc(sizeof(tipoCel));
    lista->celPrim->pProx = NULL;
}

//incrementa uma tupla com o id do documento especificado, ou caso ele nao esteja na lista, cria uma celula com esse id e quantidade 1
//os documentos ja sao inseridos ordenados com base no id
void aumenText(Lista * lista, int idDoc){
    tipoCel * celAux = lista->celPrim->pProx;
    if (celAux != NULL){
        while (1){
            if (celAux->tupla[1] == idDoc){
                celAux->tupla[0] += 1;
                return;
            }
            else {
                if (celAux->pProx != NULL && celAux->pProx->tupla[1] <= idDoc){
                    celAux = celAux->pProx;
                }
                else{
                    break;
                }
            }
        }
        tipoCel * celulaInserir = (tipoCel*) malloc(sizeof(tipoCel));
        celulaInserir->tupla[1] = idDoc;
        celulaInserir->tupla[0] = 1;
        celulaInserir->pProx = celAux->pProx;
        celAux->pProx = celulaInserir;
    }
    else{
        tipoCel * celulaInserir = (tipoCel*) malloc(sizeof(tipoCel));
        celulaInserir->tupla[1] = idDoc;
        celulaInserir->tupla[0] = 1;
        celulaInserir->pProx = NULL;
        lista->celPrim->pProx = celulaInserir;
    }
}

//retorna uma tupla especificada pelo id do documento que ela aparece
int * retornaTupla(Lista lista, int idDoc){
    tipoCel * celAux = lista.celPrim->pProx;
    while (celAux != NULL && idDoc != celAux->tupla[1]) {
        celAux = celAux->pProx;
    }
    if (celAux == NULL) {
        int * tupla = (int*) malloc(sizeof(int)*2);
        tupla[0] = -1; tupla[1] = -1;
        return tupla;
    }
    if (idDoc == celAux->tupla[1]) return celAux->tupla;
}

//retorna o tamanho da lista
int tamanho(Lista lista){
    tipoCel * celAux = lista.celPrim->pProx;
    int tam = 0;
    while (celAux != NULL) {
        tam++;
        celAux = celAux->pProx;
    }
    return tam;
}

//retorna 1 se a lista possui o documento especificado e 0 caso nao
int possuiDoc(Lista lista, int idDoc){
    tipoCel * celAux = lista.celPrim->pProx;
    while (celAux != NULL) {
        if (celAux->tupla[1] == idDoc) return 1;
        celAux = celAux->pProx;
    }
    return 0;
}

//imprime as tuplas da lista
void imprimeLista(Lista lista){
    tipoCel * celAux = lista.celPrim->pProx;
    while (celAux != NULL){
        printf("<%d,%d>",celAux->tupla[0],celAux->tupla[1]);
        celAux = celAux->pProx;
    }
    printf("\n");
}
