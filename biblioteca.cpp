#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

FILE *arquivo, *auxiliar;

struct emprestimos{
    char dataEmprestimo[10], dataDevolucao[10], usuario[150];
};

struct livros{
    int codigo, paginas;
    char titulo[150], autor[255], editora[50], area[30];
    struct emprestimos emp;
} livro;

int opcaoMenu, codLivro, posicao;
char opc;

int main() {
    do {
        cout << "|||||||||||SISTEMA DE GERENCIAMENTO DE BIBLIOTECA|||||||||||||" << endl;
        cout << "1 - Cadastro" << endl;
        cout << "2 - Alteração" << endl;
        cout << "3 - Exclusão" << endl;
        cout << "4 - Empréstimo" << endl;
        cout << "5 - Devolução" << endl;
        cout << "6 - Consulta de Livro" << endl;
        cout << "7 - Livros disponíveis" << endl;
        cout << "8 - Listagem geral de livros" << endl;
        cout << "9 - Sair" << endl << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcaoMenu;
        cout << endl << endl << endl;

        switch (opcaoMenu){
        case 1:
            cout << "CADASTRO DE LIVROS" << endl << endl;
            cout << "Deseja cadastrar um livro? [S/N]: ";
            cin >> opc;

            while (opc == 'S'){
                cout << "Informe os dados do livro" << endl;
                cout << "Código: ";
                cin >> livro.codigo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Área de conhecimento [E - Exatas, H - Humanas, B - Biológicas]: ";
                cin.get(livro.area, 29);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Título: ";
                cin.get(livro.titulo, 149);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Autor(es): ";
                cin.get(livro.autor, 254);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Editora: ";
                cin.get(livro.editora, 49);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Número de páginas: ";
                cin >> livro.paginas;

                arquivo = fopen("dados.dat", "ab");
                if (arquivo == NULL) {
                    arquivo = fopen("dados.dat", "wb");
                }

                if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                    cout << "Livro cadastrado com sucesso!";
                } else {
                    cout << "Erro ao cadastrar o livro!";
                }
                fclose(arquivo);

                cin.ignore();
                cin.get();

                cout << "Deseja cadastrar outro livro? [S/N]: ";
                cin >> opc;
            }
            break;
        case 2:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL){
                cout << "ALTERAÇÃO DE LIVRO" << endl;
                cout << "Deseja alterar um livro? [S/N]: " << endl;
                cin >> opc;
                cout << "Informe o código do livro: " << endl;
                cin >> codLivro;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                posicao = -1;

                while ((!feof(arquivo)) && (opc == 'S')){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    posicao++;
                    if (codLivro == livro.codigo){
                        cout << "Informe os novos dados do livro: " << endl;
                        cout << "Área de conhecimento [E - Exatas, H - Humanas, B - Biológicas]: ";
                        cin.get(livro.area, 29);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Título: ";
                        cin.get(livro.titulo, 149);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Autor(es): ";
                        cin.get(livro.autor, 254);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Editora: ";
                        cin.get(livro.editora, 49);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Número de páginas: ";
                        cin >> livro.paginas;

                        fseek(arquivo, sizeof(struct livros) * posicao, SEEK_SET);
                        if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                            cout << "Livro alterado com sucesso!";
                        } else {
                            cout << "Erro ao alterar o livro!";
                        } 
                        cin.ignore();
                        cin.get();
                        break;
                    }
                }
                fclose(arquivo);
                cout << "Deseja alterar outro livro? [S/N]: ";
                cin >> opc;
            } else {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            } 
            break;
        case 3:
            cout << "EXCLUSÃO DE LIVRO" << endl;
            cout << "Digite o código do livro que deseja excluir: ";
            cin >> codLivro;
            arquivo = fopen("dados.dat", "rb");
            auxiliar = fopen("dados.aux", "wb");

            fread(&livro, sizeof(struct livros), 1, arquivo);
            while(!feof(arquivo)){
                if (codLivro != livro.codigo){
                    fwrite(&livro, sizeof(struct livros), 1, auxiliar);
                }
                fread(&livro, sizeof(struct livros), 1, arquivo);
            }

            fclose(arquivo);
            fclose(auxiliar);
            remove("dados.dat");
            rename("dados.aux", "dados.dat");
            break;
        case 4:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL){
                cout << "EMPRÉSTIMO DE LIVRO" << endl;
                cout << "Informe o código do livro: ";
                cin >> codLivro;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                posicao = -1;
                while(!feof(arquivo)){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    posicao++;
                    if (codLivro == livro.codigo){
                        fseek(arquivo, sizeof(struct livros) * posicao, SEEK_SET);
                        cout << "Informe a data do empréstimo: ";
                        cin.get(livro.emp.dataEmprestimo, 9);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Informe a data de devolução: ";
                        cin.get(livro.emp.dataDevolucao, 9);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Informe o nome do usuário: ";
                        cin.get(livro.emp.usuario, 149);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Livro emprestado com sucesso!" << endl;
                        fwrite(&livro, sizeof(struct livros), 1, arquivo);
                        break;
                    }
                }
            } else {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 5:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL){
                cout << "DEVOLUÇÃO DE LIVRO" << endl;
                cout << "Informe o código do livro: ";
                cin >> codLivro;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                posicao = -1;
                while(!feof(arquivo)){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    posicao++;
                    if (codLivro == livro.codigo){
                        fseek(arquivo, sizeof(struct livros) * posicao, SEEK_SET);
                        strcpy(livro.emp.dataEmprestimo, "");
                        strcpy(livro.emp.dataDevolucao, "");
                        strcpy(livro.emp.usuario, "");
                        fwrite(&livro, sizeof(struct livros), 1, arquivo);
                        break;
                    }
                }
                fclose(arquivo);

            } else {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 6:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL){
                cout << "CONSULTAR LIVRO" << endl;
                cout << "Informe o código do livro: ";
                cin >> codLivro;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                while(!feof(arquivo)){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    if (codLivro == livro.codigo){
                        cout << "Código: " << livro.codigo << endl;
                        cout << "Área de conhecimento: " << livro.area << endl;
                        cout << "Título: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autor << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Número de páginas: " << livro.paginas << endl;
                        cin.get();
                        break;
                    }
                }
                fclose(arquivo);
            } else {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 7:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL){
                cout << "LIVROS DISPONÍVEIS" << endl;
                while(!feof(arquivo)){
                    if (strcmp(livro.emp.dataEmprestimo, "") == 0){
                        cout << "Código: " << livro.codigo << endl;
                        cout << "Área de conhecimento: " << livro.area << endl;
                        cout << "Título: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autor << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Número de páginas: " << livro.paginas << endl;
                        cout << endl;
                    }
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                }
                fclose(arquivo);
                cin.ignore();
                cin.get();
            } else {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 8:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL){
                fread(&livro, sizeof(struct livros), 1, arquivo);
                while(!feof(arquivo)){
                    cout << "LISTAGEM GERAL DE LIVROS" << endl;
                    cout << "Código: " << livro.codigo << endl;
                    cout << "Área de conhecimento: " << livro.area << endl;
                    cout << "Título: " << livro.titulo << endl;
                    cout << "Autor(es): " << livro.autor << endl;
                    cout << "Editora: " << livro.editora << endl;
                    cout << "Número de páginas: " << livro.paginas << endl;
                    cout << endl;
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                }
            fclose(arquivo);
                cin.ignore();
                cin.get();
            } else {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 9: 
            cout << "Saindo do sistema..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
        system("cls");
    } while (opcaoMenu != 9);
    
}