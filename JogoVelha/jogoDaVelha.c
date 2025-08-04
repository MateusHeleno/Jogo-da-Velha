#include "jogoDaVelha.h"

int main()
{
    srand(time(NULL));
    int y = 0, escolha, jogadas = 0;
    int vitX = 0, vitO = 0, empate = 0;
    char decisao = 's';
    char simbolo = 'x';

    char nome[30];
    printf("Qual o seu nome : ");
    fgets(nome, 30, stdin);
    retiraN(nome);

    printf("Vamos jogar um jogo da velha !!");
    printf("\n\n");
    while (decisao == 's' || decisao == 'S')
    {
        char tabuleiroFixo[MAX][MAX] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}};

        char tabuleiroMovel[MAX][MAX] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}};

        int tentativas = 1;
        do
        {
            if (tentativas > 1) // controla para aparecer a mensagem de erro só após a segunda tentativa
                printf("Jogada inválida,escolha novamente\n");
            printf("Você quer jogar contra um amigo ou contra um bot: ");
            printf("\n1-- AMIGO\n2-- BOT Fácil\n3-- BOT Médio\n\n");
            scanf("%d", &escolha);
            printf("\n\n");
            tentativas++;
        } while (escolha > 3 || escolha < 1);
        
        modoDeJogo(tabuleiroFixo,tabuleiroMovel,y,&vitX,&vitO,&empate,escolha,simbolo);

        printf("Você deseja jogar novamente ?\nDigite s para jogar novamente ou outra coisa para sair: ");
        limpar_buffer();
        scanf("%c", &decisao);
        jogadas++;
        printf("\n");
    }

    printf("Agora que terminou, você jogou %d de partida!\n", jogadas);
    printf("%s teve %d vitórias, o O teve %d vitórias, e teve %d empates.\n", nome, vitX, vitO, empate);

    return 0;
}

