#include <stdio.h>
#include <stdlib.h>
//#include "clientes.h"//colocar sempre em aspas biblioteca criada

#define QTD_CLIENTE 10
#define QTD_PRODUTOS 10

void insere_produto();
void insere_clientes();
void listar_clientes ();
void listar_produtos();

char produtos[QTD_PRODUTOS][50];
char clientes [QTD_CLIENTE][50];

int index_cliente = 0;
int index_cliente2 = 0;

int main (){
    int opcao = 0;
    do{
        printf("Selecione uma opcao: \n"
        "0 = sair\n"
        "1 = Insere cliente\n"
        "2 = Insere produto\n"
        "3 = Insere venda\n"
        "4 = Listar clientes\n"
        "5 = Listar produtos\n");

    scanf ("%d", &opcao);
    printf ("Opção escolhida: %d\n\n", opcao);

    if (opcao == 1) {
        insere_clientes();
    } else if (opcao == 2) {
        insere_produto();
    } else if (opcao == 3) {
         // insere_venda(); // ainda não implementado
    } else if (opcao == 4) {
        listar_clientes();
    } else if (opcao == 5) {
        listar_produtos();
    }

    } while (opcao != 0);

    return 0;
}

void insere_clientes(){
     int opcao;
    if (index_cliente >= QTD_CLIENTE){
        printf("Limite de clientes atingido!\n\n");
    }else{
        printf("insira o cliente: \t");
        scanf("%s", clientes[index_cliente]);
        index_cliente++;   //index_cliente = index_cliente + 1;

        printf("Deseja inserir mais clientes?\n");
        printf("1 - SIM\n");
        printf("2 - NÃO\n");
        scanf("%d", &opcao);

        if (opcao == 1){
            insere_clientes();
        }
    }
}

void listar_clientes (){ //listas = imprimi-r
    int i;
    for (i = 0; i < index_cliente; i++){
        printf("Cliente %d: %s\n\n", (i+1), clientes[i]);
    }

}

void insere_produto(){
int opcao;
    if (index_cliente2 >= 10){
    printf ("Limite de produtos atingido!\n\n");
    }else{
    printf ("insira o produto: \t");
    scanf("%s", produtos[index_cliente2]);
    index_cliente2++;
        printf("Deseja inserir mais produtos?\n");
        printf("1 - SIM\n");
        printf("2 - NÃO\n");
        scanf("%d", &opcao);

        if (opcao == 1){
            insere_produto();
        }
    }
}

void listar_produtos(){ //listas = imprimi-r
    int j;
    for (j = 0; j < index_cliente2; j++){
        printf("produtos %d: %s\n\n", (j+1), produtos[j]);

    }
}
kasndjknasjkdnajksndjk