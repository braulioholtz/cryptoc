#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <fstream>

using namespace std;

string folder = "criptografia/", tp_file = ".txt"; // Folder with files

/********************************************//**
 * \brief Convert Numbers to String
 *
 * \param Get int (T)
 * \return string
 *
 * [Converting numbers to strings and strings to numbers] [http://www.cplusplus.com/forum/articles/9645/])
 ***********************************************/
template <typename T>
string NumberToString(T pNumber)
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
    filename = folder+filename+tp_file;
    arq.open(filename.c_str()); // fix: Colocar uma variavel para criação de várias mensagens
    if (arq.is_open())  // Se houve erro na abertura
    {
        arq << message; /* Grava a string, caractere a caractere */
        arq.close();
        return true;

    }
    else
        return false;
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
    filename = folder+filename+tp_file;
    ifstream arq_read(filename.c_str());
    string letra="";
    if (arq_read.is_open())  // Se houve erro na abertura
    {
        while(!arq_read.eof())
            getline(arq_read, letra); // Saves the line in letra.

        arq_read.close();
        return letra;
    }
    else
        return "false";
}

/********************************************//**
 * \brief Concatenate string with Integer
 *
 * \param name (string)
 * \param i (integer)
 * \return string with the result concatenation
 *#include <string.h>
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
    unsigned int i;
    for (i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        /**<  fix ASCII code :) */
        if (int(x)<10)
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
    string Result, temp;
    long long m_c;
    unsigned int i;
    message = convertToASCII(read_message(message)); // read txt and convert to ASCII

    long long m;
    for (i = 0; i < message.length(); i +=3 )
    {
        temp = NumberToString(message[i]) + NumberToString(message[i+1]) + NumberToString(message[i+2]);
        m = 1;
        std::stringstream buffer(temp);
        buffer >> m_c;
        for (int j = 0; j < e; j++)
        {
            // based in http://cppgm.blogspot.com.br/2008/01/rsa-algorithm.html
            m = (m*m_c) % n;
        }
        m = m % n;
        if (m<10000000)
            Result = Result + "0"; // fix break characters
        Result = Result + NumberToString(m);
    }
    Result = Result;
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
string Decrypt(string message, int d, int n) // int e temporario
{
    string Result, temp;
    long long m_c = 0;
    unsigned int i;
    message = read_message(message); // read txt and convert to ASCII
    long long m;
    for (i = 0; i < message.length(); i+=8 )
    {
        temp = NumberToString(message[i]) + NumberToString(message[i+1]) + NumberToString(message[i+2]) + NumberToString(message[i+3]) + NumberToString(message[i+4]) + NumberToString(message[i+5]) + NumberToString(message[i+6]) + NumberToString(message[i+7]);

        m_c = 0;
        m = 1;
        stringstream buffer(temp);
        buffer >> m_c;

        for (int j = 0; j < d; j++)
            m = (m*m_c) % n;

        m = m % n;

        Result = Result + NumberToString(m);
    }
    return Result;
}
/********************************************//**
 * \brief Function for check public key
 *
 * \param e - public key
 * \return Int, if validate key return FLAG 0
 *
 ***********************************************/
long long check(int phi)
{
    int i=0, FLAG = 0, e=0;

    do
    {
        cout << "\n Insire a chave publica (4253):\n";
        cin >> e; // chave pública
        for(i=3;e%i==0 && phi%i==0;i+=2)
            FLAG = 1;
        FLAG = 0;
    }while(FLAG==1);
    return e;
}
/********************************************//**
 * \brief Function for Euler teorem
 *
 * \param e - public key
 * \return Int, if validate key return FLAG 0
 * [Teorema de Euler] [http://pt.wikipedia.org/wiki/Fun%C3%A7%C3%A3o_totiente_de_Euler]
 ***********************************************/
long long tot_euler(long long p, long long q)
{
    long long phi=0;
    phi=(p-1)*(q-1);
    return phi;
}
/********************************************//**
 * \brief Function for calcular chave privada
 *
 * \param e - public key
 * \return Int, if validate key return FLAG 0
 * [Teorema de Euler] [http://pt.wikipedia.org/wiki/Fun%C3%A7%C3%A3o_totiente_de_Euler]
 ***********************************************/
long long calc_private(long long e, long long phi)
{
    long long d = 1, s = 0;
    do
    {
        s = (d*e)%phi;
        d++;
    }while(s!=1);
    d = d-1;
    return d;
}

