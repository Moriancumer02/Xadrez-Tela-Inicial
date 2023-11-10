#include <stdio.h>
#include <stdlib.h>
#include <time.h> //biblioteca para manipular tempo 
#include <unistd.h> //biblioteca para funções como 'sleep()'

//estrutura de representar os players
struct player {
    char nome[20], sobrenome[20], sexo, pais[20];
    int dia, mes, ano, id;
}; 

//funcao verificadora para gerar numero ID
int idExiste(int id, struct player* cadastros, int numCadastros) {
    for (int i = 0; i < numCadastros; i++) {
        if (cadastros[i].id == id) {
            return 1; //se ID ja existe, gerar outro ID
        }
    }
    return 0; //finaliza função se o ID não existe
} 

//Função para escrever os jogadores em arquivo txt
void salvarJogadores(struct player* cadastros, int numCadastros) {
    FILE* arquivo = fopen("jogadores.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de jogadores");
        exit(1); //caso nao haja arquivo
    } 

    for (int i = 0; i < numCadastros; i++) {
        fprintf(arquivo, "%s %s %c %s %d %d %d %d\n", cadastros[i].nome, cadastros[i].sobrenome, cadastros[i].sexo, cadastros[i].pais, cadastros[i].dia, cadastros[i].mes, cadastros[i].ano, cadastros[i].id);
    } 

    fclose(arquivo);
}

void carregarJogadores(struct player* cadastros, int* numCadastros) {
    FILE* arquivo = fopen("jogadores.txt", "r");
    if (arquivo == NULL) {
        return; // Não há arquivo de jogadores existente
    }

    *numCadastros = 0;
    while (fscanf(arquivo, "%s %s %c %s %d %d %d %d", cadastros[*numCadastros].nome, cadastros[*numCadastros].sobrenome, &cadastros[*numCadastros].sexo, cadastros[*numCadastros].pais, &cadastros[*numCadastros].dia, &cadastros[*numCadastros].mes, &cadastros[*numCadastros].ano, &cadastros[*numCadastros].id) == 8) {
        (*numCadastros)++;
    }

    fclose(arquivo);
}

//função para listar nome e ID dos Players cadastrados
void listarNomesEIDs(struct player* cadastros, int numCadastros) {
    printf("Lista de jogadores cadastrados:\n");
    for (int i = 0; i < numCadastros; i++) {
        printf("ID: %04d, Nome: %s %s\n", cadastros[i].id, cadastros[i].nome, cadastros[i].sobrenome);
    }
}

int main() {
    srand(time(NULL)); //inicializa o gerador de numeros aleatorios pra criar ID

    //declarando variaveis
    char opcao;
    struct player novoCadastro;
    struct player cadastro[8]; //limitando a 8 cadastros
    int numCadastros = 0;

    carregarJogadores(cadastro, &numCadastros);

    //menu principal
    while (1) {
        printf("\n____Seja Bem vindo ao Xadrez virtual! O que deseja fazer?____\n\n");
        puts("1. Cadastrar novo player\n2. Jogar\n3. Listar jogadores cadastrados\n");
        scanf(" %c", &opcao);

        if (opcao == '1') {
            novoCadastro.id = rand() % 10000; //// Gera um número aleatório entre 0 e 9999 (4 dígitos) para o ID
            
            //// Verifica se o ID gerado já existe na lista de cadastros, se tiver vai criar outro
            while (idExiste(novoCadastro.id, cadastro, numCadastros)) {
                novoCadastro.id = rand() % 10000;
            }

            //coletando informações do novo jogador
            printf("Vamos iniciar seu cadastro, qual o seu primeiro nome?\n");
            scanf(" %[^\n]", novoCadastro.nome);

            printf("%s, digite seu sobrenome\n", novoCadastro.nome);
            scanf(" %[^\n]", novoCadastro.sobrenome);

            printf("Qual seu pais de origem?\n");
            scanf(" %[^\n]", novoCadastro.pais);

            printf("Digite a data de nascimento (DD MM AAAA):\n");
            scanf("%d %d %d", &novoCadastro.dia, &novoCadastro.mes, &novoCadastro.ano);
            printf("%02d/%02d/%04d\n", novoCadastro.dia, novoCadastro.mes, novoCadastro.ano);

            printf("Seu sexo (F ou M):\n");
            scanf(" %c", &novoCadastro.sexo);

           
            //switch case de mensagem personalizada para player masculino ou feminino
            switch (novoCadastro.sexo) {
                case 'f':
                case 'F':
                    printf("Seja Bem vinda, %s %s. Cadastrada com sucesso, sua ID: %04d\n", novoCadastro.nome, novoCadastro.sobrenome, novoCadastro.id);
                    
            // Armazena o novo cadastro na lista de jogadores e incrementa o contador
            cadastro[numCadastros] = novoCadastro;
            numCadastros++;
            
            // Salva a lista atualizada de jogadores no arquivo
            salvarJogadores(cadastro, numCadastros);
                    break;

                case 'm':
                case 'M':
                    printf("Seja Bem vindo, %s %s. Cadastrado com sucesso, sua ID: %04d\n", novoCadastro.nome, novoCadastro.sobrenome, novoCadastro.id);
                    
            // Armazena o novo cadastro na lista de jogadores e incrementa o contador
            cadastro[numCadastros] = novoCadastro;
            numCadastros++;
            
            // Salva a lista atualizada de jogadores no arquivo
            salvarJogadores(cadastro, numCadastros);
                    break;

                default:
                    printf("Sexo nao identificado, cadastro nao concluido.\n");
            }


            sleep(5); //conta 5 segundos antes de voltar pra tela inicial, isso graças às biblitecas que foram adicionadas
        } else if (opcao == '2') {
             printf("Procurando partida...\n");
    puts("Para voltar ao inicio, pressione 4");
    
    char opcaoJogar;
    scanf(" %c", &opcaoJogar);

    if (opcaoJogar == '4') {
        printf("Voltando ao menu principal, aguarde...\n");
    }
        } else if (opcao == '3') {
            listarNomesEIDs(cadastro, numCadastros);
            printf("\nPara voltar ao inicio, pressione 4: ");
            
            char opcaoLista;
            scanf(" %c", &opcaoLista); //condicao para listar nomes
            
            if (opcaoLista == '4') {
                printf("Voltando, aguarde...\n");
            }
        } else if (opcao == '4') {
            printf("Saindo do programa, aguarde...\n");
            break;
        }
    }
    return 0;
}
