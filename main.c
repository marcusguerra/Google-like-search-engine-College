//Eduardo Tristao - 4219 / Marcus Vinicius - 4240 / Luis Henrique - 4254

// inclusão de bibliotecas necessárias

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//inclusão dos TADs

#include "patricia.h"
#include "dicionario.h"
#include "indice_invertido.h"

// declaração dos elementos da janela

GtkWidget *janela;
GtkWidget *grade;
GtkWidget *bt_imprime_indice;
GtkWidget *bt_imprime_palavras;
GtkWidget *bt_busca_palavra;
GtkWidget *bt_limpa_palavra;
GtkWidget *bt_insere_arquivo;
GtkWidget *bt_insere_tst;
GtkWidget *bt_sugestao_1;
GtkWidget *bt_sugestao_2;
GtkWidget *bt_sugestao_3;
GtkWidget *bt_sugestao_4;
GtkWidget *bt_sugestao_5;
GtkWidget *texto1;
GtkWidget *texto2;
GtkWidget *texto3;
GtkWidget *texto4;
GtkWidget *texto5;
GtkWidget *texto6;
GtkWidget *texto7;
GtkWidget *entrada_palavra;
GtkWidget *insere_arq_texto;
GtkWidget *insere_arq_dic;
GtkWidget *spin_qt_termos;
GtkBuilder *builder;

//variaveis globais

int qntTextos = 0, *idDocs, qntTermos, termoAtual = 0;
TipoArvore arvore = NULL;
struct Node *root = NULL;
char ** termos;

int main(int argc, char *argv[]) {

gtk_init(&argc, &argv); //iniciando o gtk

builder = gtk_builder_new_from_file("TP01.glade"); //conexão com o arquivo .xml
janela = GTK_WIDGET(gtk_builder_get_object(builder, "janela")); //construção da janela
g_signal_connect(janela, "destroy", G_CALLBACK(gtk_main_quit), NULL); //botão fechar encerra o programa

//construção dos elementos da janela
gtk_builder_connect_signals(builder, NULL);
grade = GTK_WIDGET(gtk_builder_get_object(builder, "grade"));
bt_imprime_indice = GTK_WIDGET(gtk_builder_get_object(builder, "bt_imprime_indice"));
bt_imprime_palavras = GTK_WIDGET(gtk_builder_get_object(builder, "bt_imprime_palavras"));
bt_busca_palavra = GTK_WIDGET(gtk_builder_get_object(builder, "bt_busca_palavra"));
bt_limpa_palavra = GTK_WIDGET(gtk_builder_get_object(builder, "bt_limpa_palavra"));
bt_insere_arquivo = GTK_WIDGET(gtk_builder_get_object(builder, "bt_insere_arquivo"));
bt_sugestao_1 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_sugestao_1"));
bt_sugestao_2 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_sugestao_2"));
bt_sugestao_3 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_sugestao_3"));
bt_sugestao_4 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_sugestao_4"));
bt_sugestao_5 = GTK_WIDGET(gtk_builder_get_object(builder, "bt_sugestao_5"));
bt_insere_tst = GTK_WIDGET(gtk_builder_get_object(builder, "bt_insere_tst"));
texto1 = GTK_WIDGET(gtk_builder_get_object(builder, "texto1"));
texto2  = GTK_WIDGET(gtk_builder_get_object(builder, "texto2"));
texto3  = GTK_WIDGET(gtk_builder_get_object(builder, "texto3"));
texto4  = GTK_WIDGET(gtk_builder_get_object(builder, "texto4"));
texto5  = GTK_WIDGET(gtk_builder_get_object(builder, "texto5"));
texto6  = GTK_WIDGET(gtk_builder_get_object(builder, "texto6"));
entrada_palavra = GTK_WIDGET(gtk_builder_get_object(builder, "entrada_palavra"));
insere_arq_texto = GTK_WIDGET(gtk_builder_get_object(builder, "insere_arq_texto"));
insere_arq_dic = GTK_WIDGET(gtk_builder_get_object(builder, "insere_arq_dic"));
spin_qt_termos = GTK_WIDGET(gtk_builder_get_object(builder, "spin_qt_termos"));

gtk_widget_show(janela);
gtk_main();


return EXIT_SUCCESS;
}

//as funções das entradas são declaradas porem só são ativadas mediante acionamento do botão
void on_entrada_palavra_changed(GtkEntry *fEntrada) {}

void on_insere_arq_texto_file_set(GtkEntry *fArq) {}

void on_insere_arq_dic_file_set(GtkEntry *fArq) {}

