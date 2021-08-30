#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#define KEY_CODE_ENTER 10
#define DELIMITADOR "|"


char campos[10][10]={
    "Sobrenome",
    "Nome",
    "Endereco",
    "Cidade",
    "Estado",
    "CEP"
};

char* input(char str[], int tam);
bool validaFile(FILE* file);
bool eof(FILE* file);
void mostraCampos(FILE* file);
int tamanhoProximoRegistro(FILE* file);
int convertCharToInt(char c);

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
        
        printf("------\n", cont++);
        mostraCampos(leitura);
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

void mostraCampos(FILE* file){
    int tamanho = tamanhoProximoRegistro(file);
    int campoPosisao = 0;
    char registro[tamanho];
    char * token;


    fread(registro, sizeof(char), tamanho, file);
    token = strtok(registro, DELIMITADOR);

    while(token!=NULL&&campoPosisao<6){
        printf("%s: %s\n", campos[campoPosisao], token);
        token = strtok(NULL, DELIMITADOR);
        campoPosisao++;
    }
}

int tamanhoProximoRegistro(FILE* file){
    char tam[2];
    tam[0] = fgetc(file);
    tam[1] = fgetc(file);
    
    int length = 10*convertCharToInt(tam[0])+ convertCharToInt(tam[1]); 
  
    return length;
}

int convertCharToInt(char c){
    return (int)(c-'0');
}