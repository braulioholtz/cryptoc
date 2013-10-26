#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string folder = "criptografia/"; // Facilitar manutenção

// Função para criar uma mensagem
bool create_message(string message, string filename)
{
    ofstream arq;
    filename = folder+filename+".txt";
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
    filename = folder+filename+".txt";
    ifstream arq_read(filename.c_str());
    string letra="";
    if (arq_read.is_open())  // Se houve erro na abertura
    {
        while(!arq_read.eof())
        {
            getline(arq_read, letra); // Saves the line in letra.

        }
        arq_read.close();
    }
    return letra;
}
// Função para criptografar a mensagem
string Encrypt(string filename)
{
}

// Função para descriptografar a mensagem
string Decrypt(string filename)
{
}

// Checar chave
int check()
{
    int i;
    /*
    for(i=3;e%i==0 && phi%i==0;i+2)
    {
        FLAG = 1;
        return;
    }
    FLAG = 0;
    */
}

// Função principal
int main()
{
    int p = 0, q = 0, phi = 0;
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

    cout << read_message(filename);
    return 0;
}
