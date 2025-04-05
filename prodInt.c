#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 

#define TEXTO

long int n;
float *vetor1;
float *vetor2;
int nThreads;
int bloco;
double *retThread;

void *produtoInterno(void *arg);

int main(int argc, char *argv[]){
    //Inicialização de variáveis
    FILE *arquivo;
    size_t ret; 
    double prodInt_ori;
    pthread_t *tid;

    if(argc < 3){ 
        printf("Use: %s <arquivo de entrada> <numero de threads> \n", argv[0]); 
        return 1; 
    }

    tid = (pthread_t*)malloc(sizeof(pthread_t)*nThreads);

    //Abertura de arquivo
    arquivo = fopen(argv[1], "rb");
    if(arquivo==NULL){
        printf("Falha na abertura do arquivo %s\n", argv[1]); 
        return 2; 
    }

    //Obtendo n
    ret = fread(&n, sizeof(long int), 1, arquivo);
    if(!ret) {
        fprintf(stderr, "Erro de leitura das dimensoes do vetor\n");
        return 3;
    }

    //Inicializando vetores, alocando memória e obtendo valores
    vetor1 = (float*) malloc (sizeof(float) * n);
    vetor2 = (float*) malloc (sizeof(float) * n);

    if(vetor1==NULL) { 
      printf("Erro na alocação de memória do vetor 1\n"); 
      return 4;
    }
    if(vetor2==NULL) { 
        printf("Erro na alocação de memória do vetor 2\n"); 
        return 5;
    }

    ret = fread(vetor1, sizeof(float), n, arquivo);
    if(ret < n) {
       fprintf(stderr, "Erro de leitura dos elementos do vetor 1\n");
       return 6;
    }
    
    ret = fread(vetor2, sizeof(float), n, arquivo);
    if(ret < n) {
       fprintf(stderr, "Erro de leitura dos elementos do vetor 2\n");
       return 7;
    }   

    ret = fread(&prodInt_ori, sizeof(double), 1, arquivo);
    if(!ret){
        fprintf(stderr, "Erro de leitura do valor do produto interno\n");
        return 8;
    }

    //Checagem de obtenção de valores do arquivo
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

    fprintf(stdout, "Produto Interno: %f\n\n", prodInt_ori);

    #endif

    //Início da concorrência
    nThreads = atoi(argv[2]);
    if(nThreads>n) nThreads = n;

    //Tamanho do bloco por thread
    bloco = n/nThreads;

    for(long int i=0; i<nThreads; i++) {
        if (pthread_create(&tid[i], NULL, produtoInterno, (void*)(bloco*i))) {
           printf("Erro na criação da thread %ld\n", i); 
           return 9;
        }
    }

    double resultado = 0;
    for(int i=0; i<nThreads; i++) {
        if (pthread_join(tid[i], (void *) &retThread)) {
           printf("Erro no join das threads\n"); 
           return 10;
        }
        resultado += *retThread;
        free(retThread);
    }
    double e = abs(prodInt_ori-resultado)/prodInt_ori;
    fprintf(stdout, "A variação relativa é de %lf\n", e);
    free(vetor1);
    free(vetor2);
    free(arquivo);
    free(retThread);
}

void *produtoInterno(void *arg){
    long int id = (long int)arg;
    double *resultado = (double*)malloc(sizeof(double));
    if (resultado==NULL) {
        fprintf(stderr, "Erro no produto interno\n");
        exit(-1);
    }
    *resultado = 0;
    for (int i = id; i < id + bloco; i++){
        *resultado+= vetor1[i]*vetor2[i];
    }
    pthread_exit((void*)resultado);
}