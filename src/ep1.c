#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// DEVE-SE COMENTAR UM DESSES INCLUDES PARA ESCOLHER A IMPLEMENTACAO DO GRAFO

// #include "grafo_matrizadj.h"
#include "grafo_listaadj.h"

#define inf 9999;

/************************************** ALG. DE PRIM **********************************************/

int maxKey(float key[], bool mstSet[], Grafo *grafo)
{
    float max = -1;
    int max_i = -1;

    for (int v = 0; v < grafo->numVertices; v++)
        if (mstSet[v] == false && key[v] > max)
        {
            max = key[v];
            max_i = v;
        }
    return max_i;
}

int printAGM(int ant[], Grafo *grafo)
{
    printf("Aresta \tPeso\n");
    for (int i = 1; i < grafo->numVertices; i++)
        printf("%d - %d \t%.1f \n", ant[i], i, obtemPesoAresta(i, ant[i], grafo));
}

void prim(Grafo *grafo, int *parent)
{
    int i;
    float key[grafo->numVertices];
    bool mstSet[grafo->numVertices];

    for (i = 0; i < grafo->numVertices; i++)
    {
        key[i] = -1;
        mstSet[i] = false;
        parent[i] = -1;
    }

    key[0] = inf;

    for (int count = 0; count < grafo->numVertices - 1; count++)
    {
        int u = maxKey(key, mstSet, grafo);
        mstSet[u] = true;

        for (int v = 0; v < grafo->numVertices; v++)

            if (existeAresta(u, v, grafo) && mstSet[v] == false && obtemPesoAresta(u, v, grafo) > key[v])
            {
                parent[v] = u;
                key[v] = obtemPesoAresta(u, v, grafo);
            }
    }

    // printAGM(parent, grafo);
}

/************************************ BUSCA **********************************************/

bool busca(Grafo *grafo, int inicio, int destino, float *min)
{
    int i;
    bool visitado[grafo->numVertices];
    int queue[grafo->numVertices];
    int frente = 0, traseira = 0;
    int ant[grafo->numVertices];

    for (i = 0; i < grafo->numVertices; i++)
        visitado[i] = false;

    queue[traseira++] = inicio;
    visitado[inicio] = true;
    ant[inicio] = -1;

    while (frente < traseira)
    {
        int v = queue[frente++];

        if (v == destino)
        {
            int u = destino;
            while (ant[u] != -1)
            {
                if (obtemPesoAresta(ant[u], u, grafo) < *min)
                {
                    *min = obtemPesoAresta(ant[u], u, grafo);
                }
                u = ant[u];
            }

            return true;
        }

        for (int i = 0; i < grafo->numVertices; i++)
        {
            if (existeAresta(v, i, grafo) && !visitado[i])
            {
                queue[traseira++] = i;
                visitado[i] = true;
                ant[i] = v;
            }
        }
    }

    return false;
}

int main(int argc, char **argv)
{
    int i;

    Grafo grafo;

    // num de argumentos deve ser 2
    // Ex: arq.exe entrada.txt
    if (argc != 2)
    {
        fprintf(stderr, "Erro: quantidade de argumentos\n");
    }

    FILE *arq_ent = fopen(argv[1], "r");
    if (!arq_ent)
    {
        fprintf(stderr, "Erro: ponteiro do arq_ent\n");
    }

    int numVertices, numArestas, numConsultas;
    if (fscanf(arq_ent, "%d %d %d", &numVertices, &numArestas, &numConsultas) != 3)
    {
        fprintf(stderr, "Erro: falha na leitura da primeira linha\n");
    }

    int v, u;
    float peso;
    for (i = 1; i <= numArestas; i++)
    {
        if (fscanf(arq_ent, "%d %d %f", &v, &u, &peso) != 3)
        {
            fprintf(stderr, "Erro: falha de leitura de: v u peso\n");
        }
    }

    int partida, chegada;
    for (i = 1; i <= numConsultas; i++)
    {
        if (fscanf(arq_ent, "%d %d", &partida, &chegada) != 2)
        {
            fprintf(stderr, "Erro: falha de leitura das consultas\n");
        }
    }

    fclose(arq_ent);

    return 0;
}
