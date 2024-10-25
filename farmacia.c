#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "farmacia.h"

// Ponteiros para o início das listas de usuários e itens
Usuario* listaUsuarios = NULL;
Item* listaItens = NULL;

// Funções para manipulação de arquivos
void salvarItensEmArquivo() {
    FILE *arquivo = fopen("itens.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar itens.\n");
        return;
    }
    Item* atual = listaItens;
    while (atual != NULL) {
        fwrite(atual, sizeof(Item), 1, arquivo);
        atual = atual->prox;
    }
    fclose(arquivo);
}

void carregarItensDeArquivo() {
    FILE *arquivo = fopen("itens.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de itens encontrado.\n");
        return;
    }

    Item* novoItem;
    while (!feof(arquivo)) {
        novoItem = (Item*)malloc(sizeof(Item));
        if (fread(novoItem, sizeof(Item), 1, arquivo) == 1) {
            novoItem->prox = listaItens;
            listaItens = novoItem;
        }
    }
    fclose(arquivo);
}

void salvarUsuariosEmArquivo() {
    FILE *arquivo = fopen("usuarios.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar usuários.\n");
        return;
    }
    Usuario* atual = listaUsuarios;
    while (atual != NULL) {
        fwrite(atual, sizeof(Usuario), 1, arquivo);
        atual = atual->prox;
    }
    fclose(arquivo);
}

void carregarUsuariosDeArquivo() {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de usuários encontrado.\n");
        return;
    }

    Usuario* novoUsuario;
    while (!feof(arquivo)) {
        novoUsuario = (Usuario*)malloc(sizeof(Usuario));
        if (fread(novoUsuario, sizeof(Usuario), 1, arquivo) == 1) {
            novoUsuario->prox = listaUsuarios;
            listaUsuarios = novoUsuario;
        }
    }
    fclose(arquivo);
}

// Função para cadastrar um novo usuário
void cadastrarUsuario(Usuario** listaUsuarios) {
    Usuario* novoUsuario = (Usuario*)malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
        printf("Erro ao alocar memória para novo usuário.\n");
        return;
    }

    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", novoUsuario->nome);

    do {
        printf("Digite o email do usuário: ");
        scanf(" %[^\n]", novoUsuario->email);

        if (strchr(novoUsuario->email, '@') == NULL || strlen(novoUsuario->email) >= 80) {
            printf("Email inválido. Deve conter '@' e ser menor que 80 caracteres.\n");
            continue;
        }

        Usuario* atual = *listaUsuarios;
        int emailExistente = 0;
        while (atual != NULL) {
            if (strcmp(atual->email, novoUsuario->email) == 0) {
                emailExistente = 1;
                break;
            }
            atual = atual->prox;
        }

        if (emailExistente) {
            printf("Email já cadastrado. Por favor, insira um email diferente.\n");
        } else {
            break;
        }

    } while (1);

    printf("Digite a senha do usuário: ");
    scanf(" %[^\n]", novoUsuario->senha);
    novoUsuario->prox = *listaUsuarios;
    *listaUsuarios = novoUsuario;
    salvarUsuariosEmArquivo();
    printf("Usuário cadastrado com sucesso!\n");
}

// Função para cadastrar um novo item
void cadastrarItem(Item** listaItens) {
    Item* novoItem = (Item*)malloc(sizeof(Item));
    if (novoItem == NULL) {
        printf("Erro ao alocar memória para novo item.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", novoItem->nome);
    printf("Digite o preço do produto: ");
    scanf("%f", &novoItem->preco);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoItem->quantidade);
    printf("Digite a categoria do produto: ");
    scanf(" %[^\n]", novoItem->categoria);

    novoItem->prox = *listaItens;
    *listaItens = novoItem;
    salvarItensEmArquivo();
    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar todos os itens
void listarItens(Item* listaItens) {
    if (listaItens == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nLista de Produtos:\n");
    Item* atual = listaItens;
    int i = 1;
    while (atual != NULL) {
        printf("Produto %d: %s\n", i++, atual->nome);
        printf("Preço: R$%.2f\n", atual->preco);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Categoria: %s\n\n", atual->categoria);
        atual = atual->prox;
    }
}


