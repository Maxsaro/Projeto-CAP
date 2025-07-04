/*
 * Descrição: Implementação de um jogo simplificado de Truco.
 * O jogo busca simular as mecânicas básicas do Truco, incluindo a distribuição de cartas
 * e a gestão de jogadores em equipes.
 *
 * Requisitos:
 * - Número par de jogadores (2, 4 ou 6).
 *
 * Assegura:
 * - Exibição do resultado final do jogo.
 * - Gerenciamento de jogadores e suas mãos de cartas.
 */

#include <stdio.h>  // Para funções de entrada e saída, como printf, scanf, fgets.
#include <stdlib.h> // Para a função rand e srand (geração de números aleatórios).
#include <time.h>   // Para a função time (usada na semeadura do gerador de números aleatórios).
#include <string.h> // Para funções de manipulação de strings, como strlen (a ser usada para remover o '\n').
#include <locale.h>

// Variável de controle para garantir que srand() seja chamada apenas uma vez.
// Isso evita que o gerador de números aleatórios seja resemeado múltiplas vezes,
// o que poderia gerar sequências repetitivas de números.
static int gerador_semeado = 0;

// Constante para os naipes das cartas, usada para mapear os índices numéricos
// gerados aleatoriamente para os caracteres dos naipes.
// 'C' = Copas, 'E' = Espadas, 'O' = Ouros, 'P' = Paus.
const char NAIPES[] = {'C', 'E', 'O', 'P'};

/*
 * Estrutura que representa uma carta individual.
 */
struct carta
{
    // Número da carta:
    // 1 = 'A' (Ás)
    // 2 a 7 = Cartas numeradas
    // 8 = 'Q' (Rainha)
    // 9 = 'J' (Valete)
    // 10 = 'K' (Rei)
    int numero;
    // Naipe da carta, mapeado pelos caracteres definidos em NAIPES:
    // 0 = Copas ('C')
    // 1 = Espadas ('E')
    // 2 = Ouros ('O')
    // 3 = Paus ('P')
    int naipe;
};

/*
 * Estrutura que representa um jogador no jogo.
 */
struct jogador
{
    char nome[50];       // Nome do jogador.
    struct carta mao[3]; // Mão do jogador, contendo 3 cartas.
};

/*
 * @brief Gera um número aleatório dentro de um intervalo específico.
 * Esta função garante que o gerador de números aleatórios seja semeado apenas uma vez
 * durante a execução do programa, utilizando o tempo atual como semente.
 *
 * @param max O valor máximo inclusivo que o número aleatório pode atingir.
 * @return Um número inteiro aleatório entre 0 e 'max' (inclusive).
 */
int gerar_numero_aleatorio(int max)
{
    // Semeia o gerador de números aleatórios se ainda não foi semeado.
    // 'time(NULL)' retorna o tempo atual do sistema, fornecendo uma semente única.
    if (!gerador_semeado)
    {
        srand((unsigned int)time(NULL));
        gerador_semeado = 1;
    }
    // Gera um número aleatório e usa o operador de módulo (%) para limitá-lo
    // ao intervalo de 0 a 'max' - 1. Somando 1, o intervalo se torna de 1 a 'max'.
    return (rand() % (max + 1));
}

/*
 * @brief Atribui um número aleatório à carta.
 * O número da carta será gerado entre 1 e 9, representando as cartas de 'A' a 'K' (excluindo 8, 9, 10 para 'Q', 'J', 'K' respectivamente, ajustando para o índice 1-based do seu jogo).
 *
 * @param carta Um ponteiro para a estrutura 'carta' a ser atualizada.
 */
void sorteio_numero_carta(struct carta *carta)
{
    // Gera um número aleatório entre 1 e 9 para o número da carta.
    // Em um baralho de truco, as cartas válidas são A, 2, 3, 4, 5, 6, 7, Q, J, K.
    // Aqui, estamos assumindo que 1-7, 8, 9, 10 representam essa sequência.
    // A função 'gerar_numero_aleatorio' está configurada para retornar de 0 a 'max'.
    // Para obter 1 a 9, passamos 8 como 'max' e somamos 1.
    carta->numero = gerar_numero_aleatorio(9);
}

