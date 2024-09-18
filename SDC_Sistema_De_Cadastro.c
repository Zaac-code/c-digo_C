#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

// Identificadores para a caixa de entrada (input box)
//#define IDD_INPUTBOX 101
//#define IDC_EDIT_INPUT 1001

// Outros identificadores
#define MAX_LINE_LENGTH 256
#define ID_EDIT_NAME 1
#define ID_EDIT_ADDRESS 2
#define ID_EDIT_CPF 3
#define ID_EDIT_PHONE 4
#define ID_BUTTON_SUBMIT 5
#define ID_BUTTON_READ 6
#define ID_BUTTON_EDIT 7
#define ID_BUTTON_DELETE 8
#define ID_EDIT_PAST 9
#define ID_EDIT_CAMP 10
#define ID_EDIT_COD 11
#define ID_BUTTON_ATT 12
#define ID_EDIT_CAMPO 13
#define MAX_BUFFER 1024

char name_edit[MAX_BUFFER] = {0};
char cod[MAX_BUFFER] = {0};


//====================================================variáveis globais=========================================================================//
char mkd_original[] = "C:\\Users\\Zaac\\OneDrive\\"; //caminho para o diretório definido como variável global (método temporário)
char mkd[1024];
char name[1024], address[1024], cpf[1024], phone[1024], past[1024],filePath[2048];
char *campo;
int escolha=0;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow);
int WINAPI WinMain2(HINSTANCE hInstance2, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowEdit(HWND hwnd2, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CadastrarCliente(HWND hwnd);
void LerArquivo(HWND hwnd);
void ExcluirCadastro(HWND hwnd);
//===============================================================================================================================================//

//==========================================================Função principal=====================================================================//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "SDC - Sistema de Cadastro",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
//===============================================================================================================================================//

//====================================================Função de processamento da janela==========================================================//
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    (void)lParam;
    strcpy(mkd, mkd_original);
    //static HWND hEditName, hEditAddress, hEditCPF, hEditPhone, hEditPast;
    //static HWND hButtonCadastro, hButtonLeitura, hButtonEdicao, hButtonExclusao;

    switch (uMsg)
    {
        case WM_CREATE:
            CreateWindow("STATIC", "Nome:", WS_VISIBLE | WS_CHILD, 10, 10, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 10, 200, 20, hwnd, (HMENU) ID_EDIT_NAME, NULL, NULL);

            CreateWindow("STATIC", "Endereco:", WS_VISIBLE | WS_CHILD, 10, 40, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 40, 200, 20, hwnd, (HMENU) ID_EDIT_ADDRESS, NULL, NULL);

            CreateWindow("STATIC", "Telefone:", WS_VISIBLE | WS_CHILD, 10, 70, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 70, 200, 20, hwnd, (HMENU) ID_EDIT_PHONE, NULL, NULL);

            CreateWindow("STATIC", "CPF:", WS_VISIBLE | WS_CHILD, 10, 100, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 100, 200, 20, hwnd, (HMENU) ID_EDIT_CPF, NULL, NULL);


            CreateWindow("STATIC", "Pasta:", WS_VISIBLE | WS_CHILD, 10, 130, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 130, 200, 20, hwnd, (HMENU) ID_EDIT_PAST, NULL, NULL);

            CreateWindow("BUTTON", "Cadastrar Cliente", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 160, 150, 30, hwnd, (HMENU) ID_BUTTON_SUBMIT, NULL, NULL);
            CreateWindow("BUTTON", "Ler Arquivo", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 200, 150, 30, hwnd, (HMENU) ID_BUTTON_READ, NULL, NULL);
            CreateWindow("BUTTON", "Editar Cadastro", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 240, 150, 30, hwnd, (HMENU) ID_BUTTON_EDIT, NULL, NULL);
            CreateWindow("BUTTON", "Excluir Cadastro", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 280, 150, 30, hwnd, (HMENU) ID_BUTTON_DELETE, NULL, NULL);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BUTTON_SUBMIT:
                    memset(past,0,sizeof(past));
                    memset(cpf,0,sizeof(cpf));
                    memset(filePath,0,sizeof(filePath));
                    CadastrarCliente(hwnd);
                    break;
                case ID_BUTTON_READ:
                    memset(past,0,sizeof(past));
                    memset(cpf,0,sizeof(cpf));
                    memset(filePath,0,sizeof(filePath));
                    LerArquivo(hwnd);
                    break;
                case ID_BUTTON_EDIT:
                    GetWindowText(GetDlgItem(hwnd, ID_EDIT_CPF), cpf, sizeof(cpf));
                    GetWindowText(GetDlgItem(hwnd, ID_EDIT_PAST), past, sizeof(past));
                    WinMain2(GetModuleHandle(NULL), NULL, NULL, SW_SHOWNORMAL);
                    break;
                case ID_BUTTON_DELETE:
                    ExcluirCadastro(hwnd);
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
//===============================================================================================================================================//
//=========================================================função de cadastro de clientes========================================================//
void CadastrarCliente(HWND hwnd)
{
    HWND hCadName = GetDlgItem(hwnd, ID_EDIT_NAME);
    HWND hCadAddress = GetDlgItem(hwnd, ID_EDIT_ADDRESS);
    HWND hCadPhone = GetDlgItem(hwnd, ID_EDIT_PHONE);
    HWND hCadCPF = GetDlgItem(hwnd, ID_EDIT_CPF);
    HWND hCadPast = GetDlgItem(hwnd, ID_EDIT_PAST);

    // Obter o texto dos controles
    GetWindowText(hCadName, name, sizeof(name));
    GetWindowText(hCadAddress, address, sizeof(address));
    GetWindowText(hCadPhone, phone, sizeof(phone));
    GetWindowText(hCadCPF, cpf, sizeof(cpf));
    GetWindowText(hCadPast, past, sizeof(past));

    // Remover o caractere de nova linha se presente
    name[strcspn(name, "\n")] = '\0';
    address[strcspn(address, "\n")] = '\0';
    phone[strcspn(phone, "\n")] = '\0';
    cpf[strcspn(cpf, "\n")] = '\0';
    past[strcspn(past, "\n")] = '\0';
    // Criar o caminho do arquivo
    snprintf(filePath, sizeof(filePath), "%s%s\\%s.txt", mkd, past, cpf);
    
    FILE *file;
    file = fopen(filePath, "w");
    if (file!=NULL)
    {
        fprintf(file, "Nome: %s\nEndereco: %s\nTelefone: %s\nCPF: %s", name, address, phone, cpf);
        fclose(file);
        MessageBox(hwnd, "Cadastro realizado com sucesso!", "Sucesso", MB_OK);
    }
    else
    {
        MessageBox(hwnd, "Erro ao salvar o cadastro.", "Erro", MB_OK | MB_ICONERROR);
    }
}
//===============================================================================================================================================//

//====================================Função que ler arquivos txt dentro de um diretório escolhido pelo usuário===================================//
void LerArquivo(HWND hwnd)
{
    char cpf[1024];
    char filePath[2048];
    char buffer[2048];
    HWND hLerCPF = GetDlgItem(hwnd, ID_EDIT_CPF);

    // Obter o CPF do controle
    GetWindowText(hLerCPF, cpf, sizeof(cpf));
    GetWindowText(GetDlgItem(hwnd, ID_EDIT_PAST), past, sizeof(past));

    // Criar o caminho do arquivo
    snprintf(filePath, sizeof(filePath), "%s%s\\%s.txt", mkd, past, cpf);
    
    FILE *file;
    file = fopen(filePath, "r");
    if (file)
    {
        while (fgets(buffer, sizeof(buffer), file)) {
            MessageBox(hwnd, buffer, "Conteudo do Arquivo", MB_OK);
        }
        
        fclose(file);
    }
    else
    {
        MessageBox(hwnd, "Erro ao abrir o arquivo.", "Erro", MB_OK | MB_ICONERROR);
    }
}
//====================================================Funçao que edita cadastro de clientes======================================================//
// Função para editar o campo selecionado

//===============================================================================================================================================//

//====================================================Função que exclui cadastro de clientes=====================================================//
void ExcluirCadastro(HWND hwnd)
{
    char cpf[1024];
    char filePath[2048];

    HWND hExcluirCPF = GetDlgItem(hwnd, ID_EDIT_CPF);
    HWND hEditPastExcluir = GetDlgItem(hwnd, ID_EDIT_PAST);

    // Obter o CPF e o nome da pasta do controle
    GetWindowText(hExcluirCPF, cpf, sizeof(cpf));
    GetWindowText(hEditPastExcluir, past, sizeof(past));

    // Criar o caminho do arquivo
    snprintf(filePath, sizeof(filePath), "%s%s\\%s.txt", mkd, past, cpf);

    if (remove(filePath) == 0) {
        MessageBox(hwnd, "Cadastro deletado com sucesso!", "Sucesso", MB_OK);
    } else {
        MessageBox(hwnd, "Erro ao excluir o cadastro.", "Erro", MB_OK | MB_ICONERROR);
    }
}
//===============================================================================================================================================//
// Função de processamento da janela de edição
int WINAPI WinMain2(HINSTANCE hInstance2, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    const char CLASS_NAME2[] = "Edit Window Class";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowEdit;
    wc.hInstance = hInstance2;
    wc.lpszClassName = CLASS_NAME2;

    RegisterClass(&wc);

    HWND hwnd2 = CreateWindowEx(
        0,
        CLASS_NAME2,
        "Editar Cadastro",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance2,
        NULL
    );

    if (hwnd2 == NULL) {
        return 0;
    }

    ShowWindow(hwnd2, nCmdShow);
    UpdateWindow(hwnd2);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Função de processamento do diálogo de edição
LRESULT CALLBACK WindowEdit(HWND hwnd2, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    (void)lParam;
    switch (uMsg)
    {
        case WM_CREATE:
            CreateWindow("STATIC", "Codigo do Campo: digite 1 p/ editar Nome | 2 p/ editar Endereco | 3 p/ editar Telefone | 4 p/ editar CPF", WS_VISIBLE | WS_CHILD, 50, 50, 800, 20, hwnd2, NULL, NULL, NULL);
            CreateWindow("STATIC", "Codigo do campo:", WS_VISIBLE | WS_CHILD, 10, 100, 150, 20, hwnd2, NULL, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 155, 100, 200, 20, hwnd2, (HMENU) ID_EDIT_COD, NULL, NULL);
            CreateWindow("STATIC", "Novo valor do campo:", WS_VISIBLE | WS_CHILD, 10, 125, 250, 20, hwnd2, NULL, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 155, 125, 300, 20, hwnd2, (HMENU) ID_EDIT_CAMPO, NULL, NULL);

            CreateWindow("BUTTON", "Atualizar Valor", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 160, 150, 30, hwnd2, (HMENU) ID_BUTTON_ATT, NULL, NULL);
            
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case ID_BUTTON_ATT:
                    GetWindowText(GetDlgItem(hwnd2, ID_EDIT_CAMPO), name_edit, sizeof(name_edit));
                    GetWindowText(GetDlgItem(hwnd2, ID_EDIT_COD), cod, sizeof(cod));
                    FILE *file;
                    // Criar o caminho do arquivo
                    snprintf(filePath, sizeof(filePath), "%s%s\\%s.txt", mkd, past, cpf);
                    printf("filepath: %s",filePath);
                    file = fopen(filePath, "r");
                    if (!file)
                    {
                        MessageBox(hwnd2, "Erro ao abrir o arquivo para edicao.", "Erro", MB_OK | MB_ICONERROR);
                        break;
                    }

                    if(strcmp(cod,"1")==0)
                    {
                        escolha = 1;
                    }

                    if(strcmp(cod,"2")==0)
                    {
                        escolha = 2;
                    }

                    if(strcmp(cod,"3")==0)
                    {
                        escolha = 3;
                    }

                    if(strcmp(cod,"4")==0)
                    {
                        escolha = 4;
                    }
                    switch (escolha)
                    {
                        case 1:
                            campo = "Nome: ";
                            break;
                        case 2:
                            campo = "Endereco: ";
                            break;
                        case 3:
                            campo = "Telefone: ";
                            break;
                        case 4:
                            campo = "CPF: ";
                            break;
                        default:
                            MessageBox(hwnd2, "Erro ao editar arquivo !", "ERRO", MB_OK);
                            break;
                    }
                    FILE *tempFile = fopen("temp.txt", "w");
                    if (tempFile == NULL)
                    {
                        MessageBox(hwnd2, "Erro ao criar arquivo temporario!", "ERRO", MB_OK);
                        break;
                    }


                    char linha[MAX_LINE_LENGTH];
                    while (fgets(linha, sizeof(linha), file))
                    {
                        if(strncmp(linha, campo, strlen(campo)) == 0)
                        {
                            fprintf(tempFile, "%s%s\n", campo, name_edit);
                        }
                        else
                        {
                            fprintf(tempFile, "%s", linha);
                        }
                    }
                    fclose(file);
                    fclose(tempFile);
                    // Substituir o arquivo original pelo arquivo temporário
                    if (remove(filePath) != 0)
                    {
                        break;
                    }

                    if (rename("temp.txt", filePath) != 0)
                    {
                        break;
                    }  
                    //editarCampo(file, campo, name_edit);
                    MessageBox(hwnd2, "Cadastro atualizado com sucesso!", "Sucesso", MB_OK);
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd2, uMsg, wParam, lParam);
    }

    return 0;
}
