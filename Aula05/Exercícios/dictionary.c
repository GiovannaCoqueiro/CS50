// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 26

// Hash table
node *table[N];

//variáveis globais
unsigned int contword;
unsigned int valor_hash;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    valor_hash = hash(word); //acha em qual posição na hash table a palavra possivelmente está
    node *cursor = table[valor_hash]; //inicia um cursor que aponta pra posição correta na tabela hash

    //percorre a lista linkada
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int pos_hash = 0; //variável que vai armazenar o número na tabela hash na posição correta
    for (int i = 0; i < 2; i++)
    {
        if (word[i] == 39) //garante que passa pra próxima letra se a palavra começar com apóstrofo
        {
            i++;
        }
        else if (word[i] >= 65 && word[i] <= 90)
        {
            pos_hash = word[i] - 65;
        }
        else if (word[i] >= 97 && word[i] <= 122)
        {
            pos_hash = word[i] - 97;
        }
    }
    return pos_hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //abre o arquivo do dicionário e checa se ele é válido
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        printf("Impossivel abrir o arquivo %s\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    //lê cada palavra do dicionário até chegar ao fim
    while(fscanf(infile, "%s", word) != EOF) //de on vai ler, o que vai ler, pra onde vai ler, EOF(end of file)
    {
        node *n = malloc(sizeof(node)); //aloca memória pro novo nó
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word); //onde copiar a string, de onde copiar a string
        valor_hash = hash(word); //descobre o valor na hash table
        n->next = table[valor_hash];
        table[valor_hash] = n;
        contword++; //contador de palavras
    }

    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (contword > 0)
    {
        return contword;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //percorre a hash table
    for (int i = 0; i < N; i++)
    {
        //define um cursor pra lista linkada
        node *cursor = table[i];
        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}