#include <stdio.h>
#include <string.h>

<<<<<<< HEAD
#define MAX_CLI 50
#define MAX_PROD 10
#define MAX_REGS 100
=======
#define QTD_CLIENTE 100
#define QTD_PRODUTOS 100

typef 
>>>>>>> ee418bc8598b30a54122ccd0807875997352c93f

typedef struct {
    int codigo;
    char nome[50];
    char cpf[15]; // Adicionado campo para CPF
} Pessoa;

typedef struct {
    int id;
    char descricao[50];
    float valorUnitario;
    int disponivel;
} Item;

typedef struct {
    int cliente_codigo;
    int item_id;
    int unidades;
    float total;
} Registro;

typedef struct {
    Pessoa clientes[MAX_CLI];
    Item produtos[MAX_PROD];
    Registro vendas[MAX_REGS];
    int qtdClientes;
    int qtdProdutos;
    int qtdVendas;
} Banco;

Banco sistema = { .qtdClientes = 0, .qtdProdutos = 0, .qtdVendas = 0 };

void inserirCliente() {
    if (sistema.qtdClientes >= MAX_CLI) {
        puts("Limite de clientes atingido.");
        return;
    }

    Pessoa novo;
    novo.codigo = sistema.qtdClientes + 1;
    printf("Nome do novo cliente: ");
    scanf(" %[^\n]", novo.nome);
    printf("CPF do novo cliente (apenas numeros): "); // Solicitando o CPF
    scanf(" %[^\n]", novo.cpf); // Lendo o CPF

    sistema.clientes[sistema.qtdClientes++] = novo;

    printf("Cliente cadastrado com sucesso! Código: %d\n", novo.codigo);
}

void mostrarClientes() {
    if (sistema.qtdClientes == 0) {
        puts("Nenhum cliente registrado.");
        return;
    }

    puts("\n-- Clientes --");
    for (int i = 0; i < sistema.qtdClientes; i++) {
        printf("Código: %d | Nome: %s | CPF: %s\n", sistema.clientes[i].codigo, sistema.clientes[i].nome, sistema.clientes[i].cpf); // Exibindo o CPF
    }
}

void inserirProduto() {
    if (sistema.qtdProdutos >= MAX_PROD) {
        puts("Limite de produtos atingido.");
        return;
    }

    Item novo;
    novo.id = sistema.qtdProdutos + 1;
    printf("Descrição do produto: ");
    scanf(" %[^\n]", novo.descricao);
    printf("Preço unitário: R$ ");
    scanf("%f", &novo.valorUnitario);
    printf("Quantidade disponível: ");
    scanf("%d", &novo.disponivel);

    sistema.produtos[sistema.qtdProdutos++] = novo;

    puts("Produto adicionado com sucesso!");
}

void mostrarProdutos() {
    if (sistema.qtdProdutos == 0) {
        puts("Nenhum produto cadastrado.");
        return;
    }

    puts("\n-- Estoque --");
    for (int i = 0; i < sistema.qtdProdutos; i++) {
        printf("ID: %d | Nome: %s | Preço: R$%.2f | Estoque: %d\n",
               sistema.produtos[i].id,
               sistema.produtos[i].descricao,
               sistema.produtos[i].valorUnitario,
               sistema.produtos[i].disponivel);
    }
}

void efetuarVenda() {
    if (sistema.qtdClientes == 0 || sistema.qtdProdutos == 0) {
        puts("Clientes ou produtos inexistentes.");
        return;
    }

    mostrarClientes();
    int codCliente;
    printf("Informe o código do cliente: ");
    scanf("%d", &codCliente);

    if (codCliente < 1 || codCliente > sistema.qtdClientes) {
        puts("Código de cliente inválido.");
        return;
    }

    mostrarProdutos();
    int idProduto;
    printf("Informe o ID do produto: ");
    scanf("%d", &idProduto);

    if (idProduto < 1 || idProduto > sistema.qtdProdutos) {
        puts("ID de produto inválido.");
        return;
    }

    int qtd;
    printf("Quantidade: ");
    scanf("%d", &qtd);

    Item *item = &sistema.produtos[idProduto - 1];
    if (item->disponivel < qtd) {
        puts("Estoque insuficiente.");
        return;
    }

    Registro nova;
    nova.cliente_codigo = codCliente;
    nova.item_id = idProduto;
    nova.unidades = qtd;
    nova.total = item->valorUnitario * qtd;

    item->disponivel -= qtd;
    sistema.vendas[sistema.qtdVendas++] = nova;

    puts("Venda registrada com sucesso!");
}

