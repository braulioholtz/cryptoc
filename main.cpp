#include <iostream>
#include <stdlib.h>
#include <dirent.h>
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
        return letra;
    }
    else
    {
        return "false";
    }

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
int check(long int e, long int phi)
{
    int i=0, FLAG = 0;
    for(i=3;e%i==0 && phi%i==0;i+2)
    {
        FLAG = 1;
    }
    FLAG = 0;
}

// Função principal
int main()
{
    long int p1 = 0, p2 = 0; // Números primos
    int phi = 2525465465; // variaveis responsaveis pela criptografia (em teste)
    int menu = 0;
    string message = "", filename = "";

    do
    {
        system("cls");
        cout << "Menu: \n1 - criar texto criptogrado\n2 - ler texto criptografado\n";
        cin >> menu;
        fflush(stdin); // Corrigir o bug na entrada de dados
        if (menu==1)
        {
            system("cls");
            cout << "Digite o nome do arquivo:\n";
            getline(cin, filename);
            fflush(stdin);
            cout << "Digite a sua mensagem:\n";
            getline(cin, message);
            fflush(stdin);
            //getline(cin, message);
            if (create_message(message, filename))  // Se houve erro na abertura
            {
                cout << "Arquivo criado com exito\n";

            }
            else
            {
                cout << "Problemas na abertura do arquivo\n";
            }
            cout << "Texto criptografado";
            cout << read_message(filename);
            cout << "Texto descriptografado";
            cout << read_message(filename);
            system("pause");
        }
        else if (menu == 2)
        {
            cout << "Digite o arquivo sem .txt:\n";
            cin >> filename;
            fflush(stdin);
            if (read_message(filename)=="false")
            {
                cout << "Arquivo não existe";
                cout << "\n\n";
                system("pause");
            }
            else
            {
                cout << read_message(filename);
                cout << "\n\n";
                system("pause");
            }

        }
    } while (menu==1 || menu==2);
    cin >> p1 >> p2;
    cout << check(p1, phi); // apenas teste, começo criptografia
    return 0;
}
