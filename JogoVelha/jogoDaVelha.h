#ifndef JOGODAVELHA_H
#define JOGODAVELHA_H

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

#endif // JOGODAVELHA_H