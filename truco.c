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
const char NAIPES[] = {'C', 'E', 'O', 'P'}; // Copas, Espadas, Ouros, Paus

struct carta
{
    int numero; // 1 = 'A', 2 a 7, 8 = 'Q', 9 = 'J', 10 = 'K'
    char naipe; // 'C' = Copas, 'E' = Espadas, 'O' = Ouros, 'P' = Paus
};

struct jogador
{
    char nome[50];
    struct carta mao[3]; // Mão do jogador, contendo 3 cartas
};

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

/*
Função para sortear o numero da carta
@param numero máximo que a carta pode receber
@retun o numero que a carta receberá
*/
int sorteio_numero(int max)
{
    return gerar_numero_aleatorio(max);
}

/*
Função para sortear o naipe da carta
@retun o naipe que a carta reberá
*/
char sorteio_naipe()
{
    return NAIPES[gerar_numero_aleatorio(3)];
}

/*
Função para a criação da carta de um jogador
@param o sturct da carta a ser criada
@return a mão com as cartas para jogo
*/
struct carta sorteio_carta(struct carta carta)
{
}

/*
Função para adicionar o nome a um jogador a partir do que o usuário digitar
@param o struct do jogador
@return o struct do jogador atualizado com o seu nome
*/
void adicionar_nome_jogado(struct jogador *jogador)
{
    fgets(jogador->nome, sizeof jogador->nome, stdin);
}

/*
Função para a   
*/
void adicionar_carta()
{
}

void adicionar_jogador()
{
}

void adicionar_equipe(struct jogador time[], int quantidade_jogadores)
{
    for (int i = 0; i < quantidade_jogadores; i++)
        adicionar_nome_jogado(&time[i]);
}

void exibir_mao(struct carta mao[])
{
    printf("%d %c, ", mao[0].numero, mao[0].naipe);
    printf("%d %c, ", mao[1].numero, mao[1].naipe);
    printf("%d %c, ", mao[2].numero, mao[2].naipe);
}

void exibir_time(struct jogador time[], int quantidade_jogadores)
{
    for (int i = 0; i < quantidade_jogadores; i++)
    {
        printf("Jogador: %s\n", time[i].nome);
        printf("Tem na mão: ");
        exibir_mao(time[i].mao);
    }
}

int main(void)
{
    char entrada[50];
    int pontuacao_time_1 = 0;
    int pontuacao_time_2 = 0;

    printf("Bem-vindo ao jogo de Truco!\n");
    printf("Poderia informar o número de jogadores? (2, 4 ou 6)\n");
    int numero_jogadores;
    scanf("%d", &numero_jogadores);

    int jogadores_cada_time = numero_jogadores / 2;

    struct jogador time_1_jogadores[jogadores_cada_time];
    struct jogador time_2_jogadores[jogadores_cada_time];

    printf("Digite os nomes dos jogadores do primeiro time:\n");
    adicionar_equipe(time_1_jogadores, jogadores_cada_time);

    printf("Digite os nomes dos jogadores do primeiro time:\n");
    adicionar_equipe(time_1_jogadores, jogadores_cada_time);

    // while (pontuacao_time_1 < 12 && pontuacao_time_2 < 12)
    // {
    // }

    return 0;
}