#include <stdio.h>
#include <stdlib.h>

int main(void){

    struct ficha_cl{

        char nome[40];
        char endereco[100];
        char cpf[100];
        char telefone[100];
    };

    struct ficha_cl cliente;

    printf("\n==================digite o nome do cliente==================\n\n");
    fgets(cliente.nome,40,stdin);

    printf("\n==================digite o endereco do cliente==================\n\n");
    fgets(cliente.endereco,100,stdin);

    printf("\n==================digite o cpf do cliente==================\n\n");
    fgets(cliente.cpf,100,stdin);

    printf("\n==================digite o telefone do cliente==================\n\n");
    fgets(cliente.telefone,100,stdin);

    printf("%s\n%s\n%s\n%s\n", cliente.nome, cliente.endereco, cliente.cpf, cliente.telefone);

    FILE *file;
    file = fopen("cliente.txt","w");

    fprintf(file,"\n%s\n%s\n%s\n%s",cliente.nome, cliente.endereco,cliente.telefone,cliente.cpf);
    fclose(file);
    return (0);
}