/********************************************//**
 * \brief Main Function
 *
 * \return int 0 for end
 *
 ***********************************************/
int main()
{
    string message = "", filename = "";
    int menu = 0;
    long long p = 4229, q = 4283; // Números primos
    long long n = 0, phi = 0, e = 0;
    n = p * q;
    phi=tot_euler(p, q);
    e = check(phi);

    do
    {
        system("cls");
        cout << "Menu: \n1 - Criar texto\n2 - Criptografar\n3 - Descriptografar\n4 - Sair\n";
        cin >> menu;
        fflush(stdin); // Corrigir o bug na entrada de dados
        switch (menu)
        {
            case 1:
                system("cls");
                cout << "Digite o nome do arquivo:\n";
                getline(cin, filename);
                fflush(stdin);
                cout << "Digite a sua mensagem:\n";
                getline(cin, message);
                fflush(stdin);
                //getline(cin, message);
                if (create_message(message, filename))  // Se houve erro na abertura
                    cout << "Arquivo criado com exito\n";
                else
                    cout << "Problemas na abertura do arquivo\n";
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "\n Digite o nome do arquivo:";
                cin >> filename; // ?
                if (create_message(Encrypt(filename, e, n), filename))  // Se houve erro na abertura
                    cout << "Arquivo criptogrado com sucesso\n";
                else
                    cout << "Problemas ao criptografar o arquivo, verifique se o arquivo existe\n";
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "\n Digite o nome do arquivo:";
                cin >> filename; // ?
                if (create_message(Decrypt(filename, calc_private(e, phi), n), filename))  // Se houve erro na abertura
                    cout << "\nArquivo criptogrado com sucesso\n";
                else
                    cout << "\nProblemas ao criptografar o arquivo, verifique se o arquivo existe\n";
                system("pause");
                break;
            case 4:
                menu = 4;
                break;
            default:
                cout << "\nOpcao invalida\n";
                system("pause");
                menu = 5;
                break;
        }
    } while (menu!=4);

    return 0;
}
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <fstream>

using namespace std;

string folder = "criptografia/", tp_file = ".txt"; // Folder with files

/********************************************//**
 * \brief Convert Numbers to String
 *
 * \param Get int (T)
 * \return string
 *
 * [Converting numbers to strings and strings to numbers] [http://www.cplusplus.com/forum/articles/9645/])
 ***********************************************/
template <typename T>
string NumberToString(T pNumber)
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
    filename = folder+filename+tp_file;
    arq.open(filename.c_str()); // fix: Colocar uma variavel para criação de várias mensagens
    if (arq.is_open())  // Se houve erro na abertura
    {
        arq << message; /* Grava a string, caractere a caractere */
        arq.close();
        return true;

    }
    else
        return false;
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
    filename = folder+filename+tp_file;
    ifstream arq_read(filename.c_str());
    string letra="";
    if (arq_read.is_open())  // Se houve erro na abertura
    {
        while(!arq_read.eof())
            getline(arq_read, letra); // Saves the line in letra.

        arq_read.close();
        return letra;
    }
    else
        return "false";
}

/********************************************//**
 * \brief Concatenate string with Integer
 *
 * \param name (string)
 * \param i (integer)
 * \return string with the result concatenation
 *#include <string.h>
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
    unsigned int i;
    for (i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        /**<  fix ASCII code :) */
        if (int(x)<10)
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
    string Result, temp;
    long long m_c;
    unsigned int i;
    message = convertToASCII(read_message(message)); // read txt and convert to ASCII

    long long m;
    for (i = 0; i < message.length(); i +=3 )
    {
        temp = NumberToString(message[i]) + NumberToString(message[i+1]) + NumberToString(message[i+2]);
        m = 1;
        std::stringstream buffer(temp);
        buffer >> m_c;
        for (int j = 0; j < e; j++)
        {
            // based in http://cppgm.blogspot.com.br/2008/01/rsa-algorithm.html
            m = (m*m_c) % n;
        }
        m = m % n;
        if (m<10000000)
            Result = Result + "0"; // fix break characters
        Result = Result + NumberToString(m);
    }
    Result = Result;
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
string Decrypt(string message, int d, int n) // int e temporario
{
    string Result, temp;
    long long m_c = 0;
    unsigned int i;
    message = read_message(message); // read txt and convert to ASCII
    long long m;
    for (i = 0; i < message.length(); i+=8 )
    {
        temp = NumberToString(message[i]) + NumberToString(message[i+1]) + NumberToString(message[i+2]) + NumberToString(message[i+3]) + NumberToString(message[i+4]) + NumberToString(message[i+5]) + NumberToString(message[i+6]) + NumberToString(message[i+7]);

        m_c = 0;
        m = 1;
        stringstream buffer(temp);
        buffer >> m_c;

        for (int j = 0; j < d; j++)
            m = (m*m_c) % n;

        m = m % n;

        Result = Result + NumberToString(m);
    }
    return Result;
}
/********************************************//**
 * \brief Function for check public key
 *
 * \param e - public key
 * \return Int, if validate key return FLAG 0
 *
 ***********************************************/