/*
 * @brief Atribui um naipe aleatório à carta.
 * O naipe será sorteado com base nos índices da constante NAIPES.
 *
 * @param carta Um ponteiro para a estrutura 'carta' a ser atualizada.
 */
void sorteio_naipe(struct carta *carta)
{
    // Gera um número aleatório entre 0 e 3 para o naipe da carta,
    // que corresponde aos índices do array NAIPES.
    carta->naipe = gerar_numero_aleatorio(3);
}

/*
 * @brief Cria uma nova carta com número e naipe aleatórios.
 * Esta função chama 'sorteio_numero_carta' e 'sorteio_naipe' para preencher os
 * campos da carta.
 *
 * @param carta Uma estrutura 'carta' que será preenchida com valores aleatórios.
 * @return A estrutura 'carta' preenchida.
 */
struct carta criar_carta_aleatoria(struct carta carta)
{
    sorteio_numero_carta(&carta); // Sorteia o número da carta.
    sorteio_naipe(&carta);        // Sorteia o naipe da carta.
    return carta;                 // Retorna a carta com número e naipe sorteados.
}

/*
 * @brief Permite ao usuário digitar o nome de um jogador e o armazena na estrutura.
 * Utiliza fgets para ler a entrada do usuário de forma segura, evitando estouros de buffer.
 * Remove o caractere de nova linha ('\n') que fgets pode adicionar ao final da string.
 *
 * @param jogador Um ponteiro para a estrutura 'jogador' a ser atualizada.
 */
void adicionar_nome_jogador(struct jogador *jogador)
{
    printf("Digite o nome do jogador: ");
    fgets(jogador->nome, sizeof(jogador->nome), stdin); // Lê a linha inteira, incluindo o '\n'.
    // Remove o '\n' do final da string, se presente.
    jogador->nome[strcspn(jogador->nome, "\n")] = '\0';
}

/*
 * @brief Distribui as cartas para a mão de um jogador.
 * Para cada uma das 3 cartas na mão do jogador, uma nova carta aleatória é criada.
 *
 * @param jogador Um ponteiro para a estrutura 'jogador' cuja mão será preenchida.
 */
void distribuir_cartas_jogador(struct jogador *jogador)
{
    for (int i = 0; i < 3; i++)
    {
        jogador->mao[i] = criar_carta_aleatoria(jogador->mao[i]);
    }
}

/*
 * @brief Adiciona jogadores a uma equipe, solicitando seus nomes e distribuindo cartas.
 *
 * @param time Um array de estruturas 'jogador' que compõem a equipe.
 * @param quantidade_jogadores O número de jogadores na equipe.
 */
void adicionar_equipe(struct jogador time[], int quantidade_jogadores)
{
    for (int i = 0; i < quantidade_jogadores; i++)
    {
        adicionar_nome_jogador(&time[i]);    // Solicita o nome do jogador.
        distribuir_cartas_jogador(&time[i]); // Distribui 3 cartas para o jogador.
    }
}

/*
 * @brief Exibe as informações de uma única carta.
 *
 * @param carta A estrutura 'carta' a ser exibida.
 */
void exibir_carta(struct carta carta)
{
    // Acessa o caractere do naipe usando o índice armazenado na carta.
    printf("%d%c ", carta.numero, NAIPES[carta.naipe]);
}

/*
 * @brief Exibe todas as cartas na mão de um jogador.
 *
 * @param mao Um array de estruturas 'carta' representando a mão do jogador.
 */
void exibir_mao(struct carta mao[])
{
    printf("Mão: ");
    for (int i = 0; i < 3; i++)
    {
        exibir_carta(mao[i]); // Exibe cada carta individualmente.
    }
    printf("\n");
}

/*
 * @brief Exibe as informações de todos os jogadores em uma equipe, incluindo seus nomes e mãos.
 *
 * @param time Um array de estruturas 'jogador' que compõem a equipe.
 * @param quantidade_jogadores O número de jogadores na equipe.
 */
void exibir_time(struct jogador time[], int quantidade_jogadores)
{
    for (int i = 0; i < quantidade_jogadores; i++)
    {
        printf("--- Jogador: %s ---\n", time[i].nome); // Exibe o nome do jogador.
        exibir_mao(time[i].mao);                       // Exibe as cartas na mão do jogador.
    }
}

