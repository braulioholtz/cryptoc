#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Função para criar uma mensagem
bool create_message(string message, string filename)
{
   ofstream arq;
   arq.open("text.txt"); // fix: Colocar uma variavel para criação de várias mensagens
   int i=0;
   if (arq == NULL)  // Se houve erro na abertura
   {
       return false;
   }
   else
   {
        arq << message; /* Grava a string, caractere a caractere */
        arq.close();
        return true;
   }
}

// Função principal
int main()
{
    string message = "", filename = "";
    getline(cin, filename);
    getline(cin, message);
    // Abre um arquivo TEXTO para LEITURA
    if (create_message(message, filename))  // Se houve erro na abertura
    {
        printf("Arquivo criado com exito\n");

    }
    else
    {
        printf("Problemas na abertura do arquivo\n");
    }
    return 0;
}