//função de ativação dos botões de sugestão
void on_bt_sugestao_1_clicked(GtkButton *fBotao) {
    if (qntTermos > termoAtual+1){
        termoAtual += 1;
        
        //muda o label de cada botao para os primeiros 5 termos sugeridos
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_1), auto_complete(root, termos[termoAtual])[0]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_2), auto_complete(root, termos[termoAtual])[1]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_3), auto_complete(root, termos[termoAtual])[2]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_4), auto_complete(root, termos[termoAtual])[3]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_5), auto_complete(root, termos[termoAtual])[4]);}

    else{
        //criação do vetor com os ids dos arquivos
        int * ids = (int*) malloc(sizeof(int)*qntTextos);
        for (int m = 0; m < qntTextos; ++m){
            ids[m] = m+1;}
	
	//imprime os ids dos textos em ordem de relevancia
        printf("Resultado da Busca: \n");
        for (int i = 0; i < qntTextos; i++){printf("Texto de ID %d\n", buscaTexto(qntTextos, ids, qntTermos, termos, arvore)[i]);}
        free(ids);
    }
}

void on_bt_sugestao_2_clicked(GtkButton *fBotao) {
    if (qntTermos > termoAtual){
        termoAtual += 1;
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_1), auto_complete(root, termos[termoAtual])[0]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_2), auto_complete(root, termos[termoAtual])[1]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_3), auto_complete(root, termos[termoAtual])[2]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_4), auto_complete(root, termos[termoAtual])[3]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_5), auto_complete(root, termos[termoAtual])[4]);}

    else{
        //criação do vetor com os ids dos arquivos
        int * ids = (int*) malloc(sizeof(int)*qntTextos);
        for (int m = 0; m < qntTextos; ++m){
            ids[m] = m+1;}

        printf("Resultado da Busca: \n");
        for (int i = 0; i < qntTextos; i++){printf("Texto de ID %d\n", buscaTexto(qntTextos, ids, qntTermos, termos, arvore)[i]);}
        free(ids);
    }
}

void on_bt_sugestao_3_clicked(GtkButton *fBotao) {
    if (qntTermos > termoAtual){
        termoAtual += 1;
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_1), auto_complete(root, termos[termoAtual])[0]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_2), auto_complete(root, termos[termoAtual])[1]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_3), auto_complete(root, termos[termoAtual])[2]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_4), auto_complete(root, termos[termoAtual])[3]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_5), auto_complete(root, termos[termoAtual])[4]);}

    else{
        //criação do vetor com os ids dos arquivos
        int * ids = (int*) malloc(sizeof(int)*qntTextos);
        for (int m = 0; m < qntTextos; ++m){
            ids[m] = m+1;}

        printf("Resultado da Busca: \n");
        for (int i = 0; i < qntTextos; i++){printf("Texto de ID %d\n", buscaTexto(qntTextos, ids, qntTermos, termos, arvore)[i]);}
        free(ids);
    }
}

void on_bt_sugestao_4_clicked(GtkButton *fBotao) {
    if (qntTermos > termoAtual){
        termoAtual += 1;
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_1), auto_complete(root, termos[termoAtual])[0]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_2), auto_complete(root, termos[termoAtual])[1]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_3), auto_complete(root, termos[termoAtual])[2]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_4), auto_complete(root, termos[termoAtual])[3]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_5), auto_complete(root, termos[termoAtual])[4]);}

    else{
        //criação do vetor com os ids dos arquivos
        int * ids = (int*) malloc(sizeof(int)*qntTextos);
        for (int m = 0; m < qntTextos; ++m){
            ids[m] = m+1;}

        printf("Resultado da Busca: \n");
        for (int i = 0; i < qntTextos; i++){printf("Texto de ID %d\n", buscaTexto(qntTextos, ids, qntTermos, termos, arvore)[i]);}
        free(ids);
    }
}

void on_bt_sugestao_5_clicked(GtkButton *fBotao) {
    if (qntTermos > termoAtual){
        termoAtual += 1;
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_1), auto_complete(root, termos[termoAtual])[0]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_2), auto_complete(root, termos[termoAtual])[1]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_3), auto_complete(root, termos[termoAtual])[2]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_4), auto_complete(root, termos[termoAtual])[3]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_5), auto_complete(root, termos[termoAtual])[4]);}

    else{
        //criação do vetor com os ids dos arquivos
        int * ids = (int*) malloc(sizeof(int)*qntTextos);
        for (int m = 0; m < qntTextos; ++m){
            ids[m] = m+1;}

        printf("Resultado da Busca: \n");
        for (int i = 0; i < qntTextos; i++){printf("Texto de ID %d\n", buscaTexto(qntTextos, ids, qntTermos, termos, arvore)[i]);}
        free(ids);
    }
}