long long check(int phi)
{
    int i=0, FLAG = 0, e=0;

    do
    {
        cout << "\n Insire a chave publica (4253):\n";
        cin >> e; // chave pública
        for(i=3;e%i==0 && phi%i==0;i+=2)
            FLAG = 1;
        FLAG = 0;
    }while(FLAG==1);
    return e;
}
/********************************************//**
 * \brief Function for Euler teorem
 *
 * \param e - public key
 * \return Int, if validate key return FLAG 0
 * [Teorema de Euler] [http://pt.wikipedia.org/wiki/Fun%C3%A7%C3%A3o_totiente_de_Euler]
 ***********************************************/
long long tot_euler(long long p, long long q)
{
    long long phi=0;
    phi=(p-1)*(q-1);
    return phi;
}
/********************************************//**
 * \brief Function for calcular chave privada
 *
 * \param e - public key
 * \return Int, if validate key return FLAG 0
 * [Teorema de Euler] [http://pt.wikipedia.org/wiki/Fun%C3%A7%C3%A3o_totiente_de_Euler]
 ***********************************************/
long long calc_private(long long e, long long phi)
{
    long long d = 1, s = 0;
    do
    {
        s = (d*e)%phi;
        d++;
    }while(s!=1);
    d = d-1;
    return d;
}

/********************************************//**
 * \brief Main Function
 *
 * \return int 0 for end
 *
 ***********************************************/
int main()
{
    string message = "", filename = "";
    int menu = 0;
    long long p = 4229, q = 4283; // Números primos
    long long n = 0, phi = 0, e = 0; // variaveis responsaveis pela criptografia (em teste)
    n = p * q;
    phi=tot_euler(p, q);
    e = check(phi);
    cout << "\n\Chave Publica: {" << e << ", " << n << "}";

    do
    {
        system("cls");
        cout << "Menu: \n1 - Criar texto\n2 - Criptografar\n3 - Descriptografar\n4 - Sair\n";
        cin >> menu;
        fflush(stdin); // Corrigir o bug na entrada de dados
        switch (menu)
        {
            case 1:
                system("cls");
                cout << "Digite o nome do arquivo:\n";
                getline(cin, filename);
                fflush(stdin);
                cout << "Digite a sua mensagem:\n";
                getline(cin, message);
                fflush(stdin);
                //getline(cin, message);
                if (create_message(message, filename))  // Se houve erro na abertura
                    cout << "Arquivo criado com exito\n";
                else
                    cout << "Problemas na abertura do arquivo\n";
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "\n Digite o nome do arquivo:";
                cin >> filename; // ?
                if (create_message(Encrypt(filename, e, n), filename))  // Se houve erro na abertura
                    cout << "Arquivo criptogrado com sucesso\n";
                else
                    cout << "Problemas ao criptografar o arquivo, verifique se o arquivo existe\n";
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "\n Digite o nome do arquivo:";
                cin >> filename; // ?
                cout << "\Chave Privada: {" << calc_private(e, phi) << ", " << n << "}";
                if (create_message(Decrypt(filename, calc_private(e, phi), n), filename))  // Se houve erro na abertura
                    cout << "\nArquivo criptogrado com sucesso\n";
                else
                    cout << "\nProblemas ao criptografar o arquivo, verifique se o arquivo existe\n";
                system("pause");
                break;
            case 4:
                menu = 4;
                break;
            default:
                cout << "\nOpcao invalida\n";
                system("pause");
                menu = 5;
                break;
        }
    } while (menu!=4);

    return 0;
}
