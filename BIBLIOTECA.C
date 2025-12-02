#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Constantes GLOBAIS
#define MAX_LIVROS 50
#define TAM_STRING 100

// Estrutura para representar um livro
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao; 
};

// FUNÇÃO PRINCIPAL
int main() {
    struct Livro bibilioteca[MAX_LIVROS];
    int numLivros = 0;
    int opcao;

    // LAÇO DO MENU
    do{

        //EXIBE O MENU
        printf("============================\n");
        printf("  BIBLIOTECA - MENU PRINCIPAL\n");
        printf("============================\n");
        printf("1. Adicionar Livro\n");
        printf("2. Listar Livros\n");
        printf("3. Sair\n");
        printf("----------------------------\n");
        printf("Escolha uma opcao: ");

        //LE A OPÇÃO DO USUÁRIO
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        //EXECUTA A OPÇÃO ESCOLHIDA
        switch(opcao) {
            case 1: //CADASTRO DO LIVRO
                printf("CADASTRO DE LIVRO\n");
                if(numLivros < MAX_LIVROS) {
                    printf("Nome do Livro: ");
                    fgets(bibilioteca[numLivros].nome, TAM_STRING, stdin);
                    
                    printf("Autor do Livro: ");
                    fgets(bibilioteca[numLivros].autor, TAM_STRING, stdin);

                    printf("Editora do Livro: ");
                    fgets(bibilioteca[numLivros].editora, TAM_STRING, stdin);

                    printf("Edicao do Livro: ");
                    scanf("%d", &bibilioteca[numLivros].edicao);
                    getchar(); // Limpa o buffer do teclado

                    numLivros++;
                    printf("Livro cadastrado com sucesso!\n");

                } else {
                    printf("Capacidade maxima de livros atingida!\n");
                }
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;

            case 2: //LISTA OS LIVROS CADASTRADOS
                printf("LISTA DE LIVROS CADASTRADOS\n");
                if(numLivros == 0) {
                    printf("Nenhum livro cadastrado.\n");
                } else {
                    for(int i = 0; i < numLivros; i++) {
                        printf("Livro %d:\n", i + 1);
                        printf("Nome: %s", bibilioteca[i].nome);
                        printf("Autor: %s", bibilioteca[i].autor);
                        printf("Editora: %s", bibilioteca[i].editora);
                        printf("Edicao: %d\n", bibilioteca[i].edicao);
                        printf("----------------------------\n");
                    }
                }
                
                printf("Pressione ENTER para continuar...");
                getchar();
                break;

            case 3: //SAIR DO PROGRAMA
                printf("Saindo do programa...\n");
                break;  


            default:
                printf("Opcao invalida! Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                getchar();
                break;

    }    } while(opcao != 3);
    return 0;
}
