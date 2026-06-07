#include <stdio.h>

#define ROWS 30
#define COLS 80

char canvas[ROWS][COLS];

void initCanvas()
{
    int i,j;

    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
        {
            canvas[i][j]=' ';
        }
    }
}

void displayCanvas()
{
    int i,j;

    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
        {
            printf("%c",canvas[i][j]);
        }

        printf("\n");
    }
}

void drawRectangle(int x,int y,int width,int height)
{
    int i;

    for(i=0;i<width;i++)
    {
        canvas[x][y+i]='*';
        canvas[x+height-1][y+i]='*';
    }

    for(i=0;i<height;i++)
    {
        canvas[x+i][y]='*';
        canvas[x+i][y+width-1]='*';
    }
}

void drawLine(int x1,int y1,int x2,int y2)
{
    int i;

    if(x1 == x2) // horizontal line
    {
        for(i=y1;i<=y2;i++)
        {
            canvas[x1][i]='*';
        }
    }
    else if(y1 == y2) // vertical line
    {
        for(i=x1;i<=x2;i++)
        {
            canvas[i][y1]='*';
        }
    }
}

int main()
{
    initCanvas();

    drawRectangle(5,10,15,6);

    drawLine(2,5,2,25);

    displayCanvas();

    return 0;
}