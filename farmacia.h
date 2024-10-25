#ifndef FARMACIA_H
#define FARMACIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições de estrutura para o sistema de farmácia
typedef struct Usuario {
    char nome[50];
    char email[80];
    char senha[20];
    struct Usuario* prox; // Ponteiro para o próximo usuário (lista encadeada)
} Usuario;

typedef struct Item {
    char nome[50];
    float preco;
    int quantidade;
    char categoria[30];
    struct Item* prox; // Ponteiro para o próximo item (lista encadeada)
} Item;

// Funções para manipulação de usuários
void cadastrarUsuario(Usuario** listaUsuarios);
int login(Usuario* listaUsuarios);

// Funções para manipulação de itens
void cadastrarItem(Item** listaItens);
void listarItens(Item* listaItens);
void editarItem(Item* listaItens);
void excluirItem(Item** listaItens);
void buscarPorCategoria(Item* listaItens, char* categoria);
void exibirPromocoes(Item* listaItens);

// Funções de manipulação de arquivos
void salvarItensEmArquivo(Item* listaItens, const char* nomeArquivo);
void carregarItensDeArquivo(Item** listaItens, const char* nomeArquivo);
void salvarUsuariosEmArquivo(Usuario* listaUsuarios, const char* nomeArquivo);
void carregarUsuariosDeArquivo(Usuario** listaUsuarios, const char* nomeArquivo);

// Algoritmos de busca e ordenação
Item* buscaBinariaPorNome(Item* listaItens, const char* nome);
void mergeSort(Item** listaItens);
void dividir(Item* origem, Item** frente, Item** tras);
Item* merge(Item* lista1, Item* lista2);

#endif
