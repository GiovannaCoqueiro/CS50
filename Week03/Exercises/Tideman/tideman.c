#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool ciclo(int ganhador, int perdedor);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

//atualiza os votos nos ranks dos eleitores
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

//cria a matriz de preferencias dos eleitores
//   0 1 2
//0| 0 x x
//1| x 0 x
//2| x x 0
//o encontro de uma linha por uma coluna representa o número de eleitores que preferem candidato[linha] ao candidato[coluna]
void record_preferences(int ranks[])
{
    for (int linha = 0; linha < candidate_count; linha++)
    {
        for (int coluna = linha + 1; coluna < candidate_count; coluna++)
        {
            preferences[ranks[linha]][ranks[coluna]]++;
        }
    }
    return;
}

//cria a matriz de preferencias de candidatos, com o ganhador e o perdedor de cada situação
void add_pairs(void)
{
    pair_count = 0;
    for (int linha = 0; linha < candidate_count - 1; linha++)
    {
        for (int coluna = linha + 1; coluna < candidate_count; coluna++)
        {
            if (preferences[linha][coluna] > preferences[coluna][linha])
            {
                pairs[pair_count].winner = linha;
                pairs[pair_count].loser = coluna;
                pair_count++;
            }
            else if (preferences[linha][coluna] < preferences[coluna][linha])
            {
                pairs[pair_count].winner = coluna;
                pairs[pair_count].loser = linha;
                pair_count++;
            }
        }
    }
    return;
}

//ordena os pares por ordem decrescente de força de vitoria
void sort_pairs(void)
{
    int maior_força;
    int força[2] = {0, 0};
    for (int i = 0; i < pair_count - 1; i++)
    {
        maior_força = i;
        força[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        for (int j = i + 1; j < pair_count; j++)
        {
            força[j] = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (força[j] > força[maior_força])
            {
                maior_força = j;
            }
        }
        //troca a posição de dois arrays, deixando em ordem decrescente
        pair backup = pairs[i];
        pairs[i] = pairs[maior_força];
        pairs[maior_força] = backup;
    }
    return;
}

//checa se cria um ciclo no gráfico de setas
bool ciclo(int ganhador, int perdedor)
{
    if (locked[perdedor][ganhador] == true) //checa se tem um ciclo entre dois candidatos entre si
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        //checa se tem um ciclo entre o perdedor e os demais candidatos
        //e se tem ciclo entre o ganhador e o atual candidato
        if (locked[perdedor][i] == true && ciclo(ganhador, i))
        {
            return true;
        }
    }
    return false;
}

//cria o grafico de setas em orden decrescente de força de vitória
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!ciclo(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true; //faz a seta do par de candidatos
        }
    }
    return;
}

//imprime o vencedor da eleição
void print_winner(void)
{
    for (int linha = 0; linha < candidate_count; linha++)
    {
        for (int coluna = 0; coluna < candidate_count; coluna++)
        {
            //se o locked for falso, significa que não há seta apontada para ele
            if (locked[linha][coluna] == false)
            {
                printf("%s\n", candidates[linha]);
                break;
            }
        }
    }
    return;
}