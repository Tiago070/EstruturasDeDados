#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct emprestimos {
    char dt_emp[10], dt_dev[10], usuario[255];
};

struct livros {
    int codigo, paginas;
    char area[30], titulo[255], autores[255], editora[50];
    struct emprestimos emp;
};

int opcMenu, codLivro, posicao;
char opc;

FILE *arquivo, *arquivoAux;

struct livros livro;

int main(){
    do {
        cout << "###### SISTEMA LEGAL DE BIBLIOTECA ######" << endl;
        cout << "1 - Cadastro" << endl;
        cout << "2 - Alteração" << endl;
        cout << "3 - Exclusão" << endl;
        cout << "4 - Empréstimo" << endl;
        cout << "5 - Devolução" << endl;
        cout << "6 - Consulta de livro" << endl;
        cout << "7 - Livros disponíveis" << endl;
        cout << "8 - Listagem geral de livros" << endl;
        cout << "9 - Sair" << endl << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcMenu;

        switch (opcMenu){
            case 1:
                cout << "Deseja cadastrar um livro (S ou N)?";
                cin >> opc;
                while (opc == 'S'){
                    cout << "Código: ";
                    cin >> livro.codigo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Área: ";
                    cin.get(livro.area, 30);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Título: ";
                    cin.get(livro.titulo, 255);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Autor(es): ";
                    cin.get(livro.autores, 255);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Editora: ";
                    cin.get(livro.editora, 50);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nº páginas: ";
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

                    cout << "Deseja cadastrar um livro (S ou N)?";
                    cin >> opc;
                }
                break;
            case 2:
                arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){

                    cout << "Digite o código do livro que deseja alterar: ";
                    cin >> codLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    posicao = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        posicao++;
                        if (codLivro == livro.codigo){
                            cout << "Área: ";
                            cin.get(livro.area, 30);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Título: ";
                            cin.get(livro.titulo, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Autor(es): ";
                            cin.get(livro.autores, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Editora: ";
                            cin.get(livro.editora, 50);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Nº páginas: ";
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

                } else {
                    cout << "Erro ao abrir o banco de dados!";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 3:
                cout << "Digite o código do livro que deseja excluir: ";
                cin >> codLivro;
                arquivo = fopen("dados.dat", "rb");
                arquivoAux = fopen("dados.aux", "wb");

                fread(&livro, sizeof(struct livros), 1, arquivo);
                while(!feof(arquivo)){
                    if (codLivro != livro.codigo){
                        fwrite(&livro, sizeof(struct livros), 1, arquivoAux);
                    }
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                }

                fclose(arquivo);
                fclose(arquivoAux);
                remove("dados.dat");
                rename("dados.aux", "dados.dat");
                break;
            case 4:
                arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){
                    cout << "Digite o código do livro que deseja emprestar: ";
                    cin >> codLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    posicao = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        posicao++;
                        if (codLivro == livro.codigo){
                            fseek(arquivo, sizeof(struct livros) * posicao, SEEK_SET);
                            cout << "Data de empréstimo: ";
                            cin.get(livro.emp.dt_emp, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Data de devolução: ";
                            cin.get(livro.emp.dt_dev, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Usuário: ";
                            cin.get(livro.emp.usuario, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            case 5:
                arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){
                    cout << "Digite o código do livro que deseja devolver: ";
                    cin >> codLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    posicao = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        posicao++;
                        if (codLivro == livro.codigo){
                            fseek(arquivo, sizeof(struct livros) * posicao, SEEK_SET);
                            strcpy(livro.emp.dt_emp, "");
                            strcpy(livro.emp.dt_dev, "");
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
                    cout << "Digite o código do livro que deseja pesquisar: ";
                    cin >> codLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        if (codLivro == livro.codigo){
                            cout << "Código: " << livro.codigo << endl;
                            cout << "Área: " << livro.area << endl;
                            cout << "Título: " << livro.titulo << endl;
                            cout << "Autor(es): " << livro.autores << endl;
                            cout << "Editora: " << livro.editora << endl;
                            cout << "Nº páginas: " << livro.paginas << endl;
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
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    while(!feof(arquivo)){
                        if (strcmp(livro.emp.dt_emp, "") == 0){
                            cout << "Código: " << livro.codigo << endl;
                            cout << "Área: " << livro.area << endl;
                            cout << "Título: " << livro.titulo << endl;
                            cout << "Autor(es): " << livro.autores << endl;
                            cout << "Editora: " << livro.editora << endl;
                            cout << "Nº páginas: " << livro.paginas << endl;
                            cout << "---------------------------------------" << endl;
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
                        cout << "Código: " << livro.codigo << endl;
                        cout << "Área: " << livro.area << endl;
                        cout << "Título: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autores << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Nº páginas: " << livro.paginas << endl;
                        cout << "---------------------------------------" << endl;
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
                cout << "Obrigado por usar nossa solução!";
                break;
            default:
                cout << "Informe uma opção válida!";
                break;
        }
        cout << "\e[2J" << "\e[0;0H";
    } while (opcMenu != 9);

}