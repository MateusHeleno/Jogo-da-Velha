#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAX 3

void limpar_buffer();
void mapa(int tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX]);
void modoAmigos(int tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y,int *vitX,int *vitO,int *empate);
int vitoria(char tabuleiro[MAX][MAX]);

int main(){
    srand(time(NULL));
    int y=0,escolha,jogadas=0;
    int vitX = 0,vitO = 0 ,empate = 0;
    char decisao='s';
    
    char nome[30];
    printf("Qual o seu nome : ");
    fgets(nome,30,stdin);

    printf("Vamos jogar um jogo da velha !!");
    printf("\n\n");
    while(decisao == 's' || decisao == 'S')
    { 
        int tabuleiroFixo[MAX][MAX] = {
            {1, 2, 3}, 
            {4, 5, 6},
            {7, 8, 9}
        };                      

        char tabuleiroMovel[MAX][MAX] = {
            {'1', '2', '3'}, 
            {'4', '5', '6'},
            {'7', '8', '9'}
        };
        
        int inicio = 1;
            do{   
                if (!inicio) // controla para aparecer a mensagem de erro só após a segunda tentativa
                    printf("Jogada inválida,escolha novamente\n"); 
                printf("Você quer jogar contra um amigo ou contra um bot: "); 
                printf("\n1-- AMIGO\n2-- BOT Fácil\n3-- BOT Médio\n\n");
                scanf("%d",&escolha);
                printf("\n\n");
                inicio++;
            }while(escolha > 3 || escolha < 1);
            switch(escolha)
            {
                case 1:           
                    modoAmigos(tabuleiroFixo,tabuleiroMovel,y,&vitX,&vitO,&empate);//modo  amigos     
                    break;

                case 2:
                    modoBotFacil(tabuleiroFixo,tabuleiroMovel,y,&vitX,&vitO,&empate);
                    break; 

                case 3:
                    modoBotMedio(tabuleiroFixo,tabuleiroMovel,y,&vitX,&vitO,&empate);        
                    break;
                }     
            printf("Você deseja jogar novamente ?\nDigite s para jogar novamente ou outra coisa para sair: ");
            limpar_buffer();
            scanf("%c",&decisao);
            jogadas++;
            printf("\n");
    }  

    return 0;
}
    
void mapa(int tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX] ){
    
    for(int i = 0; i < MAX; i++){  // Comandar as lindas dos dois tabuleiros simultanemante
        for (int j =0;j <MAX;j++){ // Imprimir a linha do primeiro tabuleiro
            printf("| %d ",tabuleiroFixo[i][j]);
        }
        printf("|\t\t");
        for (int j =0;j <MAX;j++){ // Imprimir a linha do segundo tabuleiro
            printf("| %c ",tabuleiroMovel[i][j]);
        }
        if (i<2)
            printf("|\n-------------\t\t-------------\n");
        else 
            printf("|");
    }  
}

void limpar_buffer() 
{
   int ch;
   while ((ch = getchar()) != '\n' && ch != EOF);
}

void modoAmigos(int tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y,int *vitX,int *vitO,int *empate){
}

int vitoria(char tabuleiro[MAX][MAX]) {
    for (int i = 0; i < 3; i++) { // Verificar condições de vitória horizontais
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && (tabuleiro[i][0] == 'x' || tabuleiro[i][0] == 'o')) {
            return 1; 
        }
    }

    for (int j = 0; j < 3; j++) {  // Verificar condições de vitória verticais
        if (tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j] && (tabuleiro[0][j] == 'x' || tabuleiro[0][j] == 'o')) {
            return 1; 
        }
    }

    // Verificar condições de vitória diagonais
    // Diagonal principal
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && (tabuleiro[0][0] == 'x' || tabuleiro[0][0] == 'o')) {
        return 1; 
    }
    // Diagonal secundária
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && (tabuleiro[0][2] == 'x' || tabuleiro[0][2] == 'o')) {
        return 1; 
    }

    return 0;
}