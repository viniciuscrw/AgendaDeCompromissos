#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

#define LEN 101
#define DLEN 201

typedef struct dma date;
typedef struct agenda_compromisso agenda;
typedef struct hrmin time;

//Funções - Manipulação e validação de dados
void trataString (char string[], int nc);

int validaCompromisso(agenda *compromisso, int index, int n);

int validaData(int dia, int mes, int ano);

int validaInput(int valor, int min, int max, char msg[31]);

void removePosicao(agenda *compromisso, int ini, int n);

void trocaPosicao(agenda *compromisso, int old_index, int new_index);
//

//Funções - Secundárias
void dataDoSistema (int *dia, int *mes, int *ano);

void horaDoSistema(int *hora, int *min);

int menuItem();

int getDiaDaSemana(int dia, int mes, int ano);

int percorreSemanas(agenda *compromisso, int n, int domingo, int dias_faltando, int dia, int mes, int ano);

int comparaMes(char mes[]);
//

//Funções - Arquivos
int persisteNum();

void persisteDados(agenda *compromisso, int n);

void reescreveDados(agenda *compromisso, int n);

void escreveDados(agenda *compromisso, int n);
//

//Funções - Menu
char menu();

int cadastrar(agenda *compromisso, int n);

void listar(agenda *compromisso, int inicio, int fim);

void alterar(agenda *compromisso, int n);

int buscaPalavraChave(agenda *compromisso, int n);

int buscaDataHora(agenda *compromisso, int n);

void ordemCronologica(agenda *compromisso, int n);

void listaPorMes(agenda *compromisso, int n);

void listaPorSemana(agenda *compromisso, int n);

void listaPorDia(agenda *compromisso, int n);

int removerAnteriores(agenda *compromisso, int n);

int removerCompromisso(agenda *compromisso, int n);
//


typedef struct dma
{
    int dia;
    int mes;
    int ano;
}date;

typedef struct hrmin
{
    int hora;
    int min;
}time;

typedef struct agenda_compromisso
{
    char titulo[LEN];
    char descricao[DLEN];
    date data;
    time horario;
    char local[LEN];
    time alarme;

}agenda;

#endif // DEFINICOES_H_INCLUDED
