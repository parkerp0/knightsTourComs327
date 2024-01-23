#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"

#define boardX 5
#define boardY 5

void edgeBuilder(tile *tile,struct tile *endpoint);

void solver(tile *tile, int *path, int level);

void nodeTest(tile *tile);

int main(int argc, char * argv[])
{
    int i,j,k;

    int *path = malloc(sizeof(int)*25); //65 is max char for 5x5 board I don't want to compute this rn but I will later

    int board[boardX][boardY];

    tile *graph[(boardX*boardY)];

    k=0;
    for(i=0;i<boardY;i++)
    {
        for(j=0;j<boardX;j++)
        {
            board[i][j] = k;
            graph[k] = malloc(sizeof(tile));
            graph[k]->num = k+1;
            graph[k]->visit = 0;
            graph[k]->jumpc = 0;
            graph[k]->jump = malloc(sizeof(tile)*8);
            k++;
        }
    }

    k=0;
    for(i=0;i<boardY;i++)
    {
        for(j=0;j<boardX;j++)
        {
            //checks each move for the knight
            printf("k = %d i = %d j = %d  \n\n",k,i,j);
            if(i-2>=0 && j-1>=0)
            {
                edgeBuilder(graph[k], graph[board[i-2][j-1]]);
            }
            if(i-2>=0 && j+1<boardX)
            {
                edgeBuilder(graph[k], graph[board[i-2][j+1]]);
            }
            if(i-1>=0 && j-2>=0)
            {
                edgeBuilder(graph[k], graph[board[i-1][j-2]]);
            }
            if(i-1>=0 && j+2<boardX)
            {
                edgeBuilder(graph[k], graph[board[i-1][j+2]]);
            }
            if(i+1<boardY && j-2>=0)
            {
                edgeBuilder(graph[k], graph[board[i+1][j-2]]);
            }
            if(i+1<boardY && j+2<boardX)
            {
                edgeBuilder(graph[k], graph[board[i+1][j+2]]);
            }
            if(i+2<boardY && j-1>=0)
            {
                edgeBuilder(graph[k], graph[board[i+2][j-1]]);
            }
            if(i+2<boardY && j+1<boardX)
            {
                edgeBuilder(graph[k], graph[board[i+2][j+1]]);
            }
            k++;
        }
    }
    
    for(i=0; i<1; i++)
    {
        solver(graph[i], path, 0);
        //nodeTest(graph[i]);
    }

    return 0;
}

void edgeBuilder(tile *tile, struct tile *endpoint)
{
    tile->jump[tile->jumpc] = endpoint;
    tile->jumpc= tile->jumpc+1;
    printf("tile %d has %d edges\n", tile->num , tile->jumpc);
}

void solver(tile *tile, int *path, int level)  
{
    tile->visited = malloc(sizeof(tile)*8);
    int visitCounter = 0;
    int i;

    path[level] = tile->num;
    tile->visit = 1;
    for(i=0; i<tile->jumpc; i++)  
    {
        if(tile->jump[i]->visit == 0)
        {
            tile->visited[visitCounter] = tile->jump[i];
            visitCounter++;
            solver(tile->jump[i],path,level+1);
        } 
    }
    //printf("%d\n", level);
    if(level == 20)
    {
        for(i=0; i<level; i++)
        {
            printf("%d,", path[i]);
        }
        printf("\n");
    }

    for(i=0; i<visitCounter; i++)
    {
        tile->visited[i]->visit = 0;
    }
    free(tile->visited);
}

void nodeTest(tile *tile)
{
    int i;
    printf("tile: %d ", tile->num);
    printf("edges: %d ", tile->jumpc);
    printf("List of edges: ");
    for(i=0; i < tile->jumpc; i++)
    {
        printf("%d ", tile->jump[i]->num);
    }
    printf("\n");
}