#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>

using namespace std;

// Função para criar uma mensagem
bool create_message(char message[100], char filename[100])
{
   FILE *arq;
   arq = fopen(filename, "wt");
   int i=0;

   if (arq == NULL)  // Se houve erro na abertura
   {
       return false;
   }
   else
   {
        for(i=0; message[i]; i++) putc(message[i], arq); /* Grava a string, caractere a caractere */
        return true;
   }
   fclose(arq);
}

// Função principal
int main()
{
    char message[100] = "";
    char filename[100] = "";
    cin >> message;
    cin >> filename;
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
