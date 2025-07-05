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
    int qtd_cartas_restantes;
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
        jogador->qtd_cartas_restantes = 3;
    }
}

/**
 * @brief Adiciona jogadores a uma equipe, solicitando seus nomes e distribuindo cartas iniciais.
 *
 * Esta função itera sobre o número de jogadores especificado, chamando rotinas auxiliares
 * para obter o nome de cada jogador e para distribuir um conjunto inicial de cartas.
 *
 * @param time Um array de estruturas 'jogador' que representa os membros da equipe.
 * @param quantidade_jogadores O número total de jogadores nesta equipe.
 *
 * @note Presume que as funções 'adicionar_nome_jogador' e 'distribuir_cartas_jogador'
 * já estão definidas e são responsáveis pelas suas respectivas operações.
 * @see adicionar_nome_jogador
 * @see distribuir_cartas_jogador
 */
void adicionar_equipe(struct jogador time[], int quantidade_jogadores)
{
    for (int i = 0; i < quantidade_jogadores; i++)
    {
        adicionar_nome_jogador(&time[i]);    // Solicita e atribui o nome ao jogador.
        distribuir_cartas_jogador(&time[i]); // Distribui 3 cartas para a mão do jogador.
    }
}

/**
 * @brief Exibe as informações de uma única carta no formato "númeroNaipe".
 *
 * Esta função recebe uma estrutura 'carta' e imprime seu número e o caractere
 * correspondente ao seu naipe, utilizando um array global ou constante de naipes.
 *
 * @param carta A estrutura 'carta' contendo o número e o naipe a serem exibidos.
 *
 * @note Assume a existência de um array global 'NAIPES' (ex: char NAIPES[])
 * onde o índice 'carta.naipe' pode ser usado para acessar o caractere correto do naipe.
 */
void exibir_carta(struct carta carta)
{
    // Acessa o caractere do naipe usando o índice armazenado na carta.
    printf("%d%c ", carta.numero, NAIPES[carta.naipe]);
}

/**
 * @brief Exibe todas as cartas na mão de um jogador.
 *
 * Esta função itera sobre as cartas em um array que representa a mão de um jogador
 * e chama a função 'exibir_carta' para cada uma delas, formatando a saída com um prefixo "Mão:".
 *
 * @param mao Um array de estruturas 'carta' representando a mão completa do jogador.
 * Presume-se que a mão contém 3 cartas.
 *
 * @warning O tamanho da mão (3 cartas) está fixo nesta função. Considere passar o tamanho
 * como um parâmetro se a quantidade de cartas na mão puder variar.
 * @see exibir_carta
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

/**
 * @brief Exibe as informações detalhadas de todos os jogadores em uma equipe.
 *
 * Esta função percorre o array de jogadores de uma equipe, imprimindo o nome de cada jogador
 * e, em seguida, suas cartas na mão, através da chamada à função 'exibir_mao'.
 *
 * @param time Um array de estruturas 'jogador' que compõem a equipe.
 * @param quantidade_jogadores O número de jogadores presentes na equipe.
 *
 * @see exibir_mao
 */
void exibir_time(struct jogador time[], int quantidade_jogadores)
{
    for (int i = 0; i < quantidade_jogadores; i++)
    {
        printf("--- Jogador: %s ---\n", time[i].nome); // Exibe o nome do jogador.
        exibir_mao(time[i].mao);                       // Exibe as cartas na mão do jogador.
    }
}

/**
 * @brief Exibe a equipe vencedora do jogo.
 *
 * Esta função é chamada para anunciar o time ganhador, imprimindo um cabeçalho
 * e, em seguida, exibindo todos os jogadores e suas informações (assumindo que
 * 'exibir_time' já mostra nome e mão, o que pode ser uma redundância aqui se
 * o foco é apenas anunciar o vencedor).
 *
 * @param time Um array de estruturas 'jogador' representando a equipe vencedora.
 * @param quantidade_jogadores O número de jogadores na equipe vencedora.
 *
 * @note Esta função pode ser simplificada se 'exibir_time' já fornece a informação
 * suficiente. Pode ser mais direto imprimir "Time X Venceu!" e talvez um resumo.
 * @see exibir_time
 */
void exibir_ganhador(struct jogador time[], int quantidade_jogadores)
{
    printf("\n--- Ganhador do Jogo ---\n");
    exibir_time(time, quantidade_jogadores); // Exibe detalhes da equipe ganhadora.
}

/**
 * @brief Exibe a pontuação final de ambos os times ao término do jogo.
 *
 * Esta função imprime um cabeçalho e então mostra as pontuações acumuladas
 * do Time 1 e do Time 2 de forma clara.
 *
 * @param pontuacao_time_1 A pontuação total alcançada pelo Time 1.
 * @param pontuacao_time_2 A pontuação total alcançada pelo Time 2.
 */
void exibir_pontuacao_final(int pontuacao_time_1, int pontuacao_time_2)
{
    printf("\n--- Pontuação Final ---\n");
    printf("Time 1: %d pontos\n", pontuacao_time_1);
    printf("Time 2: %d pontos\n", pontuacao_time_2);
}

