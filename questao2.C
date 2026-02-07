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

void extrairCampos(char *linha, char *sex, char *noc, int *athlete_id) {
    /*
        Esta função faz a leitura de uma linha de um arquivo CSV e extrai
        apenas alguns campos específicos. Ela percorre a linha caractere
        por caractere, separando os campos pelas vírgulas, mas respeitando
        os casos em que o conteúdo está entre aspas, para não quebrar campos
        que possuem vírgulas internas.
    */

    int coluna = 1;
    int dentroAspas = 0;
    char campo[512];
    int j = 0;

    /*
        As variáveis de saída são inicializadas para evitar lixo de memória.
        Durante a leitura, quando o fim de um campo é detectado, a função
        verifica a coluna atual e, se for uma das colunas desejadas, copia
        o valor correspondente: sexo (coluna 2), NOC do país (coluna 7)
        e ID do atleta (coluna 8).
    */

    sex[0] = '\0';
    noc[0] = '\0';
    *athlete_id = -1;

    for (int i = 0; linha[i] != '\0'; i++) {

        if (linha[i] == '"') {
            dentroAspas = !dentroAspas;
            continue;
        }

        if ((linha[i] == ',' && !dentroAspas) || linha[i] == '\n') {

            campo[j] = '\0';

            if (coluna == 2)
                strcpy(sex, campo);
            else if (coluna == 7)
                strcpy(noc, campo);
            else if (coluna == 8)
                *athlete_id = atoi(campo);

            coluna++;
            j = 0;
        } else {
            if (j < 511)
                campo[j++] = linha[i];
        }
    }

    if (j > 0 && coluna == 8) {
        campo[j] = '\0';
        *athlete_id = atoi(campo);
    }
}

