#include<stdio.h>
#include<stdlib.h>

#define KEY_CODE_ENTER 10

typedef struct {
     char nome[30];
     char sobrenome[40];
     char endereco[50];
     char cidade[50];
     char estado[50];
     char cep[10];
} Pessoa;


char* input(char str[], int tam);
int inputInt();
void limparBuffer();
Pessoa leiaDadosPessoa();
void pesistePessoaEmFile(Pessoa p, FILE* file);


int main(){
    char str[20];
    FILE* saida;
    int numeroDeRegistros = 0, cont = 1;

    puts("Insira um nome para o arquivo de saida: ");
    input(str, 20);
    puts("Numero de registro para serem adicionados:");
    numeroDeRegistros = inputInt();
    limparBuffer();

    saida = fopen(str, "a");
    while(numeroDeRegistros-- > 0){
        printf("------ Inserindo registro %02d -------\n", cont);
        Pessoa p = leiaDadosPessoa();
        pesistePessoaEmFile(p, saida);
        cont+=1;
        puts("");
    }

    fclose(saida);
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

int inputInt(){
    int x;
    scanf("%d", &x);
    return x;
}

void limparBuffer(){
    getchar();
}

Pessoa leiaDadosPessoa(){
    Pessoa* p = (Pessoa *) malloc(sizeof(Pessoa));

    printf("Insira um nome: ");
    input(p->nome, 30);
    printf("Insira um sobrenome: ");
    input(p->sobrenome, 40);
    printf("Insira um endereco: ");
    input(p->endereco, 50);
    printf("Insira uma cidade: ");
    input(p->cidade, 50);
    printf("Insira uma estado: ");
    input(p->estado, 50);
    printf("Insira uma cep: ");
    input(p->cep, 10);

    return *p;
}

void pesistePessoaEmFile(Pessoa p, FILE* file){
    fseek(file, 0, SEEK_END);

    fprintf(file, "%s|", p.sobrenome);
    fprintf(file, "%s|", p.nome);
    fprintf(file, "%s|", p.endereco);
    fprintf(file, "%s|", p.cidade);
    fprintf(file, "%s|", p.estado);
    fprintf(file, "%s|", p.cep);

    fseek(file, 0, SEEK_SET);
}