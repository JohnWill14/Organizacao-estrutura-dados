#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#define KEY_CODE_ENTER 10
#define DELIMITADOR '|'

typedef struct {
     char nome[30];
     char sobrenome[40];
     char endereco[50];
     char cidade[50];
     char estado[50];
     char cep[10];
} Pessoa;


char* input(char str[], int tam);
bool validaFile(FILE* file);
bool eof(FILE* file);
Pessoa proximaPessoa(FILE* file);
void proximoCampo(char campo[], FILE* file);
void mostraPessoa(Pessoa p);


int main(){
    char str[20];
    FILE* leitura;
    int cont = 1;

    puts("Insira um nome para o arquivo de leitura: ");
    input(str, 20);

    leitura = fopen(str, "r");
    if(validaFile(leitura)){
        printf( "Erro ao ler o arquivo.txt\n");
        exit(1);
    }

    while(!eof(leitura)){
        Pessoa p = proximaPessoa(leitura);
        printf("------ Registro %02d -------\n", cont++);
        mostraPessoa(p);
        puts("");
    }

    fclose(leitura);
    return 0;
}


char* input(char str[], int tam){
    char c;
    int i = 0;

    while((c = getchar()) != KEY_CODE_ENTER ){
        if(i<=tam-1){
            str[i] = c;
            i+=1;
        }
    }
    str[i] = '\0';

    return str;
}

bool validaFile(FILE* file){
    return file == NULL;
}

bool eof(FILE* file){
    bool eof = false;

    if(fgetc(file) == EOF)
        eof = true;
    fseek(file, -1, SEEK_CUR);

    return eof;    
}

Pessoa proximaPessoa(FILE* file){
    Pessoa* p = (Pessoa *) malloc(sizeof(Pessoa));

    proximoCampo(p->sobrenome, file);
    proximoCampo(p->nome, file);
    proximoCampo(p->endereco, file);
    proximoCampo(p->cidade, file);
    proximoCampo(p->estado, file);
    proximoCampo(p->cep, file);

    return *p;
}

void proximoCampo(char campo[], FILE* file){
    char c;
    int i=0;

    c=fgetc(file);
    while(c != DELIMITADOR && c != EOF){
        campo[i] =  c;
        i++;
        c=fgetc(file);
    }
    campo[i] = '\0';
}

void mostraPessoa(Pessoa p){
    printf("Sobrenome: %s\n", p.sobrenome);
    printf("Nome: %s\n", p.nome);
    printf("Endereco: %s\n", p.endereco);
    printf("Cidade: %s\n", p.cidade);
    printf("Estado: %s\n", p.estado);
    printf("CEP: %s\n", p.cep);
}