/**
 * @brief Gerencia o processo de finalização de uma partida de truco.
 *
 * Esta função determina qual equipe venceu o jogo com base nas pontuações finais,
 * chama a função para exibir o time ganhador e, por fim, mostra a pontuação final
 * de ambos os times.
 *
 * @param time_1 Array de estruturas 'jogador' representando o Time 1.
 * @param time_2 Array de estruturas 'jogador' representando o Time 2.
 * @param pontuacao_time_1 Pontuação total do Time 1.
 * @param pontuacao_time_2 Pontuação total do Time 2.
 * @param qtd_jagadores_cada_time O número de jogadores em cada time (assumindo que são iguais).
 *
 * @see exibir_ganhador
 * @see exibir_pontuacao_final
 */
void finalizar_jogo(struct jogador time_1[], struct jogador time_2[], int pontuacao_time_1, int pontuacao_time_2, int qtd_jagadores_cada_time)
{
    if (pontuacao_time_1 > pontuacao_time_2)
        exibir_ganhador(time_1, qtd_jagadores_cada_time); // Time 1 venceu.
    else
        exibir_ganhador(time_2, qtd_jagadores_cada_time); // Time 2 venceu (ou houve empate, tratada como vitória do Time 2).

    exibir_pontuacao_final(pontuacao_time_1, pontuacao_time_2); // Exibe as pontuações finais.
}

/**
 * @brief Função placeholder para a lógica de uma rodada de truco.
 *
 * Esta função deve conter toda a lógica para o desenvolvimento de uma rodada completa de truco,
 * incluindo jogadas de cartas, pedidos de truco, envido, flor, etc., e o cálculo dos pontos da rodada.
 *
 * @param time_1 Array de estruturas 'jogador' representando o Time 1.
 * @param time_2 Array de estruturas 'jogador' representando o Time 2.
 * @param qtd_jogadores_cada_time O número de jogadores em cada time.
 * @param qtd_pontos_time1 Pontuação atual do Time 1 (parâmetro de entrada/saída ou usar ponteiro se for modificar).
 * @param qtd_pontos_time2 Pontuação atual do Time 2 (parâmetro de entrada/saída ou usar ponteiro se for modificar).
 *
 * @note Atualmente, esta função está vazia e serve como um esqueleto para a implementação futura.
 */
void rodada_truco(struct jogador time_1[], struct jogador time_2[], int qtd_jogadores_cada_time, int *qtd_pontos_time1, int *qtd_pontos_time2)
{
    // Lógica da rodada de truco (jogadas, contagem de pontos, etc.)
}

/**
 * @brief Função placeholder para a lógica de um jogador pedir uma carta.
 *
 * Esta função seria responsável por gerenciar a interação com o jogador
 * para que ele escolha qual carta deseja jogar da sua mão. Pode incluir
 * validação da entrada do usuário.
 *
 * @note Atualmente, esta função está vazia e serve como um esqueleto para a implementação futura.
 * Provavelmente precisará de parâmetros para interagir com o jogador atual e sua mão.
 */
void pedir_carta_jogar(struct jogador jogador)
{
    printf("Qual carta deseja jogar?: ");
    for (int i = 0; i < jogador.qtd_cartas_restantes; i++)
        printf("Para carta %d%c digite - %d\n", jogador.mao->numero, jogador.mao->naipe, i + 1);
}

/**
 * @brief Solicita ao jogador qual carta ele deseja jogar.
 *
 * Esta função exibe uma mensagem no console para o jogador, pedindo que ele
 * indique qual carta de sua mão deseja utilizar na jogada atual.
 *
 * @param jogador A estrutura 'jogador' para a qual a pergunta está sendo feita.
 * Normalmente, esta função esperaria alguma entrada do usuário
 * que não está sendo capturada aqui.
 *
 * @note Esta função apenas exibe a mensagem. A lógica para ler a escolha do
 * jogador e validar a carta deve ser implementada aqui ou em uma função auxiliar.
 */
struct carta jogar_carta(struct jogador jogador)
{
    // Lógica para ler a entrada do jogador e processar a jogada da carta.
    int posicao_carta;
    do
    {
        scanf("%d", &posicao_carta);
        switch (posicao_carta)
        {
        case 1:
            return jogador.mao[1];
            break;
        case 2:
            return jogador.mao[2];
            break;
        case 3:
            return jogador.mao[3];
            break;
        default:
            printf("Valor inválido, digite novamente se atentatendo a ele");
        }
    } while (posicao_carta < 1 && posicao_carta > jogador.qtd_cartas_restantes);
}

/**
 * @brief Função placeholder para a lógica de pedir 'truco'.
 *
 * Esta função deve encapsular as regras e interações para um jogador
 * realizar um pedido de 'truco', incluindo a resposta do time adversário
 * (aceitar, aumentar ou fugir) e as consequências nos pontos da rodada.
 *
 * @note Atualmente, esta função está vazia e serve como um esqueleto para a implementação futura.
 * Provavelmente precisará de parâmetros para o estado atual do jogo,
 * os jogadores envolvidos e a pontuação da rodada.
 */
void pedir_truco(int *qtd_pontos_valendo)
{
    printf("Quanto deseja pedir: 3, 6, 9?");
    scanf("%d", &qtd_pontos_valendo);
}

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