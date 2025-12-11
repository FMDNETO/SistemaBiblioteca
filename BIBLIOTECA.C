#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Constantes GLOBAIS
#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMOS 100

// Estrutura para representar um livro
// Define a estrutura Livro
// Incluir o campo 'disponivel' para indicar se o livro está disponível para empréstimo
typedef struct {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao; 
    int disponivel; // 1 para disponível, 0 para emprestado
} Livro;

// Nova struct para representar um empréstimo
typedef struct {
    int indiceLivro; // Qual índice do array de livros foi emprestado
    char nomeUsuario[TAM_STRING]; // Nome do usuário que fez o empréstimo
} Emprestimo;

//============================
// PROTÓTIPO DAS FUNÇÕES
//============================

void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(Livro *biblioteca, int *totalLivros);
void listarLivros(Livro *biblioteca, int totalLivros);
void emprestarLivro(Livro *biblioteca, Emprestimo *emprestimos, int *totalEmprestimos, int totalLivros);
void listarEmprestimos(Livro *biblioteca, Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(Livro *biblioteca, Emprestimo *emprestimos);

//============================
// IMPLEMENTAÇÃO DAS FUNÇÕES
//============================

// Função para limpar buffer do teclado
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para exibir o menu
void exibirMenu() {
    printf("============================\n");
    printf("  BIBLIOTECA PARTE 2 - MENU PRINCIPAL\n");
    printf("============================\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Emprestar Livro\n");
    printf("4. Listar Empréstimos\n");
    printf("0. Sair\n");
    printf("----------------------------\n");
    printf("Escolha uma opção: ");
}

// Função para cadastrar um livro
void cadastrarLivro(Livro *biblioteca, int *totalLivros) {
    printf("CADASTRO DE LIVRO\n");
    if(*totalLivros < MAX_LIVROS) {
        printf("Nome do Livro: ");
        fgets(biblioteca[*totalLivros].nome, TAM_STRING, stdin);
        
        printf("Autor do Livro: ");
        fgets(biblioteca[*totalLivros].autor, TAM_STRING, stdin);

        printf("Editora do Livro: ");
        fgets(biblioteca[*totalLivros].editora, TAM_STRING, stdin);

        printf("Edição do Livro: ");
        scanf("%d", &biblioteca[*totalLivros].edicao);
        limparBufferEntrada();

        // Define o livro como disponível
        biblioteca[*totalLivros].disponivel = 1;

        (*totalLivros)++;
        printf("Livro cadastrado com sucesso!\n");
    } else {
        printf("Capacidade máxima de livros atingida!\n");
    }
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// Função para listar todos os livros
void listarLivros(Livro *biblioteca, int totalLivros) {
    printf("LISTA DE LIVROS CADASTRADOS\n");
    if(totalLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
    } else {
        for(int i = 0; i < totalLivros; i++) {
            printf("Livro %d:\n", i + 1);
            printf("Nome: %s", biblioteca[i].nome);
            printf("Autor: %s", biblioteca[i].autor);
            printf("Editora: %s", biblioteca[i].editora);
            printf("Edição: %d\n", biblioteca[i].edicao);
            printf("----------------------------\n");
        }
    }
    printf("Pressione ENTER para continuar...");
    getchar();
}

// Função para emprestar um livro
void emprestarLivro(Livro *biblioteca, Emprestimo *emprestimos, int *totalEmprestimos, int totalLivros) {
    printf("EMPRESTAR LIVRO\n");
    if(*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de empréstimos atingido!\n");
        printf("Pressione ENTER para continuar...");
        getchar();
    } else {
        printf("Livros Disponíveis para Empréstimo:\n");
        int livrosDisponiveis = 0;
        
        for(int i = 0; i < totalLivros; i++) {
            if(biblioteca[i].disponivel) {
                printf("%d. %s", i + 1, biblioteca[i].nome);
                livrosDisponiveis++;
            }
        }

        if (livrosDisponiveis == 0) {
            printf("Nenhum livro disponível para empréstimo.\n");
            printf("Pressione ENTER para continuar...");
            getchar();
        } else {
            int escolha;
            printf("Escolha o número do livro para emprestar: ");
            scanf("%d", &escolha);
            limparBufferEntrada();

            if(escolha < 1 || escolha > totalLivros || !biblioteca[escolha - 1].disponivel) {
                printf("Escolha inválida!\n");
            } else {
                printf("Digite o nome do usuário: ");
                fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);

                // Registra o empréstimo
                emprestimos[*totalEmprestimos].indiceLivro = escolha - 1;
                biblioteca[escolha - 1].disponivel = 0; // Marca o livro como emprestado
                (*totalEmprestimos)++;

                printf("Livro emprestado com sucesso!\n");
            }
            printf("Pressione ENTER para continuar...");
            getchar();
        }
    }
}

// Função para listar todos os empréstimos
void listarEmprestimos(Livro *biblioteca, Emprestimo *emprestimos, int totalEmprestimos) {
    printf("LISTA DE EMPRÉSTIMOS\n");
    if(totalEmprestimos == 0) {
        printf("Nenhum empréstimo registrado.\n");
    } else {
        for(int i = 0; i < totalEmprestimos; i++) {
            int indiceLivro = emprestimos[i].indiceLivro;
            printf("Empréstimo %d:\n", i + 1);
            printf("Livro: %s", biblioteca[indiceLivro].nome);
            printf("Usuário: %s", emprestimos[i].nomeUsuario);
            printf("----------------------------\n");
        }
    }
    printf("Pressione ENTER para continuar...");
    getchar();
}

// Função para liberar a memória alocada
void liberarMemoria(Livro *biblioteca, Emprestimo *emprestimos) {
    free(biblioteca);
    free(emprestimos);
}

// FUNÇÃO PRINCIPAL
int main() {
    // 1 - ALOCAÇÃO DINÂMICA DE MEMÓRIA PARA LIVROS
    Livro *ptr_biblioteca;
    Emprestimo *ptr_emprestimos;

    // Aloca memória para os livros com calloc
    ptr_biblioteca = (Livro *)calloc(MAX_LIVROS, sizeof(Livro));

    // Aloca memória para os empréstimos com malloc
    ptr_emprestimos = (Emprestimo *)malloc(MAX_EMPRESTIMOS * sizeof(Emprestimo));

    //verifica se a alocação foi bem-sucedida
    if(ptr_biblioteca == NULL || ptr_emprestimos == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1; // Sai do programa com erro
    }

    // Variáveis para o menu
    int opcao;
    int totalLivros = 0;
    int totalEmprestimos = 0;

    // LAÇO DO MENU
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                cadastrarLivro(ptr_biblioteca, &totalLivros);
                break;

            case 2:
                listarLivros(ptr_biblioteca, totalLivros);
                break;

            case 3:
                emprestarLivro(ptr_biblioteca, ptr_emprestimos, &totalEmprestimos, totalLivros);
                break;
            
            case 4:
                listarEmprestimos(ptr_biblioteca, ptr_emprestimos, totalEmprestimos);
                break;
            
            case 0:
                printf("Saindo do programa...\n");
                liberarMemoria(ptr_biblioteca, ptr_emprestimos);
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
        }
    } while(opcao != 0);
    
    return 0;
}
