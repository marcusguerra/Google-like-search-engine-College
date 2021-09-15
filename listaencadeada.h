//Eduardo Tristao - 4219 / Marcus Vinicius - 4240 / Luis Henrique - 4254

//declaracao das estruturas necesarias para a lista encadeada de tuplas
typedef struct tipoCel{
    int tupla[2];
    struct tipoCel * pProx;
} tipoCel;

typedef struct Lista{
    tipoCel *celPrim;
} Lista;

void iniciaLista(Lista * lista);
void aumenText(Lista * lista, int idDoc);
void imprimeLista(Lista lista);
int * retornaTupla(Lista lista, int idDoc);
int tamanho(Lista lista);
int possuiDoc(Lista lista, int idDoc);
