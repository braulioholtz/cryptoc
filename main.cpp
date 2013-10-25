#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Função para criar uma mensagem
bool create_message(string message, string filename)
{
    ofstream arq;
    filename = "criptografia/"+filename+".txt";
    arq.open(filename.c_str()); // fix: Colocar uma variavel para criação de várias mensagens
    if (arq.is_open())  // Se houve erro na abertura
    {
        arq << message; /* Grava a string, caractere a caractere */
        arq.close();
        return true;

    }
    else
    {
        return false;
    }
}

// Função para ler a mensagem
string read_message(string filename)
{
    ifstream arq_read;
    string texto;
    arq_read.open(filename.c_str());
    if (arq_read.is_open())  // Se houve erro na abertura
    {
        while(!arq_read.eof())
        {
            getline(arq_read, texto);
            cout << texto << "\n";
        }
    }
}

// Função principal
int main()
{
    string message = "", filename = "";
    cout << "Digite o nome do arquivo:\n";
    getline(cin, filename);
    cout << "Digite a sua mensagem:\n";
    getline(cin, message);
    // Abre um arquivo TEXTO para LEITURA
    if (create_message(message, filename))  // Se houve erro na abertura
    {
        cout << "Arquivo criado com exito\n";

    }
    else
    {
        cout << "Problemas na abertura do arquivo\n";
    }
    return 0;
}
