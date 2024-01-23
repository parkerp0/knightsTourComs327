#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"

#define boardX 5
#define boardY 5

void edgeBuilder(tile *tile,tile *endpoint);

void solver(tile *tile);

int main(int argc, char * argv[])
{
    int i,j,k;

    int board[boardX][boardY];

    tile *graph[(boardX*boardY)];

    k=0;
    for(i=0;i<boardY;i++)
    {
        for(j=0;j<boardX;j++)
        {
            board[i][j] = k;
            graph[k] = malloc(sizeof(tile));
            graph[k]->num = k;
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
            printf("k = %d i = %d j = %d  \n\n",k,i,j);
        }
    }

    for(i=0; i<boardX*boardY; i++)
    {
        solver(graph[i]);
    }

    return 0;
}

void edgeBuilder(tile *tile, struct tile *endpoint)
{
    tile->jumpc= tile->jumpc+1;
    printf("tile %d has %d edges\n", tile->num , tile->jumpc);
    //tile->jump = realloc(tile->jump, sizeof(tile)*(tile->jumpc));
    tile->jump[tile->jumpc] = endpoint;
}

void solver(tile *tile)
{
    int i;
    tile->visit = 1;
    for(i=0; i<tile->jumpc; i++)
    {
        if(tile->jump[i]->visit == 0)
        {
            solver(tile->jump[i]);
        } 
    }

    for(i=0; i<tile->jumpc; i++)
    {
        tile->jump[i]->visit = 0;
    }
}