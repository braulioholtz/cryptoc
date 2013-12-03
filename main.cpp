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
    for (int i = 0; i < letter.length(); i++)
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
    message = convertToASCII(read_message(message)); // read txt and convert to ASCII

    //m_c = std::stol(message); // DEBUG
    std::stringstream buffer(message);
    buffer >> m_c;
    long long m;
    for (int i = 0; i < message.length(); i +=3 )
    {
        temp = NumberToString(message[i]) + NumberToString(message[i+1]) + NumberToString(message[i+2]);
        m = 1;
        std::stringstream buffer(temp);
        buffer >> m_c;
        for (int j = 0; j < e; j++)
        {
            // based in http://cppgm.blogspot.com.br/2008/01/rsa-algorithm.html
            m = (m*m_c) % n;
            m = m % n;

        }
        /**<  fix 0 left  */
        if (int(m)<10)
            Result = Result + "00";
        if (int(m)<100 && int(m)>9)
            Result = Result + "0";
        Result = Result + NumberToString(m);
    }
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
    string Result, temp;
    long long m_c;
    message = Encrypt(message, e , n); // DEBUG

    //m_c = std::stol(message); // DEBUG
    std::stringstream buffer(message);
    buffer >> m_c;
    long long m;
    // depois quebrar a mensagem em blocos de 9 caracteres
    //message = "19191919";
    for (int i = 0; i < message.length(); i +=3 )
    {
        temp = NumberToString(message[i]) + NumberToString(message[i+1]) + NumberToString(message[i+2]);
        m = 1;
        std::stringstream buffer(temp);
        buffer >> m_c;
        for (int j = 0; j < e; j++)
        {
            // based in http://cppgm.blogspot.com.br/2008/01/rsa-algorithm.html
            m = (m_c*m) % n;
            m = m % n;

        }
        // fix 0 left
        if (int(m)<10)
            Result = Result + "00";
        if (int(m)<100 && int(m)>9)
            Result = Result + "0";
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
int check(int e, int phi)
{
    int i=0, FLAG = 0;
    for(i=3;e%i==0 && phi%i==0;i+2)
        FLAG = 1;
    FLAG = 0;
    return FLAG;
}

/********************************************//**
 * \brief Main Function
 *
 * \return int 0 for end
 *
 ***********************************************/
int main()
{
    long long p1 = 7, p2 = 17; // Números primos
    long long n = 0, phi = 0, d = 1, s = 0; // variaveis responsaveis pela criptografia (em teste)
    int menu = 0, e=0, FLAG=0;
    string message = "", filename = "";
    do
    {
        system("cls");
        cout << "Menu: \n1 - criar texto\n2 - ler texto criptografado\n";
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
            n = p1 * p2;
            phi=(p1-1)*(p2-1);
            cout << n << "\n";
            do
            {
                cout << "\n Coloque a chave (5):";
                cin >> e; // ?
                FLAG = check(e, n); // apenas teste, começo criptografia
            }while(FLAG==1);
            do
            {
                s = (d*e)%phi;
                d++;
            }while(s!=1);
            d = d-1;
            cout << "\n Digite o nome do arquivo:";
            cin >> filename; // ?
            cout << "\n\Chave Publica: {" << e << ", " << n << "}";
            cout << "\Chave Privada: {" << d << ", " << n << "}";
            cout << "\nArquivo criptografado:\n";
            cout << Encrypt(filename, e, n)<< "<-\n\n";
            cout << "\nArquivo descriptografado:\n";
            cout << Decrypt(filename, e, n)<< "<-\n\n";
            system("pause");
        }
    } while (menu==1 || menu==2);

    return 0;
}
