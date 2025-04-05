#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TEXTO

int main(int argc, char *argv[]){
    //Seed de tempo e declaração de variáveis
    srand(time(NULL));
    int fator = 1;
    long int n;
    float elem1, elem2;
    double prodInt=0;
    float *vetor1, *vetor2;
    FILE *arquivo;
    size_t ret;

    if(argc<2){
        //fprintf(stderr, "Digite %s <dimensão> <nome do arquivo de saída>\n", argv[0]);
        fprintf(stderr, "Digite %s <dimensão>\n", argv[0]);
        return 3;
    }

    n = atoi(argv[1]);
    fprintf(stdout, "GERADOR DE VETORES\n");
    fprintf(stdout, "N = %ld\n\n", n);
    
    //inicialização de vetores
    vetor1 = (float*)malloc(sizeof(float)*n);
    if(!vetor1){
        fprintf(stderr, "Erro de alocao da memoria do vetor 1\n");
        return 1;
    }

    vetor2 = (float*)malloc(sizeof(float)*n);
    if(!vetor2){
        fprintf(stderr, "Erro de alocao da memoria do vetor 2\n");
        return 2;
    }

    //Preenchendo os vetores e calculando o produto interno
    for(long int i=0; i<n; i++) {
         elem1 = (rand() % MAX)/1.234 * fator;
         elem2 = (rand() % MAX)/1.432 * fator;
         vetor1[i] = elem1;
         vetor2[i] = elem2;
         prodInt+= elem1*elem2;
         fator*=-1;
    }

    //Mostrar valores atribuídos aos vetores e o produto interno
    #ifdef TEXTO   
    fprintf(stdout, "Valores do Vetor 1\n");
    for(long int i=0; i<n; i++) {
       fprintf(stdout, "%f ",vetor1[i]);
    }
    fprintf(stdout, "\n\n");

    fprintf(stdout, "Valores do Vetor 2\n");
    for(long int i=0; i<n; i++) {
       fprintf(stdout, "%f ",vetor2[i]);
    }
    fprintf(stdout, "\n\n");

    fprintf(stdout, "Produto Interno: %f\n\n", prodInt);

    #endif

    //Escrevendo no arquivo binário
    //abre o arquivo para escrita binaria
    char nomeArquivo[10];
    sprintf(nomeArquivo, "teste_N%ld", n);
    arquivo = fopen(nomeArquivo, "wb");
    if(!arquivo) {
       fprintf(stderr, "Erro de abertura do arquivo\n");
       return 4;
    }

    //Escreve a dimensão dos vetores
    ret = fwrite(&n, sizeof(long int), 1, arquivo);

    //Escreve os elementos dos vetores
    ret = fwrite(vetor1, sizeof(float), n, arquivo);
    if(ret < n) {
       fprintf(stderr, "Erro de escrita no  arquivo\n");
       return 4;
    }
    ret = fwrite(vetor2, sizeof(float), n, arquivo);
    if(ret < n) {
       fprintf(stderr, "Erro de escrita no  arquivo\n");
       return 5;
    }

    //Escreve o produto interno
    ret = fwrite(&prodInt, sizeof(double), 1, arquivo);
    
    //finaliza o uso das variaveis
    fclose(arquivo);
    free(vetor1);
    free(vetor2);
    return 0;
}