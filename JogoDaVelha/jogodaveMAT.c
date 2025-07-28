#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAX 3

void limpar_buffer();//limpa o buffer
void mapa(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX]);//Imprime o mapa
int vitoria(char tabuleiroFixo[MAX][MAX]);//Confere se teve vitória
int validacao(int y,char tabuleiroFixo[MAX][MAX]);
void trocaX(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y);//coloca o x
void trocaO(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y);//coloca o 0
void modoDeJogo(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y,int *vitX,int *vitO,int *empate); // Modo que permite jogar contra amigos

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
        char tabuleiroFixo[MAX][MAX] = {
            {'1', '2', '3'}, 
            {'4', '5', '6'},
            {'7', '8', '9'}
        };                      

        char tabuleiroMovel[MAX][MAX] = {
            {'1', '2', '3'}, 
            {'4', '5', '6'},
            {'7', '8', '9'}
        };
        
        int tentativas = 1;
            do{   
                if (tentativas > 1) // controla para aparecer a mensagem de erro só após a segunda tentativa
                    printf("Jogada inválida,escolha novamente\n"); 
                printf("Você quer jogar contra um amigo ou contra um bot: "); 
                printf("\n1-- AMIGO\n2-- BOT Fácil\n3-- BOT Médio\n\n");
                scanf("%d",&escolha);
                printf("\n\n");
                tentativas++;
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

    printf("Agora que terminou, você jogou %d de partida!\n",jogadas);
    printf("%s teve %d vitórias, o O teve %d vitórias, e teve %d empates.\n",nome,vitX,vitO,empate);
    
    return 0;
}
    
void mapa(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX] ){
    
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

int vitoria(char tabuleiroMovel[MAX][MAX]) {
    for (int i = 0; i < 3; i++) { // Verificar condições de vitória horizontais
        if (tabuleiroMovel[i][0] == tabuleiroMovel[i][1] && tabuleiroMovel[i][1] == tabuleiroMovel[i][2] && (tabuleiroMovel[i][0] == 'x' || tabuleiroMovel[i][0] == 'o')) {
            return 1; 
        }
    }

    for (int j = 0; j < 3; j++) {  // Verificar condições de vitória verticais
        if (tabuleiroMovel[0][j] == tabuleiroMovel[1][j] && tabuleiroMovel[1][j] == tabuleiroMovel[2][j] && (tabuleiroMovel[0][j] == 'x' || tabuleiroMovel[0][j] == 'o')) {
            return 1; 
        }
    }

    // Verificar condições de vitória diagonais
    // Diagonal principal
    if (tabuleiroMovel[0][0] == tabuleiroMovel[1][1] && tabuleiroMovel[1][1] == tabuleiroMovel[2][2] && (tabuleiroMovel[0][0] == 'x' || tabuleiroMovel[0][0] == 'o')) {
        return 1; 
    }
    // Diagonal secundária
    if (tabuleiroMovel[0][2] == tabuleiroMovel[1][1] && tabuleiroMovel[1][1] == tabuleiroMovel[2][0] && (tabuleiroMovel[0][2] == 'x' || tabuleiroMovel[0][2] == 'o')) {
        return 1; 
    }

    return 0;
}

int validacao(int y,char tabuleiroFixo[MAX][MAX])
{
    if( y <= 9 && y > 0){
        int indice = 1;
        for(int i = 0; i < MAX; i++){ 
            for (int j = 0; j < MAX; j++){
                if( y == indice){  // o indice vai andando as posições que pode ir de 1 a 9, pra ver se pode ser feito a escolha
                        if (tabuleiroFixo[i][j] == (char)('0' + indice))//transformar o indice em ASCII
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

void trocaX(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y){
    if( y <= 9 && y > 0){
        int indice = 1;
        for(int i = 0; i < MAX; i++){ 
            for (int j = 0; j < MAX; j++){
                if( y == indice){ //  quando ele fizer a escolha, vai mudar a casa respectiva
                    tabuleiroFixo[i][j] = '-';
                    tabuleiroMovel[i][j] = 'x';
                }
            }

        }
    }

}

void trocaO(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y){
    if( y <= 9 && y > 0){
        int indice = 1;
        for(int i = 0; i < MAX; i++){ 
            for (int j = 0; j < MAX; j++){
                if( y == indice){ //  quando ele fizer a escolha, vai mudar a casa respectiva
                    tabuleiroFixo[i][j] = '-';
                    tabuleiroMovel[i][j] = 'o';
                }
            }

        }
    }

}

void modoDeJogo(char tabuleiroFixo[MAX][MAX],char tabuleiroMovel[MAX][MAX],int y,int *vitX,int *vitO,int *empate){
    mapa(tabuleiroFixo, tabuleiroMovel);
            
    printf("\nEscolha um número: ");
    scanf("%d",&y);
    while(!validacao(y, tabuleiroFixo)) // se difrente de um jogada nao existe,entrar em loop
    {  
        printf("Jogada inválida!! Essa casa não existe, ou já está ocupada !");
        printf("\nEscolha um número: ");
        scanf("%d",&y);
    }
    printf("\n");
    
    trocaX(tabuleiroFixo,tabuleiroMovel,y);
    mapa(tabuleiroFixo, tabuleiroMovel);
    for(int i = 1; i<= 4;i++)
    {  
        printf("\nEscolha um número: ");
        scanf("%d",&y);
        while(!validacao(y, tabuleiroFixo))
        {  
            printf("Jogada inválida!! Essa casa não existe, ou já está ocupada !");
            printf("\nEscolha um número: ");
            scanf("%d",&y);
        }
        printf("\n");

        trocaO(tabuleiroFixo,tabuleiroMovel,y);
        mapa(tabuleiroFixo, tabuleiroMovel);

        if(vitoria(tabuleiroMovel))
        {   
            printf("\nO o(bolinha) ganhou!! \n");
            (*vitO)++;
            break;
        }         
               
        printf("\nEscolha um número: ");
        scanf("%d",&y);
                
        while(!validacao(y, tabuleiroFixo))
        {  
            printf("Jogada inválida!! Essa casa não existe, ou já está ocupada !");
            printf("\nEscolha um número: ");
            scanf("%d",&y);
        }
        printf("\n");
                
        trocaX(tabuleiroFixo,tabuleiroMovel,y);
        mapa(tabuleiroFixo, tabuleiroMovel);
        if(vitoria(tabuleiroMovel))
        {   
            printf("O x ganhou !! \n");
            (*vitX)++;
            break;
        }
                    
    }   
    if(!vitoria(tabuleiroMovel)){ 
        printf("\nO jogo deu velha !!\n");
        (*empate)++;
    }
}
