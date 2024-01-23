#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"

#define boardX 5
#define boardY 5

void edgeBuilder(tile *tile,struct tile *endpoint);

void solver(tile *tile, int *path, int level, int *counter);

void nodeTest(tile *tile);

int main(int argc, char * argv[])
{
    int i,j,k;

    int solutionCount;

    int *path = malloc(sizeof(int)*boardX*boardY); 

    int board[boardX][boardY];

    tile *graph[(boardX*boardY)];

    k=0;
    for(i=0;i<boardY;i++)
    {
        for(j=0;j<boardX;j++)
        {
            board[i][j] = k;
            graph[k] = malloc(sizeof(tile));
            graph[k]->num = k+1; //this lines up the num with the stated tiles in the assignment
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
            //printf("k = %d i = %d j = %d  \n\n",k,i,j);
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
    
    solutionCount = 0;

    for(i=0; i<boardX*boardY; i++)
    {
        solver(graph[i], path, 0, &solutionCount);
        //nodeTest(graph[i]);
    }

    //cleans up the heap after program is done
    for(i=0; i<boardX*boardY; i++)
    {
        free(graph[i]->jump);
        free(graph[i]);
    }
    free(path);

    return 0;
}

void edgeBuilder(tile *tile, struct tile *endpoint)
{
    tile->jump[tile->jumpc] = endpoint;
    tile->jumpc= tile->jumpc+1;
    //printf("tile %d has %d edges\n", tile->num , tile->jumpc);
}

void solver(tile *tile, int *path, int level, int *counter)  
{
    int i;

    path[level] = tile->num;
    tile->visit = 1;
    for(i=0; i<tile->jumpc; i++)  
    {
        if(tile->jump[i]->visit == 0)
        {
            solver(tile->jump[i],path,level+1,counter);
        } 
    }
    //printf("%d\n", level);
    if(level == boardX*boardY-1)
    {
        *counter+=1;
        //printf("%d: ",*counter);

        for(i=0; i<level; i++)
        {
            printf("%d,", path[i]);
        }
        printf("%d", path[level]);
        printf("\n");
    }

    tile->visit = 0;
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