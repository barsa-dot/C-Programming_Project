#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROWS 30
#define COLS 80

#define RECTANGLE 1
#define LINE 2
#define TRIANGLE 3
#define CIRCLE 4

typedef struct
{
    int type;

    int x;
    int y;

    int width;
    int height;

    int radius;

    int size;

    int x2;
    int y2;

    int active;

} Shape;

char canvas[ROWS][COLS];

Shape shapes[100];

int count = 0;

/* ==========================
   Canvas Functions
   ========================== */

void initCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = ' ';
        }
    }
}

void displayCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }

        printf("\n");
    }
}

/* ==========================
   Drawing Functions
   ========================== */

void drawRectangle(int x, int y, int width, int height)
{
    int i;

    for(i = 0; i < width; i++)
    {
        canvas[x][y + i] = '*';
        canvas[x + height - 1][y + i] = '*';
    }

    for(i = 0; i < height; i++)
    {
        canvas[x + i][y] = '*';
        canvas[x + i][y + width - 1] = '*';
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int i;

    if(x1 == x2)
    {
        for(i = y1; i <= y2; i++)
        {
            canvas[x1][i] = '*';
        }
    }
    else if(y1 == y2)
    {
        for(i = x1; i <= x2; i++)
        {
            canvas[i][y1] = '*';
        }
    }
}

void drawTriangle(int x, int y, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        canvas[x + i][y] = '*';

        canvas[x + size - 1][y + i] = '*';

        canvas[x + i][y + i] = '*';
    }
}

void drawCircle(int cx, int cy, int r)
{
    int x, y;

    for(x = 0; x < ROWS; x++)
    {
        for(y = 0; y < COLS; y++)
        {
            int value =
                (x - cx) * (x - cx) +
                (y - cy) * (y - cy);

            if(abs(value - r * r) <= r)
            {
                canvas[x][y] = '*';
            }
        }
    }
}

/* ==========================
   Add Shape Functions
   ========================== */

void addRectangle()
{
    Shape s;

    printf("Row: ");
    scanf("%d", &s.x);

    printf("Column: ");
    scanf("%d", &s.y);

    printf("Width: ");
    scanf("%d", &s.width);

    printf("Height: ");
    scanf("%d", &s.height);

    s.type = RECTANGLE;
    s.active = 1;

    shapes[count] = s;
    count++;
}

void addCircle()
{
    Shape s;

    printf("Center Row: ");
    scanf("%d", &s.x);

    printf("Center Column: ");
    scanf("%d", &s.y);

    printf("Radius: ");
    scanf("%d", &s.radius);

    s.type = CIRCLE;
    s.active = 1;

    shapes[count] = s;
    count++;
}

/* ==========================
   Redraw All Shapes
   ========================== */

void redrawAllShapes()
{
    int i;

    initCanvas();

    for(i = 0; i < count; i++)
    {
        if(shapes[i].active)
        {
            if(shapes[i].type == RECTANGLE)
            {
                drawRectangle(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].width,
                    shapes[i].height
                );
            }
            else if(shapes[i].type == CIRCLE)
            {
                drawCircle(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].radius
                );
            }
        }
    }
}

/* ==========================
   Main Program
   ========================== */

int main()
{
    int choice;

    initCanvas();

    while(1)
    {
        printf("\n");
        printf("===== 2D Graphics Editor =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Circle\n");
        printf("3. Display Canvas\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addRectangle();
                redrawAllShapes();
                break;

            case 2:
                addCircle();
                redrawAllShapes();
                break;

            case 3:
                displayCanvas();
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}