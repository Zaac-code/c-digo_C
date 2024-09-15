#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <direct.h>

//================================================================Protótipos======================================================================//
void cadastra_cliente(); void ler_arquivo();int main(void);void exclui_cadastro();void edita_cadastro();void ler_arquivo();int menu();
void editarCampo(FILE *file, const char *campo, const char *novoValor);

//===============================================================================================================================================//

//==========================================Variáveis globais Para criação de diretórios e arquivos txt==========================================//
char *nome_pasta;      //variável que carrega o nome da pasta/ diretório que será armazenado o arquivo txt
char *nome_dir;        //variável que cria o diretório/pasta 
char nome_ficha[1024]; //variável que armazena o arquivo txt da ficha do cliente
char aux[1024];        //variável auxiliar utilizada para concatenação de strings
char aux2[1024];       //variável auxiliar utilizada para concatenação de strings
char mkd_original[] = "C:\\Users\\Zaac\\OneDrive\\"; //caminho para o diretório definido como variável global (método temporário)
char mkd[1024];
int escolha =0;
FILE *file;            //ponteiro que atribui a variável file a função FILE
char nome_past[1024];
#define MAX_LINE_LENGTH 256
//===============================================================================================================================================//

//==================================================struct da ficha do cliente informações de cadastro===========================================//
struct ficha_cl
{
    char nome[1024];
    char endereco[1024];
    char cpf[1024]; 
    char telefone[1024];
};
struct ficha_cl cliente; //variável criada a partir da struct
//===============================================================================================================================================//
 
//=========================================================função de cadastro de clientes========================================================//
void cadastra_cliente()
{
    system("cls"); //comando que limpa todo o conteúdo do prompt
    
    printf("=============================SDC==============================\n");
    printf("======================Cadastrar cliente=======================\n");

    printf("\n==================digite o nome do cliente==================\n\n");
    fgets(cliente.nome,sizeof(cliente.nome), stdin);//armazena o valor digitado pelo usuário dentro da variável nome dentro da struct cliente e o coloca dentro do arquivo txt

    printf("\n==================digite o endereco do cliente==================\n\n");
    fgets(cliente.endereco,sizeof(cliente.endereco), stdin);//armazena o valor digitado pelo usuário dentro da variável endereco dentro da struct cliente e o coloca dentro do arquivo txt

    printf("\n==================digite o cpf do cliente==================\n\n");
    fgets(cliente.cpf,sizeof(cliente.cpf),stdin);//armazena o valor digitado pelo usuário dentro da variável cpf dentro da struct cliente e o coloca dentro do arquivo txt

    printf("\n==================digite o telefone do cliente==================\n\n");
    fgets(cliente.telefone,sizeof(cliente.telefone),stdin);//armazena o valor digitado pelo usuário dentro da variável telefone dentro da struct cliente e o coloca dentro do arquivo txt

    printf("\n==================digite o nome da pasta deste arquivo==================\n\n");
    scanf("%s", aux);//coleta o valor digitado pelo usuário e o coloca dentro da variável aux

    strcpy(aux2,cliente.cpf); //copia o valor da variável cpf e coloca dentro da variável aux2
    nome_dir = strcat(mkd,aux); //concatena a variável mkd com a variável aux, juntando o caminho do diretório ao nome definido pelo usário

    _mkdir(nome_dir);//cria um diretório e habilita a possibilidade de armazenamento, o local da criação do diretório está presente dentro da variável mkd, com o nome definido dentro da variável aux, que foram concatenadas e transformadas na variável nome_dir
    aux2 [strcspn(aux2, "\n")] ='\0';//a função strcspn varre a variável aux2 em busca do parâmetros passado que foi a presença de um "\n" e quando encontrado ela o remove da variável
    sprintf(nome_ficha,"\\%s.txt",aux2);//formata a variável nome_ficha, com o valor da variável aux2 e os carcteres "\\" e ".txt", exemplo: aux = 2222222, nome_ficha = \\2222222.txt
    nome_pasta = strcat(nome_dir,nome_ficha);//nome pasta recebe o valor de nome_dir+nome_ficha (concatenados)

    file = fopen(nome_pasta,"w");//passa o comando fopen que abre o arquivo com os parâmetros/valores dentro da variável nome_pasta 
    if (file){
        fprintf(file,"\nNome - %s\nEndereco - %s\nTelefone - %s\nCPF - %s",cliente.nome, cliente.endereco,cliente.telefone,cliente.cpf);
        fclose(file);//fecha o arquivo file
        printf("\nCadastro realizado com sucesso\n");
        system("pause");
        main();
    }
    else
    {
        perror("erro ao abrir arquivo!!!");
        system("pause");
        main();
    }
   main();
}
//===============================================================================================================================================//


