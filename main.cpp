#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

string folder = "criptografia/"; // Facilitar manutenção

/********************************************//**
 * \brief Convert Numbers to String
 *
 * \param Get int (T)
 * \return string
 *
 * [Converting numbers to strings and strings to numbers] [http://www.cplusplus.com/forum/articles/9645/])
 ***********************************************/
template <typename T>
string NumberToString(int pNumber)
{
    ostringstream oOStrStream;
    oOStrStream << pNumber;
    return oOStrStream.str();
}


/********************************************//**
 * \brief For create txt with messages
 *
 * \param message (string) with the message
 * \param filename (string) with filename
 * \return true or false (if sucess return true)
 *
 ***********************************************/
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

/********************************************//**
 * \brief For read txt
 *
 * \param filename (string) with filename for read
 * \return string with the message
 *
 ***********************************************/
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

/********************************************//**
 * \brief Concatenate string with Integer
 *
 * \param name (string)
 * \param i (integer)
 * \return string with the result concatenation
 *
 ***********************************************/
string concatenate(std::string const& name, int i)
{
    stringstream s;
    s << name << i;
    return s.str();
}

/********************************************//**
 * \brief Convert text for ASCII
 *
 * \param letter (string)
 * \return string with the ASCII Code
 *
 * [Converting string to ASCII] [http://stackoverflow.com/questions/6709795/converting-string-to-ascii]
 ***********************************************/
string convertToASCII(string letter)
{
    string result = "";
    for (int i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        /**<  fix ASCII code :) */
        if (int(x)<10 || int(x)==0)
            result = result + "00";
        if (int(x)<100 && int(x)>9)
            result = result + "0";
        result = concatenate(result, int(x));
    }
    return result;
}


/********************************************//**
 * \brief Function for Encrypt message
 * \todo Correct bug
 *
 * \param letter (string)
 * \return string with the ASCII Code
 *
 ***********************************************/
string Encrypt(string message, int e, int n)
{
    string Result;
    message = convertToASCII("t"); // DEBUG
    unsigned long m=0;
    unsigned long message_int = 0;
    istringstream ( message ) >> m;
    message_int = m;
    Result = message;
    unsigned long res = 1;
    while (e > 0) {
        if (e % 2 != 0) {
            res = (message_int*res) % n;
        }
        m = (message_int*message_int) % n;
        e /= 2;
    }
    Result = NumberToString(res);
    return Result;
}

/********************************************//**
 * \brief Function for Decrypt message
 * \todo Correct bug
 *
 * \param letter (string)
 * \return string with the ASCII Code
 *
 ***********************************************/
string Decrypt(string message, int e, int n)
{
    string Result;
    unsigned long m=0;
    unsigned long message_int = 0;
    istringstream ( message ) >> m;
    message_int = m;
    Result = message;
    unsigned long res = 1;
    while (e > 0) {
        if (e % 2 != 0) {
            res = (res*message_int) % n;
        }
        m = (res*message_int) % n;
        e /= 2;
    }
    Result = NumberToString(res);
    return Result;
}

/********************************************//**
 * \brief Function for check public key
 *
 * \param e - public key
 * \return Int, if validate key return FLAG 0
 *
 ***********************************************/
int check(int e, long int phi)
{
    int i=0, FLAG = 0;
    for(i=3;e%i==0 && phi%i==0;i+2)
        FLAG = 1;
    FLAG = 0;
    return FLAG;
}

/********************************************//**
 * \brief Function for check public key
 *
 * \return int 0 for end
 *
 ***********************************************/
int main()
{
    long int p1 = 7, p2 = 17; // Números primos
    long int n = 0, phi = 0; // variaveis responsaveis pela criptografia (em teste)
    int menu = 0, e=0, FLAG=0;
    string message = "", filename = "";
    //cout << Encrypt("testando");
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
//            message = Encrypt(message);
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
//                cout << Encrypt(filename);
                system("pause");
            }

        }
    } while (menu==1 || menu==2);
    n = p1 * p2;
    n=(p1-1)*(p2-1);
    cout << n << "\n";
    do
    {
        cin >> e; // ?
        FLAG = check(e, n); // apenas teste, começo criptografia
    }while(FLAG==1);
    cout << Encrypt(read_message("test"), e, n)<< "\n\n->";
    cout << Decrypt(Encrypt(read_message("test"), e, n), e, n);
    cout << FLAG;
    return 0;
}
