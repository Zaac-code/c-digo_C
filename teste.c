#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#define IDD_INPUTBOX 101
#define IDC_EDIT_INPUT 1001
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

//====================================================variáveis globais=========================================================================//
char mkd_original[] = "C:\\Users\\Zaac\\OneDrive\\"; //caminho para o diretório definido como variável global (método temporário)
char mkd[1024];
char name[1024], address[1024], cpf[1024], phone[1024], past[1024];

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CadastrarCliente(HWND hwnd);
void LerArquivo(HWND hwnd);
void EditarCadastro(HWND hwnd);
void ExcluirCadastro(HWND hwnd);
//===============================================================================================================================================//

//==========================================================Função principal=====================================================================//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
    memset(past,0,sizeof(past));
    memset(cpf,0,sizeof(cpf));
    strcpy(mkd, mkd_original);
    static HWND hEditName, hEditAddress, hEditCPF, hEditPhone, hEditPast;
    static HWND hButtonCadastro, hButtonLeitura, hButtonEdicao, hButtonExclusao;

    switch (uMsg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Nome:", WS_VISIBLE | WS_CHILD, 10, 10, 100, 20, hwnd, NULL, NULL, NULL);
            hEditName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 10, 200, 20, hwnd, (HMENU) ID_EDIT_NAME, NULL, NULL);

            CreateWindow("STATIC", "Endereco:", WS_VISIBLE | WS_CHILD, 10, 40, 100, 20, hwnd, NULL, NULL, NULL);
            hEditAddress = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 40, 200, 20, hwnd, (HMENU) ID_EDIT_ADDRESS, NULL, NULL);

            CreateWindow("STATIC", "CPF:", WS_VISIBLE | WS_CHILD, 10, 70, 100, 20, hwnd, NULL, NULL, NULL);
            hEditCPF = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 70, 200, 20, hwnd, (HMENU) ID_EDIT_CPF, NULL, NULL);

            CreateWindow("STATIC", "Telefone:", WS_VISIBLE | WS_CHILD, 10, 100, 100, 20, hwnd, NULL, NULL, NULL);
            hEditPhone = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 100, 200, 20, hwnd, (HMENU) ID_EDIT_PHONE, NULL, NULL);

            CreateWindow("STATIC", "Pasta:", WS_VISIBLE | WS_CHILD, 10, 130, 100, 20, hwnd, NULL, NULL, NULL);
            hEditPast = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 130, 200, 20, hwnd, (HMENU) ID_EDIT_PAST, NULL, NULL);

            hButtonCadastro = CreateWindow("BUTTON", "Cadastrar Cliente", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 160, 150, 30, hwnd, (HMENU) ID_BUTTON_SUBMIT, NULL, NULL);
            hButtonLeitura = CreateWindow("BUTTON", "Ler Arquivo", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 200, 150, 30, hwnd, (HMENU) ID_BUTTON_READ, NULL, NULL);
            hButtonEdicao = CreateWindow("BUTTON", "Editar Cadastro", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 240, 150, 30, hwnd, (HMENU) ID_BUTTON_EDIT, NULL, NULL);
            hButtonExclusao = CreateWindow("BUTTON", "Excluir Cadastro", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 280, 150, 30, hwnd, (HMENU) ID_BUTTON_DELETE, NULL, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BUTTON_SUBMIT:
                    CadastrarCliente(hwnd);
                    break;
                case ID_BUTTON_READ:
                    LerArquivo(hwnd);
                    break;
                case ID_BUTTON_EDIT:
                    EditarCadastro(hwnd);
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
    char filePath[2048];
    HWND hEditName = GetDlgItem(hwnd, ID_EDIT_NAME);
    HWND hEditAddress = GetDlgItem(hwnd, ID_EDIT_ADDRESS);
    HWND hEditCPF = GetDlgItem(hwnd, ID_EDIT_CPF);
    HWND hEditPhone = GetDlgItem(hwnd, ID_EDIT_PHONE);
    HWND hEditPast = GetDlgItem(hwnd, ID_EDIT_PAST);

    // Obter o texto dos controles
    GetWindowText(hEditName, name, sizeof(name));
    GetWindowText(hEditAddress, address, sizeof(address));
    GetWindowText(hEditCPF, cpf, sizeof(cpf));
    GetWindowText(hEditPhone, phone, sizeof(phone));
    GetWindowText(hEditPast, past, sizeof(past));

    // Remover o caractere de nova linha se presente
    name[strcspn(name, "\n")] = '\0';
    address[strcspn(address, "\n")] = '\0';
    cpf[strcspn(cpf, "\n")] = '\0';
    phone[strcspn(phone, "\n")] = '\0';
    past[strcspn(past, "\n")] = '\0';
    // Criar o caminho do arquivo
    snprintf(filePath, sizeof(filePath), "%s%s\\%s.txt", mkd, past, cpf);
    
    FILE *file;
    file = fopen(filePath, "w");
    if (file!=NULL) {
        fprintf(file, "Nome: %s\nEndereco: %s\nCPF: %s\nTelefone: %s", name, address, cpf, phone);
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
    HWND hEditCPF = GetDlgItem(hwnd, ID_EDIT_CPF);

    // Obter o CPF do controle
    GetWindowText(hEditCPF, cpf, sizeof(cpf));
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
//===============================================================================================================================================//

//====================================================Funçao que edita cadastro de clientes======================================================//
void EditarCadastro(HWND hwnd)
{
    char cpf[1024];
    char filePath[2048];
    FILE *file;
    FILE *tempFile;
    char linha[MAX_LINE_LENGTH];
    char tempFilePath[2048];
    const char *campo;
    char novoValor[MAX_LINE_LENGTH];
    HWND hEditCPF = GetDlgItem(hwnd, ID_EDIT_CPF);
    HWND hEditPastEditar = GetDlgItem(hwnd, ID_EDIT_PAST);

    // Obter o CPF e o nome da pasta do controle
    GetWindowText(hEditCPF, cpf, sizeof(cpf));
    GetWindowText(hEditPastEditar, past, sizeof(past));

    // Criar o caminho do arquivo
    snprintf(filePath, sizeof(filePath), "%s%s\\%s.txt", mkd, past, cpf);

    file = fopen(filePath, "r+");
    if (!file) {
        MessageBox(hwnd, "Erro ao abrir o arquivo para edição.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }

    snprintf(tempFilePath, sizeof(tempFilePath), "%s.temp", filePath);
    tempFile = fopen(tempFilePath, "w");
    if (!tempFile) {
        fclose(file);
        MessageBox(hwnd, "Erro ao criar arquivo temporário.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }
    int escolha;
    // Perguntar ao usuário qual campo deseja editar
    switch (escolha)
    {
        case 1:
            strcpy(campo, "Nome: ");
            GetWindowText(GetDlgItem(hwnd, ID_EDIT_NAME), novoValor, sizeof(novoValor));
            break;
        case 2:
            strcpy(campo, "Endereco: ");
            GetWindowText(GetDlgItem(hwnd, ID_EDIT_ADDRESS), novoValor, sizeof(novoValor));
            break;
        case 3:
            strcpy(campo, "Telefone: ");
            GetWindowText(GetDlgItem(hwnd, ID_EDIT_PHONE), novoValor, sizeof(novoValor));
            break;
        case 4:
            strcpy(campo, "CPF: ");
            GetWindowText(GetDlgItem(hwnd, ID_EDIT_CPF), novoValor, sizeof(novoValor));
            break;
        default:
            fclose(file);
            fclose(tempFile);
            MessageBox(hwnd, "Escolha inválida.", "Erro", MB_OK | MB_ICONERROR);
            return;
    }

    // Substituir o campo no arquivo
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
    if (remove(filePath) == 0 && rename(tempFilePath, filePath) == 0)
    {
        MessageBox(hwnd, "Cadastro atualizado com sucesso!", "Sucesso", MB_OK);
    }
    else{
        MessageBox(hwnd, "Erro ao atualizar o cadastro.", "Erro", MB_OK | MB_ICONERROR);
    }
}
//===============================================================================================================================================//

//====================================================Função que exclui cadastro de clientes=====================================================//
void ExcluirCadastro(HWND hwnd)
{
    char cpf[1024];
    char filePath[2048];

    HWND hEditCPF = GetDlgItem(hwnd, ID_EDIT_CPF);
    HWND hEditPastExcluir = GetDlgItem(hwnd, ID_EDIT_PAST);

    // Obter o CPF e o nome da pasta do controle
    GetWindowText(hEditCPF, cpf, sizeof(cpf));
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