#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <sstream>
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

// Função para concatenar as variaveis string e int
string concatenate(std::string const& name, int i)
{
    stringstream s;
    s << name << i;
    return s.str();
}

string convertToASCII(string letter)
{
    string result = "";
    for (int i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        // fix ASCII code :)
        if (int(x)<10 || int(x)==0)
            result = result + "00";
        if (int(x)<100 && int(x)>9)
            result = result + "0";
        result = concatenate(result, int(x));
    }
    return result;
}


// Função para criptografar a mensagem
string Encrypt(string message)
{
    string Result;
    Result = convertToASCII(message);
    return Result;
}

// Função para descriptografar a mensagem
string Decrypt(string filename)
{
}

// Checar chave
int check(int e, long int phi)
{
    int i=0, FLAG = 0;
    for(i=3;e%i==0 && phi%i==0;i+2)
    {
        FLAG = 1;
    }
    FLAG = 0;
    return FLAG;
}

// Função principal
int main()
{
    long int p1 = 7, p2 = 17; // Números primos
    long int n = 0, phi = 0; // variaveis responsaveis pela criptografia (em teste)
    int menu = 0, e=0, FLAG=0;
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
            cout << "Texto descriptografado\n";
            cout << read_message(filename);
            message = Encrypt(message);
            if (create_message(message, filename))
            {
                cout << "\nTexto criptografado\n";
                cout << read_message(filename);
            }
            else
            {
                cout << "Problemas na abertura do arquivo\n";
            }
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
                cout << Encrypt(filename);
                system("pause");
            }

        }
    } while (menu==1 || menu==2);
    n = p1 * p2;
    phi=(p1-1)*(p2-1);
    cout << phi << "\n";
    /*do
    {
        cin >> e; // ?
        FLAG = check(e, phi); // apenas teste, começo criptografia
        Encrypt(e);
    }while(FLAG==1);
    cout << FLAG;*/
    return 0;
}
