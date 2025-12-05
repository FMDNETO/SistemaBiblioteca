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
    int indiceLivro; // Qual indice do array de livros foi emprestado
    char nomeUsuario[TAM_STRING]; // Nome do usuário que fez o empréstimo
} Emprestimo;

// Função para limpar buffer do teclado
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

    //verifica se a alocação foi bem sucedida
    if(ptr_biblioteca == NULL || ptr_emprestimos == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1; // Sai do programa com erro
    }

    // Variáveis para o menu
    int opcao;
    int totalLivros = 0;
    int totalEmprestimos = 0;

    // LAÇO DO MENU
    do{

        //EXIBE O MENU
        printf("============================\n");
        printf("  BIBLIOTECA PARTE 2 - MENU PRINCIPAL\n");
        printf("============================\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Listar Livros\n");
        printf("3. Emprestar Livro\n");
        printf("4. Listar Emprestimos\n");
        printf("0. Sair\n");
        printf("----------------------------\n");
        printf("Escolha uma opcao: ");

        //LE A OPÇÃO DO USUÁRIO
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o buffer do teclado

        //EXECUTA A OPÇÃO ESCOLHIDA
        switch(opcao) {
            case 1: //CADASTRO DO LIVRO
                printf("CADASTRO DE LIVRO\n");
                if(totalLivros < MAX_LIVROS) {
                    // O acesso aos campos da struct é feito usando o ponteiro
                    // ptr_biblioteca[totalLivros] para acessar o livro atual
                    // Lê os dados do livro
                    // Acesso assim como no array normal
                    printf("Nome do Livro: ");
                    fgets(ptr_biblioteca[totalLivros].nome, TAM_STRING, stdin);
                    
                    printf("Autor do Livro: ");
                    fgets(ptr_biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Editora do Livro: ");
                    fgets(ptr_biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    printf("Edicao do Livro: ");
                    scanf("%d", &ptr_biblioteca[totalLivros].edicao);
                    limparBufferEntrada(); // Limpa o buffer do teclado

                    // Define o livro como disponível
                    ptr_biblioteca[totalLivros].disponivel = 1;

                    totalLivros++;
                    printf("Livro cadastrado com sucesso!\n");

                } else {
                    printf("Capacidade maxima de livros atingida!\n");
                }
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;

            case 2: //LISTA OS LIVROS CADASTRADOS
                printf("LISTA DE LIVROS CADASTRADOS\n");
                if(totalLivros == 0) {
                    printf("Nenhum livro cadastrado.\n");
                } else {
                    for(int i = 0; i < totalLivros; i++) {
                        printf("Livro %d:\n", i + 1);
                        printf("Nome: %s", ptr_biblioteca[i].nome);
                        printf("Autor: %s", ptr_biblioteca[i].autor);
                        printf("Editora: %s", ptr_biblioteca[i].editora);
                        printf("Edicao: %d\n", ptr_biblioteca[i].edicao);
                        printf("----------------------------\n");
                    }
                }
                
                printf("Pressione ENTER para continuar...");
                getchar();
                break;

            case 3: //EMPRESTAR LIVRO
                printf("EMPRESTAR LIVRO\n");
                if(totalEmprestimos >= MAX_EMPRESTIMOS){
                    printf("Limite de emprestimos atingido!\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();
                } else{
                    printf("Livros Disponiveis para Emprestimo:\n");
                    int livrosDisponiveis = 0;
                    for(int i = 0; i < totalLivros; i++) {
                        if(ptr_biblioteca[i].disponivel) {
                            printf("%d. %s", i + 1, ptr_biblioteca[i].nome);
                            livrosDisponiveis++;
                        }
                    }

                    if (livrosDisponiveis == 0) {
                        printf("Nenhum livro disponivel para emprestimo.\n");
                    } else {
                        int escolha;
                        printf("Escolha o numero do livro para emprestar: ");
                        scanf("%d", &escolha);
                        limparBufferEntrada(); // Limpa o buffer do teclado

                        if(escolha < 1 || escolha > totalLivros || !ptr_biblioteca[escolha - 1].disponivel) {
                            printf("Escolha invalida!\n");
                        } else {
                            printf("Digite o nome do usuario: ");
                            fgets(ptr_emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);

                            // Registra o empréstimo
                            ptr_emprestimos[totalEmprestimos].indiceLivro = escolha - 1;
                            ptr_biblioteca[escolha - 1].disponivel = 0; // Marca o livro como emprestado
                            totalEmprestimos++;

                            printf("Livro emprestado com sucesso!\n");
                        }
                    }
                }
            
            case 4: //LISTA OS EMPRESTIMOS
                printf("LISTA DE EMPRESTIMOS\n");
                if(totalEmprestimos == 0) {
                    printf("Nenhum emprestimo registrado.\n");
                } else {
                    for(int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = ptr_emprestimos[i].indiceLivro;
                        printf("Emprestimo %d:\n", i + 1);
                        printf("Livro: %s", ptr_biblioteca[indiceLivro].nome);
                        printf("Usuario: %s", ptr_emprestimos[i].nomeUsuario);
                        printf("----------------------------\n");
                    }
                }
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            
            case 0: //SAIR DO PROGRAMA
                printf("Saindo do programa...\n");
                free(ptr_biblioteca); // Libera a memória alocada para os livros
                free(ptr_emprestimos); // Libera a memória alocada para os empréstimos
                break;  


            default:
                printf("Opcao invalida! Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                getchar();
                break;

    }    } while(opcao != 0);
    return 0;
}
