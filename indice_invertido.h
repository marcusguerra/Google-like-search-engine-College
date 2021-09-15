//Eduardo Tristao - 4219 / Marcus Vinicius - 4240 / Luis Henrique - 4254

struct No{
    char palavra;
    int qntd[50];
    int id_doc[50];
    unsigned fim: 1;
    struct No *esq, *meio, *dir;
};

struct No* NovoNo(char palavra);
void insere(struct No** raiz, char *palavra, int id);
void AtravessaTSTUtil(struct No* raiz, char* buffer, int profundidade);
void atravessaTST(struct No* raiz);
int pesquisaTST(struct No *raiz, char *palavra);