//--------------------------------------------------------

//limpa o conteudo escrito no widget de palavra
void on_bt_limpa_palavra_clicked(GtkButton *fBotao) {
	gtk_editable_delete_text (GTK_EDITABLE(entrada_palavra), 0, -1);
	}

//imprime o indice invertido no terminal
void on_bt_imprime_indice_clicked(GtkButton *fBotao) {
    printf("\nIndice Invertido da Arvore:\n");
    printaTabela(arvore);
}

//imprime as palavras do dicionario no terminal
void on_bt_imprime_palavras_clicked(GtkButton *fBotao) {
    printf("\nPalavras: \n");
    imprimteTST(root);
}

//leitura do arquivo de dicionario e inserção na TST
void on_bt_insere_tst_clicked(GtkButton *fBotao) {

    const char *nomearq;
    FILE* arquivo_dic;
    char buffer[30];
    nomearq = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(insere_arq_dic));
    arquivo_dic = fopen(nomearq, "r");
    while(fgets(buffer, 30, arquivo_dic)){
        buffer[strcspn(buffer, "\n")] = 0;
        insere_tst(&root, buffer);}
    printf("Arquivo Inserido!\n");

}

//função de busca da(s) palavra(s) inserida(s)
void on_bt_busca_palavra_clicked(GtkButton *fBotao) {

    const char* termo_busca;
    termoAtual = 0;

    termo_busca = gtk_entry_get_text(GTK_ENTRY(entrada_palavra));
    qntTermos = (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_qt_termos));

    //separação dos termos digitados
    int j = 0;
    termos = (char**) malloc(sizeof(char*)*qntTermos);
    for (int i = 0; i < qntTermos; i++){
        termos[i] = (char*) malloc(sizeof(char)*20);
        for (int l = 0; l  < 20; l++)termos[i][l] = ' ';
        int k = 0;
        while (termo_busca[j] != ' ' && termo_busca[j] != '\0') {
            termos[i][k] = termo_busca[j];
            j++;
            k++;}
        termos[i][k] = '\0';
        j++;}

        gtk_button_set_label(GTK_BUTTON(bt_sugestao_1), auto_complete(root, termos[termoAtual])[0]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_2), auto_complete(root, termos[termoAtual])[1]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_3), auto_complete(root, termos[termoAtual])[2]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_4), auto_complete(root, termos[termoAtual])[3]);
        gtk_button_set_label(GTK_BUTTON(bt_sugestao_5), auto_complete(root, termos[termoAtual])[4]);

    }

//leitura do arquivo de texto e inserção na PATRICIA
void on_bt_insere_arquivo_clicked(GtkButton *fBotao) {

    qntTextos += 1;
    const char *nomearq;
    FILE *arq;

    nomearq = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(insere_arq_texto));

    char buffer[200], bufferaux[50];
    int q = 0, j = 0, id_doc = qntTextos;
    memset(bufferaux, 0, 50);
    FILE *inputfp;
    inputfp = fopen(nomearq, "r");
        while (fgets(buffer, 200, inputfp)){
        buffer[strcspn(buffer, "\n")] = 0;
        //pega linha por linha e palavra por palavra e coloca dentro da arvore
        while(buffer[q] != '\0'){
            //separa cada palvra por espaco ou final de char
            if (buffer[q] == ' ' || buffer[q+1]== '\0' || buffer[q] == '.'|| buffer[q] == '!'|| buffer[q] == '?' ) {
                if(buffer[q+1]== '\0') {
                    bufferaux[j] = tolower(buffer[q]);
                    while (bufferaux[j] == ' ' || bufferaux[j] == '.' || bufferaux[j] == '!' || bufferaux[j] == '?') {
                        bufferaux[j] = '\0';
                        j--;
                    }
                }
                arvore = Insere(bufferaux,id_doc,&arvore);
                j=0;
                //esvazia o buffer auxiliar para ele receber mais palavras
                memset(bufferaux, 0, 50);
                q++;
            }
            while(buffer[q] == ' ' || buffer[q] == '.'|| bufferaux[q] == '!'|| bufferaux[q] == '?' ){
                q++;
            }
            //enche um buffer auxiliar com a palavra atual
            bufferaux[j] = tolower(buffer[q]);
            q++, j++;
        }
        q = j= 0;
    }
    //fecha o arquivo e termina um ciclo
    fclose(inputfp);
    printf("Arquivo Inserido!\nID = %d\n", id_doc);
}
