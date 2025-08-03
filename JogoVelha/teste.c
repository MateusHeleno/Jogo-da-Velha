#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 3

void limpar_buffer();                                                   // limpa o buffer
void mapa(char tabuleiroFixo[MAX][MAX], char tabuleiroMovel[MAX][MAX]); // Imprime o mapa
void retiraN(char nome[]);                                              // Retira o \n do fgets
int vitoria(char tabuleiroFixo[MAX][MAX]);                              // Confere se teve vitória
int validacao(char tabuleiroFixo[MAX][MAX],int y);
void troca(char tabuleiroFixo[MAX][MAX], char tabuleiroMovel[MAX][MAX], int y,char simbolo);                                        // coloca o x
void modoDeJogo(char tabuleiroFixo[MAX][MAX], char tabuleiroMovel[MAX][MAX], int y, int *vitX, int *vitO, int *empate,int escolha,char simbolo); // Modo que permite jogar contra amigos
void usuario(int *y);
void botFacil(int *y);
void botMedio(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int *y);
void escolhaDoModo(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int *y, int escolha);

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

void mapa(char tabuleiroFixo[MAX][MAX], char tabuleiroMovel[MAX][MAX])
{

    for (int i = 0; i < MAX; i++)
    { // Comandar as lindas dos dois tabuleiros simultanemante
        for (int j = 0; j < MAX; j++)
        { // Imprimir a linha do primeiro tabuleiro
            printf("| %c ", tabuleiroFixo[i][j]);
        }
        printf("|\t\t");
        for (int j = 0; j < MAX; j++)
        { // Imprimir a linha do segundo tabuleiro
            printf("| %c ", tabuleiroMovel[i][j]);
        }
        if (i < 2)
            printf("|\n-------------\t\t-------------\n");
        else
            printf("|\n");
    }
}

void limpar_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void retiraN(char nome[])
{
    int tam = strlen(nome);
    if (nome[tam - 1] == '\n') // remove o \n do fgets
        nome[tam - 1] = '\0'; 
}

int vitoria(char tabuleiroMovel[MAX][MAX])
{
    for (int i = 0; i < 3; i++)
    { // Verificar condições de vitória horizontais
        if (tabuleiroMovel[i][0] == tabuleiroMovel[i][1] && tabuleiroMovel[i][1] == tabuleiroMovel[i][2] && (tabuleiroMovel[i][0] == 'x' || tabuleiroMovel[i][0] == 'o'))
        {
            return 1;
        }
    }

    for (int j = 0; j < 3; j++)
    { // Verificar condições de vitória verticais
        if (tabuleiroMovel[0][j] == tabuleiroMovel[1][j] && tabuleiroMovel[1][j] == tabuleiroMovel[2][j] && (tabuleiroMovel[0][j] == 'x' || tabuleiroMovel[0][j] == 'o'))
        {
            return 1;
        }
    }

    // Verificar condições de vitória diagonais
    // Diagonal principal
    if (tabuleiroMovel[0][0] == tabuleiroMovel[1][1] && tabuleiroMovel[1][1] == tabuleiroMovel[2][2] && (tabuleiroMovel[0][0] == 'x' || tabuleiroMovel[0][0] == 'o'))
    {
        return 1;
    }
    // Diagonal secundária
    if (tabuleiroMovel[0][2] == tabuleiroMovel[1][1] && tabuleiroMovel[1][1] == tabuleiroMovel[2][0] && (tabuleiroMovel[0][2] == 'x' || tabuleiroMovel[0][2] == 'o'))
    {
        return 1;
    }

    return 0;
}

int validacao(char tabuleiroFixo[MAX][MAX],int y)
{
    if (y <= 9 && y > 0)
    {
        int indice = 1;
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                if (y == indice)
                {                                                    // o indice vai andando as posições que pode ir de 1 a 9, pra ver se pode ser feito a escolha
                    if (tabuleiroFixo[i][j] == (char)('0' + indice)) // transformar o indice em ASCII
                        return 1;
                    else
                        return 0;
                }
                indice++;
            }
        }
    }
    else
        return 0;
    return 0;
}

void troca(char tabuleiroFixo[MAX][MAX], char tabuleiroMovel[MAX][MAX], int y,char simbolo)
{
    if (y <= 9 && y > 0)
    {
        int indice = 1;
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                if (y == indice)
                { //  quando ele fizer a escolha, vai mudar a casa respectiva
                    tabuleiroFixo[i][j] = '-';
                    tabuleiroMovel[i][j] = simbolo;
                }
                indice++;
            }
        }
    }
}

