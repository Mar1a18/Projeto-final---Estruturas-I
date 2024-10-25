#include <stdio.h>
#include "farmacia.h"

// Ponteiros para o início das listas de usuários e itens
Usuario* listaUsuarios = NULL;
Item* listaItens = NULL;

int main() {
    int opcao, logado = 0;

    carregarUsuariosDeArquivo(&listaUsuarios);
    carregarItensDeArquivo(&listaItens);

    // Boas-vindas e login
    printf("Bem-vindo à Farmácia Virtual!\n");

    do {
        printf("\n1. Login\n2. Cadastrar Usuário\n3. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                logado = login(listaUsuarios);
                break;
            case 2:
                cadastrarUsuario(&listaUsuarios);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (!logado && opcao != 3);

    if (!logado) {
        return 0;
    }

    // Menu de operações da farmácia
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Item\n");
        printf("2. Listar Itens\n");
        printf("3. Editar Item\n");
        printf("4. Excluir Item\n");
        printf("5. Exibir Promoções\n");
        printf("6. Buscar por Categoria\n");
        printf("7. Adicionar ao Carrinho (Busca Binária)\n");
        printf("8. Pagamento\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarItem(&listaItens);
                break;
            case 2:
                listarItens(listaItens);
                break;
            case 3:
                editarItem(listaItens);
                break;
            case 4:
                excluirItem(&listaItens);
                break;
            case 5:
                exibirPromocoes(listaItens);
                break;
            case 6:
                printf("Digite a categoria para busca: ");
                char categoria[30];
                scanf(" %[^\n]", categoria);
                buscarPorCategoria(listaItens, categoria);
                break;
            case 7: {
                // Adiciona ao carrinho com busca binária
                char nomeBusca[50];
                printf("Digite o nome do medicamento que deseja buscar: ");
                scanf(" %[^\n]", nomeBusca);
                mergeSort(&listaItens);  // Ordena a lista por nome antes da busca
                Item* itemEncontrado = buscaBinariaPorNome(listaItens, nomeBusca);
                if (itemEncontrado != NULL) {
                    printf("Medicamento encontrado: %s - Preço: R$%.2f\n", itemEncontrado->nome, itemEncontrado->preco);
                } else {
                    printf("Medicamento não encontrado.\n");
                }
                break;
            }
            case 8:
                printf("Opção de pagamento ainda não implementada.\n");
                break;
            case 9:
                printf("Saindo do sistema...\n");
                salvarItensEmArquivo(listaItens, "itens.bin");  // Salvando as alterações
                salvarUsuariosEmArquivo(listaUsuarios, "usuarios.bin");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 9);

    // Liberar a memória alocada para as listas
    liberarListaItens(&listaItens);
    liberarListaUsuarios(&listaUsuarios);

    return 0;
}