//====================================Função que le arquivos txt dentro de um diretório escolhido pelo usuário===================================//
void ler_arquivo()
{

    system("cls");
    char nome_pasta_dir[1024];
    char nome_past[1024];
    char buffer[2048];
    memset(nome_past,0,sizeof(nome_past));
    memset(nome_pasta_dir,0,sizeof(nome_pasta_dir));
    memset(buffer,0,sizeof(buffer));
    system("cls");

    printf("=============================SDC==============================\n");
    printf("======================Leitura de cadastro=====================\n");
    
    printf("\n==================digite o cpf do cliente==================\n\n");
    fgets(cliente.cpf,sizeof(cliente.cpf),stdin);

    printf("\n==================Digite o nome da pasta do arquivo==================\n\n");
    scanf("%s", nome_pasta_dir);
    getchar();
    cliente.cpf[strcspn(cliente.cpf, "\n")] = '\0'; // Remove o '\n' do final
    snprintf(nome_past, sizeof(nome_past), "%s%s\\%s.txt", mkd, nome_pasta_dir, cliente.cpf);
    file = fopen(nome_past, "r");

    
    while (fgets(buffer, sizeof(buffer), file)){
        printf("%s", buffer);
    }
    if (file) {
        printf("\nArquivo aberto com sucesso!!!\n");
    }
    else{
        perror("erro ao abrir arquivo!!!");
        printf("\n%s\n",nome_past);
        system("pause");
        main();;
    }
    fclose(file);
    system("pause");
    main();
}
//===============================================================================================================================================//


//====================================================Funçao que edita cadastro de clientes======================================================//

void edita_cadastro()
{
// Abrir o arquivo original para leitura
    char nome_pasta_dir[1024];
    memset(nome_pasta_dir,0,sizeof(nome_pasta_dir));
    system("cls");
 
    printf("=============================SDC==============================\n");
    printf("========================Editar cadastro=======================\n");

    printf("\n==================Digite o cpf do cliente==================\n\n");
    fgets(cliente.cpf, sizeof(cliente.cpf), stdin);

    printf("\n==================Digite o nome da pasta do arquivo==================\n\n");
    scanf("%s", nome_pasta_dir);
    getchar();
    cliente.cpf[strcspn(cliente.cpf, "\n")] = '\0'; // Remove o '\n' do final
    snprintf(nome_past, sizeof(nome_past), "%s%s\\%s.txt", mkd, nome_pasta_dir, cliente.cpf);

    file = fopen(nome_past, "r");

    // Exibir o menu e obter a escolha do usuário
    int escolha = menu();

    // Escolher o campo a ser editado
    const char *campo;
    switch (escolha) {
        case 1:
            campo = "Nome - ";
            break;
        case 2:
            campo = "Endereço - ";
            break;
        case 3:
            campo = "Telefone - ";
            break;
        case 4:
            campo = "CPF - ";
            break;
        default:
            printf("Escolha inválida.\n");
            fclose(file);
            system("pause");
            main();
    }

    // Obter o novo valor do usuário
    char novoValor[MAX_LINE_LENGTH];
    system("cls");
    printf("\nDigite o novo valor para %s ", campo);
    fgets(novoValor, sizeof(novoValor), stdin);
    // Remover o caractere de nova linha se presente
    novoValor[strcspn(novoValor, "\n")] = '\0';

    // Editar o campo no arquivo
    editarCampo(file, campo, novoValor);

    printf("Cadastro atualizado com sucesso!\n");
    system("pause");
    main( );
}

int menu() {
    int choice;
    printf("Escolha o campo a ser editado:\n");
    printf("1. Nome\n");
    printf("2. Endereco\n");
    printf("3. Telefone\n");
    printf("4. CPF\n");
    printf("Digite o numero correspondente: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Limpar o buffer do stdin
    return choice;
}

// Função para editar o campo selecionado
void editarCampo(FILE *file, const char *campo, const char *novoValor) {
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Erro ao criar arquivo temporário");
        exit(1);
    }

    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, sizeof(linha), file)) {
        if (strncmp(linha, campo, strlen(campo)) == 0) {
            fprintf(tempFile, "%s%s\n", campo, novoValor);
        } else {
            fprintf(tempFile, "%s", linha);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Substituir o arquivo original pelo arquivo temporário
    if (remove(nome_past) != 0) {
        perror("Erro ao remover o arquivo original");
        system("pause");
        main();
    }
    if (rename("temp.txt", nome_past) != 0) {
        perror("Erro ao renomear o arquivo temporário");
        system("pause");
        main();
    }
}


//===============================================================================================================================================//




//====================================================Função que exclui cadastro de clientes=====================================================//
void exclui_cadastro()
{
    
    char nome_pasta_dir[1024];
    memset(nome_pasta_dir,0,sizeof(nome_pasta_dir));
    strcpy(mkd, mkd_original);
    system("cls");
 
    printf("=============================SDC==============================\n");
    printf("=======================Excluir cadastro========================\n");

    printf("\n==================Digite o cpf do cliente==================\n\n");
    fgets(cliente.cpf, sizeof(cliente.cpf), stdin);

    printf("\n==================Digite o nome da pasta do arquivo==================\n\n");
    scanf("%s", nome_pasta_dir);
    getchar();
    cliente.cpf[strcspn(cliente.cpf, "\n")] = '\0'; // Remove o '\n' do final
    snprintf(nome_past, sizeof(nome_past), "%s%s\\%s.txt", mkd, nome_pasta_dir, cliente.cpf);

    file = fopen(nome_past, "r");

    if (file) {
        printf("Arquivo removido com sucesso!!!\n");
        fclose(file);
        printf("%d",remove(nome_past));
        system("pause");
        main();
    }
    else{
        perror("\nerro ao abrir arquivo!!!\n");
        printf("\n%s\n",nome_past);
        system("pause");
        main();
    }
}