void exibir_ganhador(struct jogador time[], int quantidade_jogadores)
{
    printf("\n--- Ganhador do Jogo ---\n");
    exibir_time(time, quantidade_jogadores);
}

void exibir_pontuacao_final(int pontuacao_time_1, int pontuacao_time_2)
{
    printf("\n--- Pontuação Final ---\n");
    printf("Time 1: %d pontos\n", pontuacao_time_1);
    printf("Time 2: %d pontos\n", pontuacao_time_2);
}

void finalizar_jogo(struct jogador time_1[], struct jogador time_2[], int pontuacao_time_1, int pontuacao_time_2, int qtd_jagadores_cada_time)
{
    if (pontuacao_time_1 > pontuacao_time_2)
        exibir_ganhador(time_1, qtd_jagadores_cada_time);
    else
        exibir_ganhador(time_2, qtd_jagadores_cada_time);

    exibir_pontuacao_final(pontuacao_time_1, pontuacao_time_2);
}

void rodada_truco(struct jogador time_1[], struct jogador time_2[], int qtd_jogadores_cada_time, int qtd_pontos_time1, int qtd_pontos_time2);

/*
 * @brief Função principal do programa.
 * Gerencia o fluxo do jogo, desde a configuração inicial até o loop principal.
 */
int main(void)
{
    // Variáveis para pontuação dos times (ainda não implementado o cálculo).
    int pontuacao_time_1 = 0;
    int pontuacao_time_2 = 0;
    int numero_jogadores;
    int qtd_jogadores_cada_time;

    // Configura o locale para suportar caracteres especiais, como acentos.
    setlocale(LC_ALL, "Portuguese");

    printf("Bem-vindo ao jogo de Truco!\n");
    printf("Por favor, informe o número de jogadores (2, 4 ou 6): ");
    // Lê o número de jogadores.
    // Note: Seria importante adicionar validação de entrada para garantir que o número seja 2, 4 ou 6.
    scanf("%d", &numero_jogadores);

    // Limpa o buffer de entrada após scanf para evitar problemas com fgets.
    while (getchar() != '\n')
        ;

    // Calcula quantos jogadores haverá em cada time.
    qtd_jogadores_cada_time = numero_jogadores / 2;

    // Declara os arrays de jogadores para cada time.
    struct jogador time_1_jogadores[qtd_jogadores_cada_time];
    struct jogador time_2_jogadores[qtd_jogadores_cada_time];

    printf("\n--- Configurando o Time 1 ---\n");
    adicionar_equipe(time_1_jogadores, qtd_jogadores_cada_time); // Adiciona e distribui cartas para o Time 1.

    printf("\n--- Configurando o Time 2 ---\n");
    adicionar_equipe(time_2_jogadores, qtd_jogadores_cada_time); // Adiciona e distribui cartas para o Time 2.

    printf("\n--- Equipes Configuradas ---\n");
    printf("\nTime 1:\n");
    exibir_time(time_1_jogadores, qtd_jogadores_cada_time); // Exibe os jogadores e suas mãos do Time 1.

    printf("\nTime 2:\n");
    exibir_time(time_2_jogadores, qtd_jogadores_cada_time); // Exibe os jogadores e suas mãos do Time 2.

    // O loop principal do jogo (ainda não implementado).
    // O jogo continuaria enquanto nenhum dos times atingisse a pontuação de 12.
    // while (pontuacao_time_1 < 12 && pontuacao_time_2 < 12)
    // {
    //     // Lógica para cada rodada do Truco:
    //     // - Embaralhar e distribuir cartas (já feito na inicialização, mas precisaria ser refeito a cada rodada).
    //     // - Jogadores jogam suas cartas.
    //     // - Determinar o vencedor da rodada.
    //     // - Atualizar pontuações.
    //     // - Lógica para 'truco', 'seis', 'nove', 'doze'.
    // }

    finalizar_jogo(time_1_jogadores, time_2_jogadores, pontuacao_time_1, pontuacao_time_2, qtd_jogadores_cada_time);

    printf("\n--- Fim do jogo ---\n");

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso.
}