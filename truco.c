/*
Descrição: Jogo de Truco
Requer: Número par de jogadores (2, 4 ou 6)
Asegura: mostrar o resultado do jogo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variável de controle para garantir que srand() seja chamada apenas uma vez
static int gerador_semeado = 0;

// Constante para os naipes das cartas
const int NAIPES[] = {'C', 'E', 'O', 'P'}; // Copas, Espadas, Ouros, Paus

/*
Função para gerar um número aleatório entre 1 e max (inclusive).
@param numero máximo (max) que o número aleatório pode atingir.
@return um número aleatório entre 1 e max.
*/

int gerar_numero_aleatorio(int max)
{
    // Semeia o gerador de números aleatórios se ainda não foi semeado.
    // Isso é feito apenas uma vez para toda a execução do programa.
    if (!gerador_semeado)
    {
        srand((unsigned int)time(NULL));
        gerador_semeado = 1;
    }
    // Gera um número aleatório e usa o operador de módulo (%) para colocá-lo no intervalo.
    // (rand() % 9) gera números de 0 a 8. Somando 1, temos de 1 a 9.
    return (rand() % max) + 1;
}

int sorteio_numero(int min, int max)
{
}

struct carta
{
    int numero; // 1 = 'A', 2 a 7, 8 = 'Q', 9 = 'J', 10 = 'K'
    char naipe; // 'C' = Copas, 'E' = Espadas, 'O' = Ouros, 'P' = Paus
};

sorteio_carta(void)
{
}

struct jogador
{
    char nome[50];
    struct carta mao[3]; // Mão do jogador, contendo 3 cartas
};

int main(void)
{
    int pontuacao_time_1 = 0;
    int pontuacao_time_2 = 0;

    printf("Bem-vindo ao jogo de Truco!\n");
    printf("Poderia informar o número de jogadores? (2, 4 ou 6)\n");
    int numero_jogadores;
    scanf("%d", &numero_jogadores);

    struct jogador time_1_jogadores[numero_jogadores / 2];
    struct jogador time_2_jogadores[numero_jogadores / 2];

    while (pontuacao_time_1 < 12 && pontuacao_time_2 < 12)
    {
        /* code */
    }

    return 0;
}