void mostrarVendas() {
    if (sistema.qtdVendas == 0) {
        puts("Nenhuma venda registrada.");
        return;
    }

    puts("\n-- Vendas --");
    for (int i = 0; i < sistema.qtdVendas; i++) {
        Registro v = sistema.vendas[i];
        Pessoa cliente = sistema.clientes[v.cliente_codigo - 1];
        Item produto = sistema.produtos[v.item_id - 1];

        printf("Venda %d | Cliente: %s | Produto: %s | Quantidade: %d | Total: R$%.2f\n",
               i + 1, cliente.nome, produto.descricao, v.unidades, v.total);
    }
}

void removerCliente() {
    if (sistema.qtdClientes == 0) {
        puts("Nenhum cliente para remover.");
        return;
    }

    mostrarClientes();
    int codigo;
    printf("Informe o código do cliente a remover: ");
    scanf("%d", &codigo);

    for (int i = 0; i < sistema.qtdClientes; i++) {
        if (sistema.clientes[i].codigo == codigo) {
            // Verificar se há vendas para este cliente antes de remover
            int clienteComVenda = 0;
            for(int k = 0; k < sistema.qtdVendas; k++) {
                if(sistema.vendas[k].cliente_codigo == codigo) {
                    clienteComVenda = 1;
                    break;
                }
            }

            if(clienteComVenda) {
                puts("Não é possível remover. Cliente possui vendas registradas.");
                return;
            }

            for (int j = i; j < sistema.qtdClientes - 1; j++) {
                sistema.clientes[j] = sistema.clientes[j + 1];
                // Atualiza o código dos clientes que foram "movidos"
                // Esta linha pode causar inconsistência de IDs se o ID é o identificador único
                // e não apenas index + 1. Se IDs devem ser persistentes, remova esta linha.
                // sistema.clientes[j].codigo = j + 1; // Comentada, pois pode causar inconsistência de IDs
            }
            sistema.qtdClientes--;
            puts("Cliente removido.");
            return;
        }
    }

    puts("Cliente não encontrado.");
}

void removerProduto() {
    if (sistema.qtdProdutos == 0) {
        puts("Nenhum produto para remover.");
        return;
    }

    mostrarProdutos();
    int id;
    printf("Informe o ID do produto a remover: ");
    scanf("%d", &id);

    // This is the loop where the error occurred in your previous paste,
    // indicating a corrupted line here or just above it.
    for (int i = 0; i < sistema.qtdProdutos; i++) {
        // The condition `if (sistema.produtos[i].id == id)` was likely corrupted/missing
        if (sistema.produtos[i].id == id) { // Corrected/restored line 214 logic
            // Verificar se há vendas para este produto antes de remover
            int produtoComVenda = 0;
            for(int k = 0; k < sistema.qtdVendas; k++) {
                if(sistema.vendas[k].item_id == id) {
                    produtoComVenda = 1;
                    break;
                }
            }

            if(produtoComVenda) {
                puts("Não é possível remover. Produto possui vendas registradas.");
                return;
            }

            for (int j = i; j < sistema.qtdProdutos - 1; j++) {
                sistema.produtos[j] = sistema.produtos[j + 1];
                // Atualiza o ID dos produtos que foram "movidos"
                // Assim como em removerCliente, esta linha pode causar inconsistência de IDs.
                // sistema.produtos[j].id = j + 1; // Comentada, pois pode causar inconsistência de IDs
            }
            sistema.qtdProdutos--;
            puts("Produto removido.");
            return;
        }
    }

    puts("Produto não encontrado.");
}

void menuPrincipal() {
    int opcao;

    do {
        puts("\n==== SISTEMA COMERCIAL ====");
        puts("1 - Novo Cliente");
        puts("2 - Listar Clientes");
        puts("3 - Novo Produto");
        puts("4 - Listar Produtos");
        puts("5 - Realizar Venda");
        puts("6 - Histórico de Vendas");
        puts("7 - Remover Cliente");
        puts("8 - Remover Produto");
        puts("0 - Sair");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirCliente(); break;
            case 2: mostrarClientes(); break;
            case 3: inserirProduto(); break;
            case 4: mostrarProdutos(); break;
            case 5: efetuarVenda(); break;
            case 6: mostrarVendas(); break;
            case 7: removerCliente(); break;
            case 8: removerProduto(); break;
            case 0: puts("Finalizando sistema."); break;
            default: puts("Opção inválida.");
        }

    } while (opcao != 0);
}

int main() {
    menuPrincipal();
    return 0;
<<<<<<< HEAD
}
=======
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
>>>>>>> ee418bc8598b30a54122ccd0807875997352c93f
