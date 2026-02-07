#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define tamanho maximo de uma linha do csv e numero maximo de atletas unicos para armazenar os ids
#define MAX_LINE 4096
#define MAX_ATHLETES 200000

//remove espaços em branco do inicio e do fim de uma string, verifica se um id ja foi contado e extrai os campos necessarios de uma linha do csv
void trim(char *str);
int jaContado(int id, int *lista, int total);
void extrairCampos(char *linha, char *sex, char *noc, int *athlete_id);

//indice do começo e indice do fim de cada campo na linha do csv, pula espaços em branco e caracteres de nova linha, copia os campos para as variaveis correspondentes e finaliza as strings com o caractere nulo
void trim(char *str) {
    int inicio = 0;
    int fim = strlen(str) - 1;

    while (str[inicio] == ' ' || str[inicio] == '\n' || str[inicio] == '\r')
        inicio++;

    while (fim >= inicio &&
          (str[fim] == ' ' || str[fim] == '\n' || str[fim] == '\r'))
        fim--;

    int j = 0;
    for (int i = inicio; i <= fim; i++)
        str[j++] = str[i];

    str[j] = '\0';
}

//percorre ids ja guardados para verifica se o id do atleta atual ja foi contado, se sim retorna 1, se nao retorna 0
int jaContado(int id, int *lista, int total) {
    for (int i = 0; i < total; i++) {
        if (lista[i] == id)
            return 1;
    }
    return 0;
}