void modoDeJogo(char tabuleiroFixo[MAX][MAX], char tabuleiroMovel[MAX][MAX], int y, int *vitX, int *vitO, int *empate,int escolha,char simbolo)
{
    mapa(tabuleiroFixo, tabuleiroMovel);

    usuario(&y);
    while (!validacao(tabuleiroFixo,y)) // se difrente de um jogada nao existe,entrar em loop
    {
        printf("Jogada inválida!! Essa casa não existe, ou já está ocupada !");
        usuario(&y);
    }
    printf("\n");

    simbolo = 'x';
    troca(tabuleiroFixo, tabuleiroMovel, y,simbolo);
    mapa(tabuleiroFixo, tabuleiroMovel);
    for (int i = 1; i <= 4; i++)
    {
        escolhaDoModo(tabuleiroFixo,tabuleiroMovel,&y,escolha);
        while (!validacao(tabuleiroFixo,y))
        {
            if(escolha == 1) 
                printf("Jogada inválida!! Essa casa não existe, ou já está ocupada !");
            escolhaDoModo(tabuleiroFixo,tabuleiroMovel,&y,escolha);
        }
        printf("\n");

        simbolo = 'o';
        troca(tabuleiroFixo, tabuleiroMovel, y,simbolo);
        mapa(tabuleiroFixo, tabuleiroMovel);

        if (vitoria(tabuleiroMovel))
        {
            printf("\nO o(bolinha) ganhou!! \n");
            (*vitO)++;
            break;
        }

        usuario(&y);

        while (!validacao(tabuleiroFixo,y))
        {
            printf("Jogada inválida!! Essa casa não existe, ou já está ocupada !");
            usuario(&y);
        }
        printf("\n");

        simbolo = 'x';
        troca(tabuleiroFixo, tabuleiroMovel, y,simbolo);
        mapa(tabuleiroFixo, tabuleiroMovel);
        if (vitoria(tabuleiroMovel))
        {
            printf("\nO x ganhou !! \n");
            (*vitX)++;
            break;
        }
    }
    if (!vitoria(tabuleiroMovel))
    {
        printf("\nO jogo deu velha !!\n");
        (*empate)++;
    }
}

void usuario(int *y)
{
    printf("\nEscolha um número: ");
    scanf("%d", y);
}

void botFacil(int *y)
{
    *y = (rand() % 9) + 1;
}

void escolhaDoModo(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int *y, int escolha)
{
    switch (escolha)
    {
    case 1:
        usuario(y);
        break;
    case 2:
        botFacil(y);
        break;
    case 3:
        botMedio(tabuleiroFixo,tabuleiroMovel,y);
        break;
    }
}


void botMedio(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int *y) {
    char letra[] = {'o','x'};
    for (int l = 0;l < 2;l++){//na primeira iteração confere a vitoria, na segunda bloqueia
        // Verificar linhas horizontais
        for (int i = 0; i < MAX; i++) { // o for anda com com a linha, e os if consideram todos os casos
            
            if (tabuleiroMovel[i][0] == letra[l] && tabuleiroMovel[i][1] == letra[l]) {  
                *y = (i * MAX) + 3;
                if(validacao(tabuleiroFixo,*y))
                    return;
            }
            else if (tabuleiroMovel[i][0] == letra[l] && tabuleiroMovel[i][2] == letra[l]) { 
                *y = (i * MAX) + 2;
                if(validacao(tabuleiroFixo,*y))
                    return;
            }
            else if (tabuleiroMovel[i][1] == letra[l] && tabuleiroMovel[i][2] == letra[l]) { 
                *y = (i * MAX) + 1;
                if(validacao(tabuleiroFixo,*y))
                    return;
            }
        }

        // Verificar colunas verticais
        for (int j = 0; j < MAX; j++) { // o for anda com a coluna, e os if consideram todos os casos
            if (tabuleiroMovel[0][j] == letra[l] && tabuleiroMovel[1][j] == letra[l]) { 
                *y = j + 7;
                if(validacao(tabuleiroFixo,*y))
                    return;
            }
            else if (tabuleiroMovel[0][j] == letra[l] && tabuleiroMovel[2][j] == letra[l]) { 
                *y = j + 4;
                if(validacao(tabuleiroFixo,*y))
                    return;
            }
            else if (tabuleiroMovel[1][j] == letra[l] && tabuleiroMovel[2][j] == letra[l]) { 
                *y = j + 1;
                if(validacao(tabuleiroFixo,*y))
                    return;
            }
        }

        // Verificar diagonais para ganhar
        
        if (tabuleiroMovel[0][0] == letra[l] && tabuleiroMovel[1][1] == letra[l]) { 
            *y = 9;
            if(validacao(tabuleiroFixo,*y))
                    return;
        }
        else if (tabuleiroMovel[0][0] == letra[l] && tabuleiroMovel[2][2] == letra[l]) { 
            *y = 5;
            if(validacao(tabuleiroFixo,*y))
                    return;
        }
        else if (tabuleiroMovel[1][1] == letra[l] && tabuleiroMovel[2][2] == letra[l]) { 
            *y = 1;
            if(validacao(tabuleiroFixo,*y))
                    return;
        }

        //anti diagonal
        if (tabuleiroMovel[0][2] == letra[l] && tabuleiroMovel[1][1] == letra[l]) {
            *y = 7;
            if(validacao(tabuleiroFixo,*y))
                    return;
        }
    else  if (tabuleiroMovel[0][2] == letra[l] && tabuleiroMovel[2][0] == letra[l]) { 
            *y = 5;
            if(validacao(tabuleiroFixo,*y))
                    return;
        }
        else if (tabuleiroMovel[1][1] == letra[l] && tabuleiroMovel[2][0] == letra[l]) { 
            *y = 3;
            if(validacao(tabuleiroFixo,*y))
                    return;
        }
    }
    //se nao tiver uma jogada antes, o bot faz ela de maneira aleatoria
    botFacil(y);

}

