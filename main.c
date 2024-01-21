#include <stdio.h>
#include <stdlib.h>
#include "tile.h"


int main(int argc, char * argv[])
{
    int boardX,boardY;
    int* board;

    if(argc != 2)
    {
        printf("please enter the values for x,y");
        return 1;
    }

    boardX = atoi(argv[0]);
    boardY = atoi(argv[1]);

    tile *graph[boardX*boardY];

    board = boardGen(boardX,boardY);

}

int* boardGen(int boardX, int boardY)
{
    int tempBoard[boardX][boardY];
    int i,j,k;
    i = 1;
    for(j = 0; j<boardY; j++)
    {
        for(k = 0; k<boardY; k++)
        {
            tempBoard[k][j]=i;
            i++;
        }
    }
    return tempBoard;
}

tile** graphGen(int* board)
{
    
}

/*
!q !p !q->!p
0  0  1
0  1  0
1  0  1
1  1  1
*/

//test

//test2